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
from common import ROOT, FormatError, identity, read_json, recipes, relative, write_json
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


def search(symbol, files=(), template=None, meta=None, note=None, full=False):
    from promote import check_source, function_flags
    began = time.perf_counter()
    profile, flags = function_flags(symbol)
    stamp = datetime.now(timezone.utc).strftime('%Y%m%dT%H%M%S') + '-%d' % os.getpid()
    out = ROOT / 'build/search' / symbol.lstrip('_') / stamp
    labels, warnings = [], {}
    if template:
        spec = dict(read_json(template), symbol=symbol, compiler='msc700', flags=flags, publics=[symbol])
        spec.setdefault('max_candidates', 10000)
    else:
        if not files:
            raise FormatError('give at least one candidate file or --template')
        sources = []
        for name in files:
            path = Path(name).resolve()
            if not path.is_file():
                raise FormatError('candidate does not exist: ' + name)
            text = path.read_text()
            sources.append(text)
            labels.append(name)
            try:
                check_source(text, flags)
            except FormatError as exc:
                warnings[name] = 'promotion would reject this source: ' + str(exc)
        spec = dict(symbol=symbol, compiler='msc700', flags=flags, publics=[symbol], sources=sources, max_candidates=len(sources))
    report = run(spec, relative(out), cache=True)
    rows = []
    for row in report['results']:
        label = labels[row['choices']['input']] if labels else row['choices']
        rows.append((row, summary_row(row, label, out)))
    admitted = symbol in recipes()
    improved = False
    if not admitted:
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
                            aligned_asm=diagnostic.get('aligned_asm', []) if full else focused_alignment(diagnostic.get('aligned_asm', []))),
                  exact=exact, draft_ledger='improved' if improved else 'unchanged',
                  report=relative(out / 'results.json'), seconds=round(time.perf_counter() - began, 2))
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
    args = ap.parse_args()
    from contextlib import redirect_stdout
    with redirect_stdout(sys.stderr):
        result = search(args.symbol, args.files, args.template, args.meta, args.note, args.full)
    print(json.dumps(result, indent=2))


if __name__ == '__main__':
    try:
        main()
    except (FormatError, FileNotFoundError) as exc:
        raise SystemExit('ERROR: ' + str(exc))
