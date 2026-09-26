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

GOOD = ('CONFIRMED_MEMBER', 'STRONGLY_SUPPORTED_MEMBER')
PROOF_TOOLS = ['tools/matcher.py', 'tools/library_match.py', 'tools/recovery_gate.py', 'tools/verify_recovery.py', 'tools/compiler.py', 'tools/assembler.py',
               'tools/cfg_solver.py', 'tools/ne.py', 'tools/omf.py', 'tools/mapsym.py', 'tools/promote.py', 'tools/publication.py',
               'layout/toolchain.json', 'layout/fixtures.json', 'layout/compiler-profiles.json', 'layout/runtime-ownership.json']


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


def check_source(source, flags, unit=None):
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
    if re.search(r'\b(?:__asm|_asm|asm|_emit|__emit|incbin)\b|#\s*(?:include|pragma)', stripped, re.I):
        raise FormatError('recovered source must be self-contained ordinary C, without assembly or compiler pragmas')
    if re.search(r'\([^)]*\*[^)]*\)\s*(?:0x[0-9a-f]+|[1-9][0-9]*)', code, re.I):
        raise FormatError('literal-address pointer cast is not recoverable source')
    # Only catalogued compiler profiles are admissible; no free flag search.
    compiler_profiles.identify_profile(flags)


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
            if data:
                names = {p['name'] for p in module['publics'] if p['segment']}
            else:
                names = {p['name'] for p in module['publics'] if p['segment'] and module['segments'][p['segment'] - 1]['class'] == 'CODE' and p['segment'] not in stubs}
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


def promote_function(symbol, path, summary=None, verify_only=False, assembler_version='masm600', asm_flags=None):
    path = path.resolve()
    if not path.is_file():
        raise FormatError('candidate source does not exist')
    if path.suffix.lower() == '.asm':
        return promote_asm_function(symbol, path, summary, verify_only, assembler_version, asm_flags)
    profile, flags = function_flags(symbol)
    source_bytes = path.read_bytes()
    text = path.read_text()
    check_source(text, flags)
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


def promote_unit(unit_id, reason, verify_only=False):
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
    check_source(path.read_text(), spec['flags'], dict(spec, scaffold=scaffold))
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
    args = ap.parse_args()
    if args.retire_data:
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
        result = promote_unit(args.unit, args.reason, args.verify_only)
    elif args.symbol and args.source:
        from pathlib import Path
        result = promote_function(args.symbol, Path(args.source), args.summary, args.verify_only, args.assembler, args.asm_flag)
    else:
        ap.error('give SYMBOL SOURCE, --unit UNIT or --recover')
    print(json.dumps(result, indent=2))


if __name__ == '__main__':
    try:
        main()
    except (FormatError, FileNotFoundError) as exc:
        raise SystemExit('ERROR: ' + str(exc))
