"""Compile and compare C hypotheses for one function; never changes canonical state.

    python tools/search.py SYMBOL a.c [b.c ...] [--meta round.json] [--note TEXT] [--full]
    python tools/search.py SYMBOL --template spec.json      # controlled equivalence classes

Every file is compiled with authentic MSC 7.00 under the symbol's catalogued
object profile and checked by the strict member matcher, with an aligned
instruction diagnostic. There is no attempt budget, eligibility gate or task
state. Output lives in ignored build/search/SYMBOL/; the best readable draft is
kept durably in evidence/recovery/drafts/. Only promote.py admits anything.
"""
import argparse
import json
import os
import sys
import time
from datetime import datetime, timezone
from pathlib import Path
from common import ROOT, FormatError, fixture, identity, ownership_review, read_json, recipes, relative, write_json
from codegen_grinder import GOOD, run
import drafts


def focused_alignment(rows, limit=60, radius=2):
    """Keep the opening context and mismatch windows from across the member."""
    if len(rows) <= limit:
        return rows
    selected = set(range(min(8, len(rows))))
    for i, row in enumerate(rows):
        if row.get('differences'):
            selected.update(range(max(0, i - radius), min(len(rows), i + radius + 1)))
    # Preserve the first occurrence of each discrepancy when the budget is
    # tight, then sample late windows so a long prologue cannot hide the tail.
    if len(selected) > limit:
        anchors = [i for i, row in enumerate(rows) if row.get('differences')]
        chosen = set(range(min(6, len(rows))))
        if anchors:
            slots = min(limit - len(chosen), len(anchors))
            for n in range(slots):
                chosen.add(anchors[n * (len(anchors) - 1) // max(1, slots - 1)])
        selected = chosen
    return [dict(rows[i], alignment_index=i) for i in sorted(selected)[:limit]]


def summary_row(row, label, out):
    from tu_assembly import body_exact
    c = row['comparison']
    d = c.get('diagnostic') or {}
    return dict(input=label, result=c.get('result'), exact_body=body_exact(c) if d else False,
                opcodes='%s/%s' % (d.get('opcode_matches'), d.get('opcode_total')) if d else None,
                bytes='%s/%s' % (d.get('candidate_bytes'), d.get('target_bytes')) if d else None,
                literal='%s/%s' % (c.get('literal_equal'), c.get('literal_compared')), fixups='%s/%s' % (c.get('fixups_equal'), c.get('fixups_total')),
                register_differences=d.get('register_only_differences'), branch_differences=d.get('branch_target_differences'),
                stack_differences=d.get('stack_local_differences'), immediate_differences=d.get('immediate_differences'),
                memory_differences=d.get('memory_operand_differences'), first_structural_difference=d.get('first_structural_difference'),
                issues=(c.get('issues') or [])[:4], object=(row['receipt'].get('object_identity') or {}).get('sha256', '')[:12] or None,
                diff=relative(out / ('candidate%04d.diff.txt' % row['candidate'])) if d else None)


def output_history(symbol):
    """Earlier searches of SYMBOL: first input that produced each object, and best opcode score per round."""
    log = ROOT / 'build/search' / symbol.lstrip('_') / 'history.jsonl'
    seen, bests = {}, []
    if not log.is_file():
        return seen, bests
    for line in log.read_text(encoding='utf-8').splitlines():
        try:
            rows = json.loads(line).get('rows') or []
        except ValueError:
            continue
        scores = []
        for row in rows:
            if row.get('object'):
                seen.setdefault(row['object'], row['input'])
            try:
                scores.append(int(str(row.get('opcodes')).split('/')[0]))
            except ValueError:
                pass
        if scores:
            bests.append(max(scores))
    return seen, bests


def input_label(value):
    """A hashable, readable label for a candidate input (a path, or a template axis choice dict)."""
    return value if isinstance(value, str) else json.dumps(value, sort_keys=True)


def effective_output(rows, seen, bests):
    """Group candidates by produced object: edits that do not reach the compiler's output are visible at once."""
    first, repeated = {k: input_label(v) for k, v in seen.items()}, {}
    for _, s in rows:
        label = input_label(s['input'])
        if s.get('object') and s['object'] in first:
            earlier = first[s['object']]
            repeated[label] = 'an earlier run of this file' if earlier == label else earlier
        elif s.get('object'):
            first[s['object']] = label
    scores = []
    for _, s in rows:
        try:
            scores.append(int(str(s.get('opcodes')).split('/')[0]))
        except ValueError:
            pass
    history = bests + ([max(scores)] if scores else [])
    flat = 0
    if history:
        top = max(history)
        flat = len(history) - 1 - min(i for i, v in enumerate(history) if v == top)
    return dict(distinct_outputs=len({s['object'] for _, s in rows if s.get('object')}), candidates=len(rows),
                same_output_as=repeated, rounds_since_best_opcodes_improved=flat,
                hint='candidates listed in same_output_as compiled to an object already produced by the named earlier input; '
                     'their source differences never reach the output' if repeated else None)


def search_asm(symbol, files, meta=None, note=None, full=False, assembler_version='masm600', asm_flags=None):
    import assembler
    import mapsym
    import ne
    import omf
    from library_match import compare_member, import_symbols
    from recovery_gate import admission_targets, check_member
    began = time.perf_counter()
    review = ownership_review()
    if review.get(symbol, {}).get('class') != 'GAME_ASM':
        raise FormatError('assembly search is limited to reviewed GAME_ASM symbols')
    spec = assembler.versions().get(assembler_version)
    if spec is None:
        raise FormatError('unknown or unprovisioned assembler version: ' + assembler_version)
    flags = assembler._validate_flags(spec.get('default_flags', []) if asm_flags is None else asm_flags)
    stamp = datetime.now(timezone.utc).strftime('%Y%m%dT%H%M%S') + '-%d' % os.getpid()
    out = ROOT / 'build/search' / symbol.lstrip('_') / stamp
    out.mkdir(parents=True, exist_ok=True)
    raw = fixture('SIMANTW.EXE'); image = ne.parse(raw); symbols = mapsym.parse(fixture('SIMANTW.SYM'))
    imports = import_symbols(ROOT / 'toolchain/sdk300/WLIB/LIBW.LIB')
    rows = []
    for index, name in enumerate(files):
        path = Path(name).resolve()
        if path.suffix.lower() != '.asm':
            raise FormatError('ASM search accepts only .asm candidates; do not mix source languages')
        snapshot = out / ('candidate%04d.asm' % index)
        if not path.is_file():
            raise FormatError('candidate does not exist: ' + name)
        text = path.read_text(encoding='latin1')
        snapshot.write_text(text, encoding='latin1')
        row = dict(candidate=index, input=name, comparison=None, receipt=None, issues=[])
        try:
            assembler.check_asm_source(text)
            obj, receipt = assembler.assemble_source(relative(snapshot), assembler_version, flags)
            row['receipt'] = receipt
            module = omf.parse(obj.read_bytes())
            comparison = compare_member(module, raw, image, symbols, imports)
            if not comparison:
                comparison = dict(result='UNPLACED_MEMBER', issues=['no unique MAPSYM public anchor'])
            if comparison.get('result') in ('CONFIRMED_MEMBER', 'STRONGLY_SUPPORTED_MEMBER'):
                targets = admission_targets(module, raw, image, symbols, [symbol])
                comparison = check_member(module, raw, image, symbols, imports, targets)
            row['comparison'] = comparison
            if comparison.get('result') in ('CONFIRMED_MEMBER', 'STRONGLY_SUPPORTED_MEMBER'):
                from codegen_diff import diagnose, render
                comparison['diagnostic'] = diagnose(module, raw, image, symbols, symbol, comparison)
                (out / ('candidate%04d.diff.txt' % index)).write_text(render(comparison['diagnostic']), encoding='utf-8')
        except FormatError as exc:
            row['comparison'] = dict(result='ASM_REJECTED', issues=[str(exc)])
            row['issues'] = [str(exc)]
        rows.append(row)
    summaries = []
    for row in rows:
        comparison = row['comparison'] or {}
        diagnostic = comparison.get('diagnostic') or {}
        summaries.append(dict(input=row['input'], result=comparison.get('result'),
                              bytes='%s/%s' % (comparison.get('literal_equal'), comparison.get('literal_compared')),
                              fixups='%s/%s' % (comparison.get('fixups_equal'), comparison.get('fixups_total')),
                              object=((row.get('receipt') or {}).get('object_identity') or {}).get('sha256'),
                              issues=(comparison.get('issues') or [])[:4],
                              aligned_asm=diagnostic.get('aligned_asm', []) if full else focused_alignment(diagnostic.get('aligned_asm', []))))
    exact = [row['input'] for row in rows if row['comparison'] and row['comparison'].get('result') in ('CONFIRMED_MEMBER', 'STRONGLY_SUPPORTED_MEMBER')]
    if note:
        drafts.note(symbol, note, origin=relative(out))
    report = dict(symbol=symbol, language='asm', assembler=assembler_version, assembler_version=spec['display_version'],
                  flags=flags, candidates=len(rows), ranking=summaries, exact=exact,
                  report=relative(out / 'results.json'), seconds=round(time.perf_counter() - began, 2),
                  promotion='NONE: promote.py must freshly assemble and run publication gates')
    if exact:
        report['next'] = 'python tools/promote.py %s %s --assembler %s' % (symbol, exact[0], assembler_version)
    write_json(out / 'results.json', dict(spec=dict(symbol=symbol, language='asm', assembler=assembler_version, flags=flags,
                                                   sources=[relative(Path(x).resolve()) for x in files]), results=rows, summary=report))
    history = dict(time=stamp, meta=read_json(meta) if meta else None, note=note, report=report['report'],
                   rows=[dict(input=r['input'], result=(r['comparison'] or {}).get('result'),
                              object=((r.get('receipt') or {}).get('object_identity') or {}).get('sha256')) for r in rows])
    history_path = ROOT / 'build/search' / symbol.lstrip('_') / 'history.jsonl'
    history_path.parent.mkdir(parents=True, exist_ok=True)
    with history_path.open('a', encoding='utf-8') as stream:
        stream.write(json.dumps(history) + '\n')
    return report


def search(symbol, files=(), template=None, meta=None, note=None, full=False, assembler_version='masm600', asm_flags=None, frame=False, pool=False):
    from promote import check_source, function_flags
    if not files and not template and note:
        # A finding without a new candidate: record it durably, compile nothing.
        drafts.note(symbol, note, origin='search.py --note')
        return dict(symbol=symbol, note_recorded=True, candidates=0)
    if files and any(Path(name).suffix.lower() == '.asm' for name in files):
        if template:
            raise FormatError('ASM candidates do not use C template batches')
        if pool:
            raise FormatError('--pool is available for C candidates only')
        return search_asm(symbol, files, meta, note, full, assembler_version, asm_flags)
    if pool and template:
        raise FormatError('--pool requires explicit C candidate files')
    began = time.perf_counter()
    profile, flags = function_flags(symbol)
    stamp = datetime.now(timezone.utc).strftime('%Y%m%dT%H%M%S') + '-%d' % os.getpid()
    out = ROOT / 'build/search' / symbol.lstrip('_') / stamp
    labels, warnings, source_snapshots = [], {}, []
    pool_info = None
    pool_infos = []
    if template:
        spec = dict(read_json(template), symbol=symbol, compiler='msc700', flags=flags, publics=[symbol])
        spec.setdefault('max_candidates', 10000)
    else:
        if not files:
            raise FormatError('give at least one candidate file or --template')
        sources = []
        if pool:
            from pool_search import apply_pool_prefix
            out.mkdir(parents=True, exist_ok=True)
        for index, name in enumerate(files):
            path = Path(name).resolve()
            if not path.is_file():
                raise FormatError('candidate does not exist: ' + name)
            text = path.read_text()
            if pool:
                derived, current_pool_info = apply_pool_prefix(symbol, text)
                if pool_info is None:
                    pool_info = current_pool_info
                pool_infos.append(current_pool_info)
                snapshot = out / ('input%04d.c' % index)
                snapshot.write_text(text, encoding='latin1')
                source_snapshots.append(snapshot)
                sources.append(derived)
            else:
                source_snapshots.append(path)
                sources.append(text)
            labels.append(name)
            try:
                check_source(text, flags)
            except FormatError as exc:
                warnings[name] = 'promotion would reject this source: ' + str(exc)
        spec = dict(symbol=symbol, compiler='msc700', flags=flags, publics=[symbol], sources=sources, max_candidates=len(sources))
        if pool:
            spec['pool_prefix'] = pool_info
            spec['pool_prefixes'] = [dict(input=labels[i], **info)
                                     for i, info in enumerate(pool_infos)]
    seen, bests = output_history(symbol)
    report = run(spec, relative(out), cache=True)
    rows = []
    for row in report['results']:
        label = labels[row['choices']['input']] if labels else row['choices']
        rows.append((row, summary_row(row, label, out)))
    admitted = symbol in recipes()
    improved = False
    if not admitted and not pool:
        for row, _ in rows:
            if row['comparison'].get('diagnostic'):
                improved = drafts.store(symbol, out / ('candidate%04d.c' % row['candidate']), row['comparison'], relative(out / 'results.json'), flags) or improved
    if note:
        drafts.note(symbol, note, origin=relative(out))
    best, best_summary = rows[0]
    diagnostic = best['comparison'].get('diagnostic') or {}
    exact = [s['input'] for r, s in rows if r['comparison'].get('result') in GOOD]
    result = dict(symbol=symbol, profile=profile['name'], flags=flags, candidates=len(rows), cache=report['cache'],
                  ranking=[s for _, s in rows] if full or len(rows) <= 12 else [s for _, s in rows[:12]],
                  best=dict(best_summary, compiler_log=best['receipt']['stdout'][-1500:] if best['comparison'].get('result') == 'COMPILE_FAILED' else None,
                            unresolved_member_obligations=diagnostic.get('unresolved_member_obligations'),
                            categories=diagnostic.get('categories'),
                            branch_destinations=diagnostic.get('branch_destinations'),
                            aligned_asm=diagnostic.get('aligned_asm', []) if full else focused_alignment(diagnostic.get('aligned_asm', []))),
                  exact=exact, effective_output=effective_output(rows, seen, bests), draft_ledger='improved' if improved else 'unchanged',
                  report=relative(out / 'results.json'), seconds=round(time.perf_counter() - began, 2))
    if pool:
        result['pool_prefix'] = pool_info
        result['pool_prefixes'] = [dict(input=labels[i], **info)
                                   for i, info in enumerate(pool_infos)]
        result['pool_prefix_applied'] = sum(bool(info.get('applied')) for info in pool_infos)
        result['draft_ledger'] = 'unchanged (pool-aware diagnostic context)'
    if frame and best['comparison'].get('result') != 'COMPILE_FAILED' and best['receipt'].get('object'):
        # Diagnostic only: named-local homes from a /Zi recompile (code must be identical).
        from common import cards
        from frame_map import frame_report
        card = next(c for c in cards() if c['symbol'] == symbol)
        result['best']['frame'] = frame_report(symbol, relative(out / ('candidate%04d.c' % best['candidate'])), flags,
                                               ROOT / best['receipt']['object'], card['disassembly'])
    if warnings:
        result['source_warnings'] = warnings
    if admitted:
        result['note'] = 'already admitted; this run is a regression/diagnostic comparison only'
    elif exact:
        result['next'] = 'python tools/promote.py %s %s' % (symbol, exact[0] if labels else '<file>')
    history = dict(time=stamp, meta=read_json(meta) if meta else None, note=note, report=result['report'],
                   rows=[{k: s[k] for k in ('input', 'result', 'exact_body', 'opcodes', 'bytes', 'fixups', 'object')} for _, s in rows])
    log = ROOT / 'build/search' / symbol.lstrip('_') / 'history.jsonl'
    log.parent.mkdir(parents=True, exist_ok=True)
    with log.open('a', encoding='utf-8') as stream:
        stream.write(json.dumps(history) + '\n')
    return result


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('symbol')
    ap.add_argument('files', nargs='*')
    ap.add_argument('--template', help='codegen_grinder spec with template/axes for controlled equivalence classes')
    ap.add_argument('--meta', help='JSON describing the round: family, prediction, falsifier')
    ap.add_argument('--note', help='durable free-text finding for this function (kept in the draft ledger)')
    ap.add_argument('--full', action='store_true', help='complete ranking and aligned assembly')
    ap.add_argument('--assembler', default='masm600', help='authentic MASM version for .asm candidates')
    ap.add_argument('--asm-flag', action='append', help='assembler option for .asm candidates; may be repeated')
    ap.add_argument('--frame', action='store_true', help='diagnostic frame map of the best candidate: named-local BP homes/registers (CodeView via /Zi) versus the target frame')
    ap.add_argument('--pool', action='store_true', help='prepend component selector-pool stand-ins in POOLSTUB_TEXT before compiling C candidates')
    args = ap.parse_args()
    from contextlib import redirect_stdout
    with redirect_stdout(sys.stderr):
        result = search(args.symbol, args.files, args.template, args.meta, args.note, args.full, args.assembler, args.asm_flag, args.frame, args.pool)
    print(json.dumps(result, indent=2))


if __name__ == '__main__':
    try:
        main()
    except (FormatError, FileNotFoundError) as exc:
        raise SystemExit('ERROR: ' + str(exc))
