"""Fresh strict admission and single-writer publication of exact reconstructions.

    python tools/promote.py SYMBOL SOURCE.c [--summary TEXT] [--verify-only]
    python tools/promote.py --unit UNIT_ID --reason TEXT [--verify-only]
    python tools/promote.py --data DATA.c [--summary TEXT] [--verify-only]
    python tools/promote.py --recover
    python tools/promote.py --retire-data SRC.c --reason TEXT [--verify-only]

The source is frozen into src/recovered/, freshly compiled under the symbol's
catalogued object profile and admitted only when the complete original scope,
ordinary bytes, semantic fixups and private contributions match. The existing
manifest is independently re-verified before and after. Nothing here patches
bytes, and nothing here depends on earlier search runs.
"""
import argparse
import json
import re
import shutil
import sys
from pathlib import Path
from common import ROOT, FormatError, cards, fixture, identity, ownership, ownership_review, read_json, recipes, relative, sha256, write_json
from compiler import compile_source, validate_receipt
import assembler
from library_match import SCAFFOLD_SEGMENT, import_symbols
from recovery_gate import admission_targets, check_data_member, check_member, data_targets
from verify_recovery import verify
import compiler_profiles
import mapsym
import ne
import omf
import publication
import link_lane

GOOD = ('CONFIRMED_MEMBER', 'STRONGLY_SUPPORTED_MEMBER')
PROOF_TOOLS = ['tools/matcher.py', 'tools/library_match.py', 'tools/recovery_gate.py', 'tools/verify_recovery.py', 'tools/compiler.py', 'tools/assembler.py',
               'tools/cfg_solver.py', 'tools/ne.py', 'tools/omf.py', 'tools/mapsym.py', 'tools/promote.py', 'tools/publication.py',
               'layout/toolchain.json', 'layout/fixtures.json', 'layout/compiler-profiles.json', 'layout/runtime-ownership.json',
               'layout/pragma-review.json']


def semantic_summary(text, summary=None):
    comment = re.search(r'/\*(.*?)\*/', text, re.S)
    result = (summary or (comment.group(1).strip() if comment else '')).strip()
    if not result:
        raise FormatError('state the semantic hypothesis in a leading C block comment or with --summary')
    return result


def reviewed_intrinsic_source(unit, source):
    """A source-local strlen intrinsic is admissible only in an exact, tested, reviewed unit source."""
    if not unit or unit.get('layout') != 'reviewed':
        return False
    if (unit.get('last_test') or {}).get('result') not in GOOD:
        return False
    unit_source = (ROOT / unit.get('source', '')).resolve()
    if not unit_source.is_relative_to(ROOT) or not unit_source.is_file() or unit.get('source_identity') != identity(unit_source):
        return False
    # Path.read_text normalizes CRLF on Windows, as the variant loader does.
    return source == unit_source.read_text()


RUNTIME_LIBRARIES = ('toolchain/sdk300/CLIB/LLIBCW.LIB', 'toolchain/sdk300/CLIB/LLIBFPW.LIB', 'toolchain/sdk300/WLIB/LIBW.LIB', 'toolchain/msc700/LIB/LIBH.LIB')
_RUNTIME_PUBLICS = None


def runtime_library_publics():
    """Publics defined by any member of the pinned runtime libraries the game links."""
    global _RUNTIME_PUBLICS
    if _RUNTIME_PUBLICS is None:
        names = set()
        for lib in RUNTIME_LIBRARIES:
            for data in omf.library_modules((ROOT / lib).read_bytes()):
                try:
                    names.update(p['name'] for p in omf.parse(data)['publics'])
                except FormatError:
                    continue
        _RUNTIME_PUBLICS = names
    return _RUNTIME_PUBLICS


PACK_INDEX = re.compile(r'\bmatch_position\s*\[\s*(0[xX][0-9A-Fa-f]+|\d+)\s*\]')


def pack_index_bindings(code):
    return [m.group(0) for m in PACK_INDEX.finditer(code) if int(m.group(1), 0) > 0]


INLINE_ASM_REVIEW = ROOT / 'layout/inline-asm-review.json'
PRAGMA_REVIEW = ROOT / 'layout/pragma-review.json'


def reviewed_optimize_pragmas(code, allow=False):
    """Blank only an evidence-backed, exact per-function optimize/restore pair.

    The source passed to the compiler is never rewritten here.  Blanking is only
    for the ordinary-C source check below.  A populated review is deliberately
    fail-closed: it must identify one setting and the empty-on restore text for a
    particular function, plus repository-local evidence.  The caller still needs
    the complete strict member proof and an explicit --steered provenance note.
    """
    directives = list(re.finditer(r'(?m)^[ \t]*(#\s*pragma\s+optimize\b[^\r\n]*)[ \t]*$', code, re.I))
    if not directives:
        return code, False
    if not allow:
        raise FormatError('recovered source #pragma optimize requires a reviewed per-function entry')
    if not PRAGMA_REVIEW.is_file():
        raise FormatError('recovered source #pragma optimize requires layout/pragma-review.json')
    document = read_json(PRAGMA_REVIEW)
    review = document.get('functions') if isinstance(document, dict) else None
    if not isinstance(review, dict):
        raise FormatError('pragma review must contain a functions map')

    parsed = []
    syntax = re.compile(r'#\s*pragma\s+optimize\s*\(\s*"([^"]*)"\s*,\s*(off|on)\s*\)', re.I)
    for match in directives:
        text = match.group(1)
        setting = syntax.fullmatch(text)
        if not setting:
            raise FormatError('unsupported #pragma optimize text: ' + text.strip())
        parsed.append((match, text.strip(), setting.group(1), setting.group(2).lower()))

    claimed = set()
    out = code
    for name, start, end in function_spans(code):
        header = re.search(r'([A-Za-z_]\w*)\s*\([^()]*\)\s*$', code[:start])
        if not header or header.group(1) != name:
            continue
        before = [(i, row) for i, row in enumerate(parsed)
                  if row[0].end() <= header.start() and
                  not re.search(r'[;{}#=]', code[row[0].end():header.start()])]
        after = [(i, row) for i, row in enumerate(parsed)
                 if row[0].start() > end and not code[end + 1:row[0].start()].strip()]
        if not before or not after:
            continue
        if len(before) != 1 or len(after) != 1:
            raise FormatError('ambiguous #pragma optimize boundary around ' + name)
        set_index, (set_match, set_text, letters, state) = before[0]
        restore_index, (restore_match, restore_text, restore_letters, restore_state) = after[0]
        if set_index == restore_index:
            continue

        symbol = name if name.startswith('_') else '_' + name
        entry = review.get(symbol)
        if not isinstance(entry, dict):
            raise FormatError('unreviewed #pragma optimize in ' + symbol)
        if entry.get('pragma_text') != set_text or entry.get('restore_text') != restore_text:
            raise FormatError('pragma text for %s differs from layout/pragma-review.json' % symbol)
        if restore_letters != '' or restore_state != 'on':
            raise FormatError('pragma restore for %s must be #pragma optimize("", on)' % symbol)
        evidence = entry.get('evidence')
        if not isinstance(evidence, list) or not evidence:
            raise FormatError('pragma review for %s needs repository-local evidence paths' % symbol)
        for item in evidence:
            if not isinstance(item, str) or not item.strip():
                raise FormatError('pragma review evidence for %s must be nonempty paths' % symbol)
            path = Path(item)
            resolved = (ROOT / path).resolve() if not path.is_absolute() else path.resolve()
            if path.is_absolute() or not resolved.is_relative_to(ROOT) or not resolved.is_file():
                raise FormatError('pragma review evidence for %s is missing or outside the repository: %s' % (symbol, item))
        if set_index in claimed or restore_index in claimed:
            raise FormatError('one pragma directive is associated with more than one function')
        claimed.update((set_index, restore_index))
        # Only a recognized pair with exact recorded text is blanked.  Preserve
        # newlines and offsets so any later source checks see the same layout.
        for match in (set_match, restore_match):
            out = out[:match.start()] + re.sub(r'[^\r\n]', ' ', out[match.start():match.end()]) + out[match.end():]

    if len(claimed) != len(directives):
        raise FormatError('every #pragma optimize must immediately bracket one reviewed function')
    return out, True


def function_spans(code):
    """(name, start, end) of each top-level function body in comment-free C."""
    spans, depth, name, start = [], 0, None, None
    for i, ch in enumerate(code):
        if ch == '{':
            if depth == 0:
                header = re.findall(r'([A-Za-z_]\w*)\s*\([^()]*\)\s*$', code[:i])
                name, start = (header[-1] if header else None), i
            depth += 1
        elif ch == '}':
            depth -= 1
            if depth == 0 and name:
                spans.append((name, start, i))
                name = None
    return spans


def reviewed_inline_asm(code):
    """Blank the `_asm` blocks a review evidences; anything unreviewed stays and is refused.

    MSC 7.00 compiles `_asm { ... }` inside a C function, and some originals did
    this (hand-written idioms such as a dead `mov dx, 0` inside a compiler frame).
    A block is admissible only in a function listed in layout/inline-asm-review.json
    whose recorded signature instruction occurs in the original's disassembly, and
    never as byte emission. Strict proof of the complete member is still required.
    """
    if not re.search(r'\b_asm\b', code) or not INLINE_ASM_REVIEW.is_file():
        return code
    review = read_json(INLINE_ASM_REVIEW)['functions']
    by_symbol = {c['symbol']: c for c in cards()}
    out, last = [], 0
    for name, start, end in function_spans(code):
        body = code[start:end + 1]
        if not re.search(r'\b_asm\b', body):
            continue
        entry = review.get('_' + name) or review.get(name)
        card = by_symbol.get('_' + name) or by_symbol.get(name)
        if not entry or not card:
            continue
        rows = ['%s %s' % (r['mnemonic'], r['operands']) for r in card['disassembly']]
        if entry['signature'] not in rows:
            raise FormatError('inline asm review for %s names signature %r, absent from the original' % (name, entry['signature']))
        blocks = re.findall(r'\b_asm\s*\{[^{}]*\}', body)
        if any(re.search(r'\b(?:_emit|__emit|db|dw|dd)\b', block, re.I) for block in blocks):
            raise FormatError('inline asm in %s emits bytes; only instructions are admissible' % name)
        out.append(code[last:start] + re.sub(r'\b_asm\s*\{[^{}]*\}', ';', body))
        last = end + 1
    return ''.join(out) + code[last:]


def promotion_names(module, stubs, symbols, data=False):
    """Publics a compiled object promotes. MSC records a `static` function as a
    local PUBDEF; an unnamed static helper (no MAPSYM entry) is not a promotion
    target: its bytes lie in the anchored code contribution and are compared there."""
    if data:
        return {p['name'] for p in module['publics'] if p['segment']}
    mapsym_names = {s['name'] for seg in symbols['segments'] for s in seg.get('symbols', [])}
    return {p['name'] for p in module['publics'] if p['segment'] and module['segments'][p['segment'] - 1]['class'] == 'CODE' and p['segment'] not in stubs
            and not (p.get('local') and p['name'] not in mapsym_names)}


def check_source(source, flags, unit=None, allow_pragma_optimize=False):
    """Ordinary self-contained C under a catalogued profile; fail closed on anything else."""
    code = re.sub(r'/\*.*?\*/|//[^\n]*', '', source, flags=re.S)
    if 'TODO' in source or not code.strip():
        raise FormatError('unfinished source')
    if pack_index_bindings(code):
        # match_position is a 2-byte PACK word: a nonzero constant index reaches a
        # different PACK object and, inside a unit, allocates the wrong selector-pool
        # words. Name the object instead (tools/rebind_pack_index.py).
        raise FormatError('match_position[K] reaches another PACK object; declare and use that object')
    stripped = code
    if unit and unit.get('scaffold'):
        # A scaffolded unit may only carry `#pragma alloc_text(...)` placements
        # (stand-ins into the reserved segment, later code runs into RUNk_TEXT).
        stripped = re.sub(r'#\s*pragma\s+alloc_text\s*\(\s*(?:POOLSTUB_TEXT|RUN\d+_TEXT)\s*,[^()]*\)', '', stripped)
    if reviewed_intrinsic_source(unit, source):
        stripped = re.sub(r'(?m)^[ \t]*#\s*pragma\s+intrinsic\s*\(\s*strlen\s*\)[ \t]*$', '', stripped)
    stripped = reviewed_inline_asm(stripped)
    stripped, has_reviewed_optimize = reviewed_optimize_pragmas(stripped, allow_pragma_optimize)
    if re.search(r'\b(?:__asm|_asm|asm|_emit|__emit|incbin)\b|#\s*(?:include|pragma)', stripped, re.I):
        raise FormatError('recovered source must be self-contained ordinary C, without assembly or compiler pragmas')
    if re.search(r'\([^)]*\*[^)]*\)\s*(?:0x[0-9a-f]+|[1-9][0-9]*)', code, re.I):
        raise FormatError('literal-address pointer cast is not recoverable source')
    # Only catalogued compiler profiles are admissible; no free flag search.
    compiler_profiles.identify_profile(flags)
    return has_reviewed_optimize


def function_flags(symbol):
    card = next((c for c in cards() if c['symbol'] == symbol), None)
    if card is None:
        raise FormatError('unknown function symbol ' + symbol)
    profile = compiler_profiles.resolve(symbol)
    return profile, compiler_profiles.profile_flags(profile['name'], card['segment_name'])


def admit(label, publics, source_bytes, flags, profile, summary, verify_only, unit=None, scaffold=None, data=False,
          language='c', assembler_version=None, rework=False):
    """Compile the frozen source and admit every public, or change nothing."""
    with publication.publication_lock():
        publication.recover()
        current = read_json(ROOT / 'src/recovery.json')
        manifest = read_json(ROOT / 'build/recovered/manifest.json')
        superseded = {name: current['targets'][name] for name in publics or () if name in current['targets']}
        if superseded and unit is None and not verify_only and not rework:
            raise FormatError('already admitted; only a unit promotion may supersede recipes: ' + ', '.join(sorted(superseded)))
        verify(dict(manifest, game_objects=[g for g in manifest['game_objects'] if g['symbol'] not in superseded]),
               {k: v for k, v in current['targets'].items() if k not in superseded}, publish=False)
        ident = label + '-' + sha256(source_bytes)[:10]
        extension = '.asm' if language == 'asm' else '.c'
        destination = (ROOT / 'build/promote' / ident / ('source' + extension)) if verify_only else (ROOT / 'src/recovered' / (ident + extension))
        created = not destination.exists()
        if not created and destination.read_bytes() != source_bytes:
            raise FormatError('destination exists with different source; refusing overwrite')
        destination.parent.mkdir(parents=True, exist_ok=True)
        destination.write_bytes(source_bytes)
        try:
            if language == 'asm':
                obj, receipt = assembler.assemble_source(relative(destination), assembler_version, flags)
                assembler.validate_receipt(receipt)
            else:
                obj, receipt = compile_source(relative(destination), flags, 'msc700')
                validate_receipt(receipt)
            module = omf.parse(obj.read_bytes())
            raw = fixture('SIMANTW.EXE'); image = ne.parse(raw); symbols = mapsym.parse(fixture('SIMANTW.SYM'))
            imports = import_symbols(ROOT / 'toolchain/sdk300/WLIB/LIBW.LIB')
            # Pool scaffolding (stand-ins in the reserved segment) is never part of the promotion scope.
            stubs = [s['index'] for s in module['segments'] if s['name'] == SCAFFOLD_SEGMENT and s['class'] == 'CODE']
            names = promotion_names(module, stubs, symbols, data)
            if publics is None:
                # Data and assembly modules: the scope is the compiled object's publics.
                publics = sorted(names)
                prior = {n: current['targets'][n] for n in names if n in current['targets']}
                if prior and not verify_only:
                    if not rework:
                        raise FormatError('already admitted: ' + ', '.join(sorted(prior)))
                    if data:
                        if any(v.get('kind') != 'DATA' for v in prior.values()):
                            raise FormatError('data rework may only supersede data recipes')
                        sources = {v['source'] for v in prior.values()}
                        rest = sorted(k for k, v in current['targets'].items() if v['source'] in sources and k not in names)
                        if rest:
                            raise FormatError('data rework must replace whole earlier modules; also define: ' + ', '.join(rest))
                    elif language == 'asm':
                        if any(v.get('language') != 'asm' for v in prior.values()):
                            raise FormatError('an assembly module may only supersede assembly recipes')
                    superseded = prior
            if not names or names != set(publics):
                raise FormatError('compiled code publics differ from the promotion scope: ' + ', '.join(sorted(names ^ set(publics))))
            if stubs and not scaffold:
                raise FormatError('pool scaffolding is only admissible inside a scaffolded unit')
            inventory = {x['name']: x for x in read_json(ROOT / 'evidence/symbols/inventory.json')['symbols']}
            if data:
                if any(inventory.get(name, {}).get('kind') != 'DATA_SYMBOL' for name in names):
                    raise FormatError('data lane admits only original data symbols')
                crt = sorted(set(names) & runtime_library_publics())
                if crt:
                    raise FormatError('runtime-library data belongs to its library member, not a game data module: ' + ', '.join(crt))
            elif language == 'asm':
                review = ownership_review()
                if any(review.get(name, {}).get('class') != 'GAME_ASM' for name in names):
                    raise FormatError('assembly promotion is limited to reviewed GAME_ASM symbols')
            elif any(ownership(name, inventory.get(name, {})) != 'GAME' for name in names):
                raise FormatError('runtime/unknown ownership cannot receive game-source promotion')
            if language == 'c' and compiler_profiles.identify_profile(flags)[0] != profile['name']:
                raise FormatError('flags disagree with the resolved compiler profile')
            if data:
                targets = data_targets(module, raw, image, symbols, sorted(names))
                comparison = check_data_member(module, raw, image, symbols, imports, targets)
            else:
                targets = admission_targets(module, raw, image, symbols, sorted(names), scaffold=bool(scaffold))
                comparison = check_member(module, raw, image, symbols, imports, targets, scaffold=bool(scaffold))
            proof = dict(id=ident, publics=sorted(names), admitted=True, verify_only=verify_only, semantic_summary=summary, source=relative(destination),
                         source_identity=identity(destination), receipt=receipt, comparison=comparison, targets=targets,
                         compiler_profile=dict(profile, flags=flags) if language == 'c' else None,
                         assembler=dict(name=assembler_version, version=receipt.get('assembler_version'), flags=flags) if language == 'asm' else None,
                         language=language, unit=unit, scaffold=scaffold, superseded_recipes=superseded,
                         proof_tools={p: identity(ROOT / p) for p in PROOF_TOOLS}, created=publication.timestamp(),
                         scope='Exact readable reconstruction, not original text or filename')
            if verify_only:
                path = destination.parent / 'proof.json'
                write_json(path, proof)
                return dict(id=ident, admission='PASSED', promotion='NONE (--verify-only)', evidence=relative(path), result=comparison['result'])
            stored = ROOT / 'build/recovered' / (ident + '.obj')
            shutil.copyfile(obj, stored)
            proof_path = ROOT / 'evidence/recovery/promotions' / (ident + '.json')
            game = {r['symbol']: r for r in manifest['game_objects']}
            for name, target in targets.items():
                if language == 'asm':
                    target.update(source=relative(destination), language='asm', assembler=assembler_version,
                                  flags=flags, promotion_evidence=relative(proof_path))
                else:
                    target.update(source=relative(destination), compiler='msc700', flags=flags, profile=profile['name'],
                                  profile_evidence=profile.get('assignment'), promotion_evidence=relative(proof_path))
                if unit:
                    target['unit'] = unit
                if scaffold:
                    target['scaffold'] = scaffold
                current['targets'][name] = target
                game[name] = dict(symbol=name, object=relative(stored), identity=identity(stored), receipt=receipt)
            manifest['game_objects'] = list(game.values())
            verified = verify(manifest, current['targets'], publish=False)
            # The whole executable must still rebuild exactly from admitted
            # objects plus explicit raw debt.
            from image import build as build_image
            before = build_image(write=False)
            whole = build_image(manifest=manifest, write=False)
            if whole['status'] != 'HYBRID_EXACT':
                raise FormatError('whole-image check failed: ' + '; '.join(whole['problems'][:5]))
            if rework == 'reduce_conflicts' and whole['claim_conflicts']['bytes'] >= before['claim_conflicts']['bytes']:
                raise FormatError('already admitted; a replacement must strictly reduce double-claimed bytes (%d -> %d)'
                                  % (before['claim_conflicts']['bytes'], whole['claim_conflicts']['bytes']))
            if not data and whole['claim_conflicts']['bytes'] > before['claim_conflicts']['bytes']:
                # Two separately linked objects can never prove the same bytes:
                # an admission may not add double-claimed bytes (e.g. a unit that
                # supersedes only part of an older unit, or a function whose
                # private data an admitted object already claims). Merge into one
                # unit or rework the other side first.
                raise FormatError('admission adds double-claimed bytes (%d -> %d); merge the overlapping objects into one unit or rework the other side first; overlaps: %s'
                                  % (before['claim_conflicts']['bytes'], whole['claim_conflicts']['bytes'],
                                     '; '.join('%s / %s: %d bytes' % (t['objects'][0], t['objects'][1], t['bytes']) for t in whole['claim_conflicts'].get('top', []))))
            if data and (whole['claim_conflicts']['bytes'] > before['claim_conflicts']['bytes'] or
                         (not rework and whole['claim_conflicts']['bytes'] != before['claim_conflicts']['bytes'])):
                # Data modules may only take unowned bytes: private data of an
                # admitted object belongs to that object's unit, not a data module.
                raise FormatError('data module overlaps bytes already owned by an admitted object')
            proof['image'] = dict(status=whole['status'], owned=whole['owned'], debt_total=whole['debt_total'], claim_conflicts=whole['claim_conflicts']['bytes'])
            write_json(proof_path, proof)
            progress = {k: v for k, v in verified.items() if k not in ('game', 'runtime')}
            publication.commit(dict(zip(publication.CORE, [current, manifest, verified, progress])), ident)
            created = False
            from image import build as build_image
            build_image()
            return dict(id=ident, status='PROMOTED', symbols=sorted(names), superseded=sorted(superseded), evidence=relative(proof_path), progress=progress,
                        image=dict(owned_c=whole['owned']['C'], debt_total=whole['debt_total'], owned_delta=whole['owned']['C'] - before['owned']['C'],
                                   new_claim_conflicts=whole['claim_conflicts']['bytes'] - before['claim_conflicts']['bytes']))
        finally:
            if created and not verify_only:
                destination.unlink(missing_ok=True)


def asm_semantic_summary(text, summary=None):
    if summary and summary.strip():
        return summary.strip()
    lines = []
    for line in text.splitlines():
        value = line.strip()
        if not value:
            continue
        if value.startswith(';'):
            lines.append(value[1:].strip())
            continue
        break
    result = ' '.join(x for x in lines if x).strip()
    if not result:
        raise FormatError('state the assembly hypothesis in leading semicolon comments or with --summary')
    return result


def promote_asm_function(symbol, path, summary=None, verify_only=False, assembler_version='masm600', asm_flags=None):
    path = path.resolve()
    if path.suffix.lower() != '.asm' or not path.is_file():
        raise FormatError('assembly candidate must be an existing .asm file')
    if ownership_review().get(symbol, {}).get('class') != 'GAME_ASM':
        raise FormatError('assembly promotion is limited to reviewed GAME_ASM symbols')
    text = path.read_text(encoding='latin1')
    assembler.check_asm_source(text)
    spec = assembler.versions().get(assembler_version)
    if spec is None:
        raise FormatError('unknown or unprovisioned assembler version: ' + assembler_version)
    flags = assembler._validate_flags(spec.get('default_flags', []) if asm_flags is None else asm_flags)
    # Rework: an admitted assembly recipe whose source no longer satisfies the
    # current source rules (e.g. hard-coded linked addresses) may be replaced
    # by a compliant source for the same symbol; the old recipe is archived.
    rework = False
    existing = recipes().get(symbol)
    if existing and not verify_only:
        if existing.get('language') != 'asm':
            raise FormatError('already admitted as C; assembly rework applies only to assembly recipes')
        try:
            assembler.check_asm_source((ROOT / existing['source']).read_text(encoding='latin1'))
        except FormatError:
            rework = True
        else:
            raise FormatError('already admitted with a compliant assembly source: ' + symbol)
    return admit(symbol.lstrip('_'), [symbol], path.read_bytes(), flags, None,
                 asm_semantic_summary(text, summary), verify_only, language='asm', assembler_version=assembler_version, rework=rework)


def promote_function(symbol, path, summary=None, verify_only=False, assembler_version='masm600', asm_flags=None, steered=None):
    path = path.resolve()
    if not path.is_file():
        raise FormatError('candidate source does not exist')
    if path.suffix.lower() == '.asm':
        return promote_asm_function(symbol, path, summary, verify_only, assembler_version, asm_flags)
    profile, flags = function_flags(symbol)
    source_bytes = path.read_bytes()
    text = path.read_text()
    has_pragma_optimize = check_source(text, flags, allow_pragma_optimize=True)
    if has_pragma_optimize and not (steered and steered.strip()):
        raise FormatError('reviewed #pragma optimize requires --steered text for EXACT_STEERED provenance')
    # Rework: an isolated recipe whose admitted source fails a later source rule
    # (index-based PACK bindings) may be replaced by a compliant source.
    rework = False
    existing = recipes().get(symbol)
    if existing and not verify_only:
        if existing.get('unit') or existing.get('language') == 'asm':
            raise FormatError('already admitted; unit members are reworked through promote.py --unit')
        # Either the admitted source fails a later source rule, or the new
        # admission must strictly reduce double-claimed bytes (checked in admit).
        rework = True if pack_index_bindings((ROOT / existing['source']).read_text(encoding='latin1')) else 'reduce_conflicts'
    return admit(symbol.lstrip('_'), [symbol], source_bytes, flags, profile, semantic_summary(text, summary), verify_only, rework=rework)


def promote_unit(unit_id, reason, verify_only=False, steered=None):
    from tu_assembly import UNITS
    if not re.fullmatch(r'[A-Za-z0-9_]+', unit_id):
        raise FormatError('invalid unit id')
    spec = read_json(UNITS / unit_id / 'unit.json')
    if spec['status'] != 'COMPOSED':
        raise FormatError('unit is not composed')
    if (spec.get('last_test') or {}).get('result') not in GOOD:
        raise FormatError('unit has no exact tested result; run tools/tu_assembly.py test first')
    if identity(ROOT / spec['source']) != spec['source_identity']:
        raise FormatError('unit source changed since composition')
    if not reason.strip():
        raise FormatError('reviewed reason required')
    members = spec['members']
    import unit_owner
    component = (compiler_profiles.component_of(members[0]) or {}).get('id')
    if component and not verify_only:
        # One owner per historical object admits its canonical unit (tools/unit_owner.py).
        unit_owner.require(component)
    profiles = {compiler_profiles.resolve(m)['name'] for m in members}
    if profiles != {spec['profile']}:
        raise FormatError('unit profile disagrees with its members: ' + ', '.join(sorted(profiles)))
    scaffold = None
    if spec.get('scaffold'):
        scaffold = dict(unit=unit_id, segment=spec['scaffold']['segment'], stand_ins=[s['function'] for s in spec['scaffold']['stubs']], runs=spec['scaffold']['runs'])
        if spec['scaffold'].get('private_zero_gaps'):
            scaffold['private_zero_gaps'] = spec['scaffold']['private_zero_gaps']
    path = ROOT / spec['source']
    text = path.read_text(encoding='latin1')
    has_pragma_optimize = check_source(path.read_text(), spec['flags'], dict(spec, scaffold=scaffold), allow_pragma_optimize=True)
    if has_pragma_optimize and not (steered and steered.strip()):
        raise FormatError('reviewed #pragma optimize requires --steered text for EXACT_STEERED provenance')
    profile = compiler_profiles.resolve(members[0])
    return admit('tu_' + unit_id, members, path.read_bytes(), spec['flags'], profile, 'Unit assembly %s: %s' % (unit_id, reason), verify_only, unit=unit_id, scaffold=scaffold)


def promote_asm_module(path, summary=None, verify_only=False, assembler_version='masm600', asm_flags=None):
    """Several reviewed GAME_ASM procedures from one assembly module, admitted together."""
    path = path.resolve()
    if path.suffix.lower() != '.asm' or not path.is_file():
        raise FormatError('assembly module must be an existing .asm file')
    text = path.read_text(encoding='latin1')
    assembler.check_asm_source(text)
    spec = assembler.versions().get(assembler_version)
    if spec is None:
        raise FormatError('unknown or unprovisioned assembler version: ' + assembler_version)
    flags = assembler._validate_flags(spec.get('default_flags', []) if asm_flags is None else asm_flags)
    return admit('asmmod_' + re.sub(r'[^A-Za-z0-9_]+', '_', path.stem), None, path.read_bytes(), flags, None,
                 asm_semantic_summary(text, summary), verify_only, language='asm', assembler_version=assembler_version, rework=True)


def promote_data(path, summary=None, verify_only=False, rework=False):
    """A data-only module: initialized public data at its MAPSYM addresses."""
    path = path.resolve()
    if not path.is_file():
        raise FormatError('candidate source does not exist')
    profile = dict(compiler_profiles.catalog()['profiles'].get('baseline', {}), name='baseline', basis='DATA_MODULE', assignment=None)
    flags = compiler_profiles.profile_flags('baseline', '_TEXT')
    text = path.read_text()
    check_source(text, flags)
    # The admitted names are exactly the compiled object's publics (checked in admit).
    return admit('data_' + re.sub(r'[^A-Za-z0-9_]+', '_', path.stem), None, path.read_bytes(), flags, profile, semantic_summary(text, summary), verify_only, data=True, rework=rework)


def retire_data(source, reason, verify_only=False):
    """Remove one whole data module whose bytes another owner (e.g. a library member) now proves.

    Fail closed: the module must be data-only, the image must stay HYBRID_EXACT,
    raw debt may not grow (every retired byte stays owned) and double-claimed
    bytes must strictly fall. A retirement proof records what was removed.
    """
    if not reason.strip():
        raise FormatError('reviewed reason required')
    from image import build as build_image
    with publication.publication_lock():
        publication.recover()
        current = read_json(ROOT / 'src/recovery.json')
        manifest = read_json(ROOT / 'build/recovered/manifest.json')
        names = sorted(k for k, v in current['targets'].items() if v['source'] == source)
        if not names:
            raise FormatError('no admitted recipe uses ' + source)
        if any(current['targets'][k].get('kind') != 'DATA' for k in names):
            raise FormatError('only data modules can be retired')
        retired = {k: current['targets'].pop(k) for k in names}
        staged = dict(manifest, game_objects=[g for g in manifest['game_objects'] if g['symbol'] not in retired])
        verified = verify(staged, current['targets'], publish=False)
        before = build_image(write=False)
        whole = build_image(manifest=staged, write=False)
        if whole['status'] != 'HYBRID_EXACT':
            raise FormatError('whole-image check failed after retirement')
        if whole['debt_total'] > before['debt_total']:
            raise FormatError('retirement would turn owned bytes back into raw debt (%d -> %d)' % (before['debt_total'], whole['debt_total']))
        if whole['claim_conflicts']['bytes'] >= before['claim_conflicts']['bytes']:
            raise FormatError('retirement must strictly reduce double-claimed bytes')
        ident = 'retire_' + re.sub(r'[^A-Za-z0-9_]+', '_', Path(source).stem) + '-' + sha256(source.encode())[:10]
        proof = dict(id=ident, retired=retired, source=source, reason=reason, created=publication.timestamp(),
                     image_before=dict(debt_total=before['debt_total'], claim_conflicts=before['claim_conflicts']['bytes']),
                     image_after=dict(debt_total=whole['debt_total'], claim_conflicts=whole['claim_conflicts']['bytes']),
                     scope='Removed a data module whose bytes another admitted owner proves; the retired source stays in src/recovered for history')
        if verify_only:
            return dict(id=ident, retirement='PASSED', promotion='NONE (--verify-only)', retired=names)
        proof_path = ROOT / 'evidence/recovery/promotions' / (ident + '.json')
        write_json(proof_path, proof)
        progress = {k: v for k, v in verified.items() if k not in ('game', 'runtime')}
        publication.commit(dict(zip(publication.CORE, [current, staged, verified, progress])), ident)
        build_image()
        return dict(id=ident, status='RETIRED', retired=names, evidence=relative(proof_path),
                    claim_conflicts=whole['claim_conflicts']['bytes'], debt_total=whole['debt_total'])


def promote_resources(verify_only=False):
    """Freshly compile the tracked RC source and admit only exact payload ranges."""
    import resources
    from image import build as build_image

    with publication.publication_lock():
        publication.recover()
        current = read_json(ROOT / 'src/recovery.json')
        manifest = read_json(ROOT / 'build/recovered/manifest.json')
        verified = read_json(ROOT / 'build/recovery/verified-objects.json')
        progress = read_json(ROOT / 'docs/progress.json')
        before = build_image(write=False, recovery=current)

        proof = resources.compile_payload_admission(store=not verify_only)
        proof['created'] = publication.timestamp()
        if verify_only:
            proof_path = ROOT / 'build/resources/verify-only' / (proof['id'] + '.json')
        else:
            proof_path = ROOT / 'evidence/recovery/promotions' / (proof['id'] + '.json')
        proof_path.parent.mkdir(parents=True, exist_ok=True)
        if proof_path.exists() and not verify_only:
            old = read_json(proof_path)
            old_core = {k: v for k, v in old.items() if k != 'created'}
            new_core = {k: v for k, v in proof.items() if k != 'created'}
            if old_core != new_core:
                raise FormatError('resource promotion proof already exists with different evidence')
            proof = old
        else:
            write_json(proof_path, proof)

        staged = dict(current)
        staged['resources'] = {
            'id': proof['id'],
            'promotion_evidence': relative(proof_path),
            'proof_identity': identity(proof_path),
            'source_identity': proof['source'],
            'rc_toolchain_identity': proof['rc_toolchain'],
        }
        whole = build_image(write=False, recovery=staged)
        if whole['status'] != 'HYBRID_EXACT':
            raise FormatError('whole-image check failed after resource admission: ' + '; '.join(whole['problems'][:5]))
        if proof.get('table_credit') is not False or whole['owned'].get('RESOURCES', 0) == 0:
            raise FormatError('resource admission did not prove payload bytes without table credit')

        if verify_only:
            return dict(id=proof['id'], admission='PASSED', promotion='NONE (--verify-only)',
                        evidence=relative(proof_path), resources=proof['resource_count'],
                        image=dict(status=whole['status'], owned=whole['owned'], debt=whole['debt'],
                                   debt_total=whole['debt_total']))

        publication.commit(dict(zip(publication.CORE, [staged, manifest, verified, progress])), proof['id'])
        rebuilt = build_image()
        return dict(id=proof['id'], status='PROMOTED', evidence=relative(proof_path),
                    resources=proof['resource_count'], table_credit=False,
                    image_before=dict(owned=before['owned'], debt=before['debt'], debt_total=before['debt_total']),
                    image_after=dict(status=rebuilt['status'], owned=rebuilt['owned'], debt=rebuilt['debt'],
                                     debt_total=rebuilt['debt_total']))


def promote_link(verify_only=False):
    """Freshly run pinned LINK 5.30 and admit only the five complete regions."""
    from image import build as build_image

    with publication.publication_lock():
        publication.recover()
        current = read_json(ROOT / 'src/recovery.json')
        manifest = read_json(ROOT / 'build/recovered/manifest.json')
        verified = read_json(ROOT / 'build/recovery/verified-objects.json')
        progress = read_json(ROOT / 'docs/progress.json')
        before = build_image(write=False, recovery=current)

        proof = link_lane.compile_admission(store=not verify_only)
        proof['created'] = publication.timestamp()
        if verify_only:
            proof_path = ROOT / 'build/link/verify-only' / (proof['id'] + '.json')
        else:
            proof_path = ROOT / 'evidence/recovery/promotions' / (proof['id'] + '.json')
        proof_path.parent.mkdir(parents=True, exist_ok=True)
        if proof_path.exists() and not verify_only:
            old = read_json(proof_path)
            stable = ('id', 'scope', 'sources', 'toolchain', 'output', 'regions', 'uncredited_region_kinds')
            if any(old.get(key) != proof.get(key) for key in stable):
                raise FormatError('LINK promotion proof already exists with different evidence')
            proof = old
        else:
            write_json(proof_path, proof)

        staged = dict(current)
        staged['link'] = {
            'id': proof['id'],
            'promotion_evidence': relative(proof_path),
            'proof_identity': identity(proof_path),
            'source_identity': proof['sources'],
            'toolchain_identity': proof['toolchain'],
        }
        whole = build_image(write=False, recovery=staged)
        region_bytes = sum(row['oracle_range']['size'] for row in proof['regions'])
        if whole['status'] != 'HYBRID_EXACT':
            raise FormatError('whole-image check failed after LINK admission: ' + '; '.join(whole['problems'][:5]))
        if region_bytes != 1195 or whole['owned'].get('LINK', 0) < region_bytes:
            raise FormatError('LINK admission did not prove exactly the five reviewed complete regions')

        if verify_only:
            return dict(id=proof['id'], admission='PASSED', promotion='NONE (--verify-only)',
                        evidence=relative(proof_path), regions=len(proof['regions']), bytes=region_bytes,
                        image=dict(status=whole['status'], owned=whole['owned'], debt=whole['debt'],
                                   debt_total=whole['debt_total']))

        publication.commit(dict(zip(publication.CORE, [staged, manifest, verified, progress])), proof['id'])
        rebuilt = build_image()
        return dict(id=proof['id'], status='PROMOTED', evidence=relative(proof_path),
                    regions=len(proof['regions']), bytes=region_bytes,
                    image_before=dict(owned=before['owned'], debt=before['debt'], debt_total=before['debt_total']),
                    image_after=dict(status=rebuilt['status'], owned=rebuilt['owned'], debt=rebuilt['debt'],
                                     debt_total=rebuilt['debt_total']))


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('symbol', nargs='?')
    ap.add_argument('source', nargs='?')
    ap.add_argument('--summary')
    ap.add_argument('--unit')
    ap.add_argument('--data', help='data-only module: initialized public data definitions')
    ap.add_argument('--rework', action='store_true', help='with --data: replace whole earlier data modules (claim conflicts may not increase)')
    ap.add_argument('--asm-module', help='assembly module whose reviewed GAME_ASM procedures are admitted together')
    ap.add_argument('--reason', default='')
    ap.add_argument('--verify-only', action='store_true')
    ap.add_argument('--assembler', default='masm600', help='authentic MASM version for .asm candidates')
    ap.add_argument('--asm-flag', action='append', help='assembler option for .asm candidates; may be repeated')
    ap.add_argument('--recover', action='store_true')
    ap.add_argument('--retire-data', help='remove the whole data module with this recipe source (bytes must stay owned by someone else)')
    ap.add_argument('--resources', action='store_true', help='freshly compile and admit exact resource payloads with pinned RC 3.00')
    ap.add_argument('--link', action='store_true', help='freshly run LINK 5.30 and admit the five exact complete NE regions')
    ap.add_argument('--steered', metavar='TEXT', help='source provenance EXACT_STEERED: name every construct that exists to steer MSC 7.00 '
                    '(no runtime effect) and why; the binary proof is unchanged (docs/factory.md, "Source provenance")')
    args = ap.parse_args()
    if args.steered is not None and not args.steered.strip():
        ap.error('--steered needs a description of the steering constructs')
    if args.link:
        result = promote_link(args.verify_only)
    elif args.resources:
        result = promote_resources(args.verify_only)
    elif args.retire_data:
        result = retire_data(args.retire_data, args.reason, args.verify_only)
    elif args.recover:
        with publication.publication_lock():
            result = publication.recover()
    elif args.data:
        from pathlib import Path
        result = promote_data(Path(args.data), args.summary, args.verify_only, args.rework)
    elif args.asm_module:
        from pathlib import Path
        result = promote_asm_module(Path(args.asm_module), args.summary, args.verify_only, args.assembler, args.asm_flag)
    elif args.unit:
        result = promote_unit(args.unit, args.reason, args.verify_only, args.steered)
    elif args.symbol and args.source:
        from pathlib import Path
        result = promote_function(args.symbol, Path(args.source), args.summary, args.verify_only, args.assembler, args.asm_flag, args.steered)
    else:
        ap.error('give SYMBOL SOURCE, --unit UNIT or --recover')
    if isinstance(result, dict) and result.get('status') == 'PROMOTED' and result.get('symbols'):
        result['provenance'] = record_provenance(result['symbols'], result['id'], args.steered)
    print(json.dumps(result, indent=2))


PROVENANCE = ROOT / 'evidence/recovery/provenance.json'


def record_provenance(symbols, admission, steered=None):
    """Source provenance of an exact admission. Both classes are binary matched; EXACT_STEERED only says
    that some source constructs exist to steer MSC 7.00 and the historical spelling is uncertain.
    A later natural admission of the same symbol clears the steered entry."""
    with publication.publication_lock():
        data = read_json(PROVENANCE) if PROVENANCE.exists() else dict(version=1, entries={})
        for name in symbols:
            if steered:
                data['entries'][name] = dict(provenance='EXACT_STEERED', steering=steered.strip(), admission=admission,
                                             recorded=publication.timestamp())
            else:
                data['entries'].pop(name, None)
        write_json(PROVENANCE, data)
    return 'EXACT_STEERED' if steered else 'EXACT_NATURAL'


if __name__ == '__main__':
    try:
        main()
    except (FormatError, FileNotFoundError) as exc:
        raise SystemExit('ERROR: ' + str(exc))
