"""Supervisor-managed background queue for long permuter searches (permuter.py itself is unchanged).

    python tools/permuter_queue.py plan [--limit N]             # candidates from triage, with the mutations to use
    python tools/permuter_queue.py enqueue [--limit N] [--symbols A,B]
    python tools/permuter_queue.py run [--budget-minutes 120] [--per-target-seconds 900] [--parallel 2]
    python tools/permuter_queue.py report                         # only meaningful improvements and exact winners
    python tools/permuter_queue.py backfill                       # import earlier build/permuter runs as attempts

Candidates come from tools/triage.py: near-exact functions (every or nearly every opcode
matched), not placement-only, not parked without a reopen, whose remaining residue is an
allocation / home / expression choice that the structural mutations can move. A target is
skipped when two earlier permuter runs found no gain and no shared component (permuter,
matcher, profiles, facts ...) changed since. Mutation families that had NO effect on the
target, or that the fact register FALSIFIED as causes (declaration order, `register`), are
left out via --only. Every run appends a PERMUTER_SEARCH attempt record; exact winners are
reported with the permuter's provenance class and still go through promote.py.
"""
import argparse
import json
import subprocess
import sys
import time
from datetime import datetime, timezone
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from common import ROOT, FormatError, read_json, relative, write_json
import attempts
import shared_state

QUEUE = ROOT / 'build/permuter-queue/queue.json'
PERMUTER_OUT = ROOT / 'build/permuter'

MUTATION_FAMILY = {
    'register_toggle': 'REGISTER_HINT', 'decl_axis': 'DECLARATION_ORDER',
    'sink_decl': 'LOCAL_LIFETIME', 'hoist_decl': 'LOCAL_LIFETIME', 'split_var': 'LOCAL_LIFETIME', 'merge_vars': 'LOCAL_LIFETIME',
    'param_copy': 'LOCAL_LIFETIME',
    'inline_temp': 'CSE_SUBEXPRESSION', 'introduce_temp': 'CSE_SUBEXPRESSION', 'inline_temp_multi': 'CSE_SUBEXPRESSION',
    'for_to_while': 'LOOP_STRUCTURE', 'while_to_for': 'LOOP_STRUCTURE', 'while_to_dowhile': 'LOOP_STRUCTURE',
    'dowhile_to_while': 'LOOP_STRUCTURE', 'loop_interchange': 'LOOP_STRUCTURE', 'hoist_invariant': 'LOOP_STRUCTURE',
    'sink_invariant': 'LOOP_STRUCTURE',
    'invert_if': 'CFG_STRUCTURE', 'else_layout': 'CFG_STRUCTURE', 'return_layout': 'CFG_STRUCTURE', 'switch_reorder': 'CFG_STRUCTURE',
    'continue_else': 'CFG_STRUCTURE', 'assign_in_cond': 'CFG_STRUCTURE', 'stmt_swap': 'CFG_STRUCTURE',
    'reorder_independent_calls': 'CFG_STRUCTURE',
    'swap_commutative': 'EXPRESSION_SHAPE', 'mirror_comparison': 'EXPRESSION_SHAPE', 'demorgan': 'EXPRESSION_SHAPE',
    'cond_zero': 'EXPRESSION_SHAPE', 'incdec_style': 'EXPRESSION_SHAPE', 'compound_assign': 'EXPRESSION_SHAPE',
    'index_pointer': 'EXPRESSION_SHAPE', 'split_merge_and': 'EXPRESSION_SHAPE', 'ternary': 'EXPRESSION_SHAPE',
    'chain_assign': 'EXPRESSION_SHAPE', 'type_change': 'TYPE', 'const_bound': 'TYPE',
}
# Families the fact register FALSIFIED as causes of allocation/home residues (MSC7-F7/F8, MSC7-R13).
GLOBALLY_FALSIFIED = {'REGISTER_HINT', 'DECLARATION_ORDER'}
QUEUE_CLASSES = ('REGISTER_ALLOCATION', 'HOME_ORDER', 'EXPRESSION_SHAPE', 'FRAME_SIZE', 'CFG_STRUCTURE', 'FAR_POINTER_LIFETIME')
MIN_RATIO = 0.9


def now():
    return datetime.now(timezone.utc).strftime('%Y-%m-%dT%H:%M:%SZ')


def mutation_names():
    import permuter_mutations
    return [k for k, (_, _, safe) in permuter_mutations.MUTATIONS.items() if safe]


def select_mutations(fam_summary):
    """Safe mutations minus globally falsified families and families with no effect on this target."""
    dead = set(GLOBALLY_FALSIFIED)
    dead.update(f for f, s in fam_summary.items() if s['verdict'] == 'NO_EFFECT' and not s['stale_since'])
    return [m for m in mutation_names() if MUTATION_FAMILY.get(m, 'OTHER') not in dead], sorted(dead)


def mutations_changed_at():
    """Commit time of the latest permuter/mutation-catalogue change (backfilled runs carry no fingerprint)."""
    proc = subprocess.run(['git', 'log', '-1', '--format=%cI', '--', 'tools/permuter_mutations.py', 'tools/permuter.py'],
                          cwd=ROOT, capture_output=True, text=True)
    try:
        return datetime.fromisoformat(proc.stdout.strip()).astimezone(timezone.utc).strftime('%Y-%m-%dT%H:%M:%SZ')
    except ValueError:
        return None


def prior_runs(symbol, fp, changed_at=None):
    """Earlier PERMUTER_SEARCH attempts: (count without gain since the last shared change, any gain)."""
    rows = [r for r in attempts.load(symbol) if 'PERMUTER_SEARCH' in (r.get('families') or [])]

    def fresh_row(r):
        if r.get('state'):
            return not attempts.stale_components(r, fp, shared_state.CONCLUSION)
        # A backfilled run predating the current mutation catalogue did not try today's mutations.
        return bool(changed_at) and (r.get('time') or '') >= changed_at
    fresh = [r for r in rows if fresh_row(r)]
    no_gain = [r for r in fresh if r.get('outcome') in ('NEUTRAL', 'NO_OP')]
    return len(no_gain), any(r.get('outcome') in ('IMPROVED', 'EXACT', 'BODY_EXACT') for r in rows)


def candidates(limit=None, symbols=None):
    import triage
    fp = shared_state.fingerprint()
    if symbols:
        rows = [triage.triage(s, fp) for s in symbols]
    else:
        rows = triage.backlog()['functions']
    out, skipped = [], []
    changed_at = mutations_changed_at()
    for t in rows:
        if t.get('state') == 'MATCHED' or t.get('error'):
            continue
        cur = t.get('current') or {}
        try:
            m, total = (int(x) for x in cur.get('opcodes', '0/1').split('/'))
        except ValueError:
            continue
        reason = None
        if t['lane'] in ('PARKED',) and not t.get('reopen_hint'):
            reason = 'parked without a reopen'
        elif t['lane'] in ('COMPOSE', 'PROMOTE', 'AUTHORING'):
            reason = 'lane %s' % t['lane']
        elif t.get('blocker_class') not in QUEUE_CLASSES:
            reason = 'class %s is not a mutation residue' % t.get('blocker_class')
        elif m / max(total, 1) < MIN_RATIO:
            reason = 'below %.0f%% opcodes' % (MIN_RATIO * 100)
        else:
            no_gain, _ = prior_runs(t['symbol'], fp, changed_at)
            if no_gain >= 2:
                reason = '%d earlier permuter runs without gain and no shared change since' % no_gain
        draft = cur.get('frontier_draft') or cur.get('draft')
        if not reason:
            reason = permutable(t['symbol'], draft)
        if reason and not symbols:
            skipped.append(dict(symbol=t['symbol'], reason=reason))
            continue
        fam = attempts.summary(t['symbol'], current_fp=fp)
        muts, dead = select_mutations(fam)
        out.append(dict(symbol=t['symbol'], draft=cur.get('frontier_draft') or cur.get('draft'), opcodes=cur.get('opcodes'),
                        blocker_class=t.get('blocker_class'), lane=t['lane'], value=t.get('value'), mutations=muts, excluded_families=dead,
                        priority=round(m / max(total, 1) * (t.get('size') or 0), 1)))
    out.sort(key=lambda r: -r['priority'])
    return (out[:limit] if limit else out), skipped


def permutable(symbol, draft):
    """None when permuter.py can locate the function in the draft, else the reason it cannot."""
    if not draft or not (ROOT / draft).is_file():
        return 'no readable draft'
    try:
        import permuter
        permuter.source_function((ROOT / draft).read_text(encoding='latin1'), symbol)
    except Exception as exc:  # parse failures are routing information, never a crash
        return 'draft not permutable: %s' % str(exc)[:120]
    return None


def load_queue():
    return read_json(QUEUE) if QUEUE.exists() else dict(items=[], history=[])


def enqueue(limit=None, symbols=None):
    queue = load_queue()
    present = {i['symbol'] for i in queue['items'] if i['status'] in ('QUEUED', 'RUNNING')}
    picked, skipped = candidates(limit, symbols)
    added = []
    for c in picked:
        if c['symbol'] in present or not c['draft']:
            continue
        queue['items'].append(dict(c, status='QUEUED', queued=now()))
        added.append(c['symbol'])
    write_json(QUEUE, queue)
    return dict(added=added, skipped=len(skipped), queue=relative(QUEUE))


def run_item(item, seconds):
    stamp = datetime.now(timezone.utc).strftime('%Y%m%d_%H%M%S')
    out = PERMUTER_OUT / ('%s_%s' % (item['symbol'].lstrip('_'), stamp))
    cmd = [sys.executable, str(ROOT / 'tools/permuter.py'), str(ROOT / item['draft']), '--function', item['symbol'],
           '--time-limit', str(seconds), '--out', str(out)]
    if item.get('mutations'):
        cmd += ['--only', ','.join(item['mutations'])]
    return subprocess.Popen(cmd, cwd=ROOT, stdout=subprocess.DEVNULL, stderr=subprocess.PIPE, text=True), out


def score_snapshot(score):
    if not score:
        return None
    return dict(strict=bool(score.get('strict_exact')), body_exact=False, row=score.get('first_divergence_row'),
                opcodes=score.get('opcode_matches'), opcode_total=score.get('opcode_total'))


def _dir_time(name):
    import re
    m = re.search(r'(\d{8})_(\d{6})$', name)
    if not m:
        return None
    d, t = m.groups()
    return '%s-%s-%sT%s:%s:%sZ' % (d[:4], d[4:6], d[6:], t[:2], t[2:4], t[4:])


def record_run(symbol, summary, out, fp, worker='permuter-queue', when=None, ledger_opcodes=None):
    before, after = score_snapshot(summary.get('baseline')), score_snapshot(summary.get('best'))
    if ledger_opcodes is not None and before is not None:
        # Judge against the stored draft the queue started from, not the permuter's own
        # (possibly regenerated, lower) baseline: a gain below the ledger is not an improvement.
        before = dict(before, opcodes=max(before.get('opcodes') or 0, ledger_opcodes), row=None)
        if after is not None and not after.get('strict') and (after.get('opcodes') or 0) <= ledger_opcodes:
            after = dict(after, row=None)
    chain = summary.get('best_chain') or []
    fams = sorted({MUTATION_FAMILY.get(str(step).split(':')[0].strip(), 'OTHER') for step in chain})
    outcome = attempts.outcome_of(before, after)
    return attempts.record(symbol, dict(worker=worker, families=['PERMUTER_SEARCH'] + [f for f in fams if f in attempts.FAMILIES and f != 'OTHER'],
                                        family_source='declared', hypothesis='permuter %ss, %s evaluations; best chain: %s' % (
                                            summary.get('time_limit_seconds'), (summary.get('counts') or {}).get('evaluations'), ', '.join(map(str, chain))[:200] or 'none'),
                                        candidates=(summary.get('counts') or {}).get('evaluations'), before=before, after=after,
                                        outcome=outcome, report=relative(out / 'summary.json'), source_key='permuter:%s' % out.name,
                                        provenance=summary.get('best_source_class'), exact_source=summary.get('exact_source'), state=fp,
                                        time=when or now()))


def run(budget_minutes=120.0, per_target=900, parallel=2):
    queue = load_queue()
    fp = shared_state.fingerprint()
    deadline = time.monotonic() + budget_minutes * 60
    running = []
    pending = [i for i in queue['items'] if i['status'] == 'QUEUED']
    finished = []
    while (pending or running) and time.monotonic() < deadline + per_target:
        while pending and len(running) < parallel and time.monotonic() + per_target <= deadline + 60:
            item = pending.pop(0)
            proc, out = run_item(item, per_target)
            item.update(status='RUNNING', started=now(), out=relative(out))
            write_json(QUEUE, queue)
            running.append((item, proc, out))
        if not pending and not running:
            break
        if not running:
            break
        time.sleep(5)
        for entry in list(running):
            item, proc, out = entry
            if proc.poll() is None:
                continue
            running.remove(entry)
            summary_path = out / 'summary.json'
            if proc.returncode == 0 and summary_path.exists():
                summary = read_json(summary_path)
                try:
                    queued = int(str(item.get('opcodes')).split('/')[0])
                except ValueError:
                    queued = None
                rec = record_run(item['symbol'], summary, out, fp, ledger_opcodes=queued)
                item.update(status='DONE', finished=now(), outcome=rec['outcome'], best=(summary.get('best') or {}).get('opcode_matches'),
                            exact_source=summary.get('exact_source'), provenance=summary.get('best_source_class'))
            else:
                item.update(status='FAILED', finished=now(), error=(proc.stderr.read() if proc.stderr else '')[-600:])
            finished.append(item['symbol'])
            write_json(QUEUE, queue)
    for item in pending:
        item['status'] = 'QUEUED'
    write_json(QUEUE, queue)
    return dict(finished=finished, remaining=[i['symbol'] for i in queue['items'] if i['status'] == 'QUEUED'])


def report():
    queue = load_queue()
    rows = [i for i in queue['items'] if i['status'] == 'DONE' and i.get('outcome') in ('EXACT', 'IMPROVED', 'BODY_EXACT')]
    return dict(meaningful=[{k: i.get(k) for k in ('symbol', 'outcome', 'opcodes', 'best', 'exact_source', 'provenance', 'out')} for i in rows],
                done=sum(i['status'] == 'DONE' for i in queue['items']), queued=sum(i['status'] == 'QUEUED' for i in queue['items']),
                failed=sum(i['status'] == 'FAILED' for i in queue['items']),
                next='exact winners: python tools/promote.py SYMBOL EXACT_SOURCE (add --steered TEXT when the provenance is STEERED)')


def backfill():
    """Import earlier build/permuter/*/summary.json runs as PERMUTER_SEARCH attempts (idempotent)."""
    count = 0
    for path in sorted(PERMUTER_OUT.glob('*/summary.json')):
        try:
            summary = read_json(path)
        except (ValueError, OSError):
            continue
        symbol = summary.get('symbol')
        if not symbol or summary.get('helper_address'):
            continue
        key = 'permuter:%s' % path.parent.name
        if any(r.get('source_key') == key for r in attempts.load(symbol)):
            continue
        rec = record_run(symbol, summary, path.parent, None, worker='permuter-backfill', when=_dir_time(path.parent.name))
        count += 1
    return dict(imported=count)


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = ap.add_subparsers(dest='command', required=True)
    p = sub.add_parser('plan'); p.add_argument('--limit', type=int, default=30); p.add_argument('--symbols')
    p = sub.add_parser('enqueue'); p.add_argument('--limit', type=int, default=12); p.add_argument('--symbols')
    p = sub.add_parser('run'); p.add_argument('--budget-minutes', type=float, default=120); p.add_argument('--per-target-seconds', type=int, default=900)
    p.add_argument('--parallel', type=int, default=2)
    sub.add_parser('report')
    sub.add_parser('backfill')
    args = ap.parse_args()
    if args.command == 'plan':
        picked, skipped = candidates(args.limit, args.symbols.split(',') if args.symbols else None)
        reasons = {}
        for s in skipped:
            key = s['reason'].split(' (')[0] if 'earlier permuter' not in s['reason'] else 'earlier permuter runs without gain'
            reasons[key] = reasons.get(key, 0) + 1
        print(json.dumps(dict(candidates=[{k: c[k] for k in ('symbol', 'opcodes', 'blocker_class', 'lane', 'excluded_families')} | dict(mutations=len(c['mutations']))
                                          for c in picked], skipped_by_reason=reasons), indent=2))
    elif args.command == 'enqueue':
        print(json.dumps(enqueue(args.limit, args.symbols.split(',') if args.symbols else None), indent=2))
    elif args.command == 'run':
        print(json.dumps(run(args.budget_minutes, args.per_target_seconds, args.parallel), indent=2))
    elif args.command == 'report':
        print(json.dumps(report(), indent=2))
    else:
        print(json.dumps(backfill(), indent=2))


if __name__ == '__main__':
    try:
        main()
    except FormatError as exc:
        raise SystemExit('ERROR: ' + str(exc))
