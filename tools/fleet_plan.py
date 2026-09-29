"""Lane-based worker assignment from the triage backlog (small, focused, one owner per object).

    python tools/fleet_plan.py [--authoring N] [--tail N] [--compose N] [--per-worker 4] [--prefix f3]
    python tools/fleet_plan.py ... --write     # also write build/workers/NAME/PROMPT.md + build/fleet/plan.json
    python tools/fleet_plan.py ... --claim     # claim each worker's composition objects in layout/unit-owners.json

Targets are ranked by triage's expected progress per agent-hour, not by closeness to exact:
  AUTHORING  large opcode/byte debt with a poor match: author semantics, control flow, loops,
             structs and calls region by region (emu_diff first). 3-5 targets per worker.
  TAIL       near-exact functions with an UNTRIED (or newly stale) mechanism family for their
             blocker class. A tail target with no untried family is not given to an agent: it
             goes to tools/permuter_queue.py (BACKGROUND_PERMUTER) or stays PARKED.
  COMPOSE    body-exact / binding-only functions: one worker per historical object, which it
             owns for canonical unit composition (tools/unit_owner.py).
Workers are grouped by historical object so a single worker holds all planned targets of an
object; other workers never persist or admit units of an object they do not own.
"""
import argparse
import json
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from common import ROOT, FormatError, read_json, relative, write_json

LANE_OF = {'AUTHORING': 'AUTHORING', 'TAIL_INTERACTIVE': 'TAIL', 'COMPOSE': 'COMPOSE', 'PROMOTE': 'COMPOSE'}
BINDING_TO_COMPOSE = True

BRIEF = """Your name: {name}. You work on the byte-exact Win16 SimAnt reconstruction in D:\\Prog\\simantw_recon (read AGENTS.md first).
Set SIMANTW_WORKER={name} for every command (PowerShell: $env:SIMANTW_WORKER='{name}'). Work only in build/workers/{name}/.

Lane: {lane}. {lane_text}

Your targets (from python tools/triage.py; re-run it per target before you start, it is cheap):
{targets}

Workflow per target:
1. python tools/triage.py SYMBOL   (the next tool, untried families, exhausted families, facts, last compose result)
2. python tools/context.py SYMBOL --brief   (already_tried replaces reading every note)
3. Run the recommended tool first. Then write drafts and compile them with
   python tools/search.py SYMBOL a.c [b.c] --family FAMILY --hypothesis "..." [--prediction "..."] [--falsifier "..."]
   Always give --family (python tools/attempts.py families). Repeat an exhausted family only with --why-repeat "new fact/tool/evidence".
4. Exact: python tools/promote.py SYMBOL FILE.c. Exact body blocked by placement: say so in REPORT.md; the unit owner composes it
   ({owner_rule}).
Stop a target when it is exact, when you hit a concrete missing dependency (search.py --note), or after ~10 stagnant rounds
(rounds, not checks: a round is a compiled source change): record what you learned with --note and move to your next target.
Rules: no asm/pragmas/includes/absolute-address casts to force bytes; never edit src/recovery.json, ledgers, proofs, fixtures, locks or hashes;
no git, no validate.py. Write build/workers/{name}/REPORT.md. Final answer: at most 15 lines.
"""

LANE_TEXT = {
    'AUTHORING': 'Author missing semantics and structure. These functions have a large opcode/byte gap; a better reconstruction of '
                 'control flow, loops, structs, calls and data use moves dozens to hundreds of opcodes. Do not tune registers or homes here.\n'
                 'Depth is the point of this lane: plan on 2-3 hours, most of it on your largest target. triage.py lists "missing regions" '
                 '(target code the draft lacks, with offsets and first instructions) and "extra regions" (draft code the target does not have). '
                 'Each round, pick one region, read those target instructions in the aligned diff (search.py --full), write the C that produces '
                 'them, compile, and keep the draft if the region aligns. A restructuring round may lose opcodes elsewhere before it wins; keep '
                 'going. Checking emu_diff/typedb is a diagnostic, not the work. Do not leave a target after one or two trials: leave it only '
                 'after about 10 rounds without any region gain, or on a concrete missing dependency (record it with --note).',
    'TAIL': 'Near-exact functions. Each has at least one mechanism family that was never tried (or whose earlier negative result went stale '
            'after a shared change). Test exactly those families; do not re-run exhausted ones.',
    'COMPOSE': 'Body-exact or binding-only functions. You own canonical unit composition of the listed objects: '
               'fix wrong data/selector bindings, then python tools/tu_assembly.py compose OBJECT --add SYMBOL=DRAFT [--persist] and '
               'python tools/promote.py --unit UNIT --reason "..." once strict.',
}


def backlog(path=None, refresh=True):
    import triage
    if refresh or not path:
        return triage.backlog()
    return read_json(Path(path))


def eligible(t, lane):
    if t.get('error') or t.get('state') == 'MATCHED':
        return False
    if lane == 'COMPOSE':
        return t['lane'] in ('COMPOSE', 'PROMOTE') or (BINDING_TO_COMPOSE and t.get('blocker_class') == 'BINDING')
    if lane == 'TAIL':
        return t['lane'] == 'TAIL_INTERACTIVE' and t.get('blocker_class') != 'BINDING' and bool(t.get('next_families'))
    return LANE_OF.get(t['lane']) == lane


def assign(rows, lane, workers, per_worker, prefix, taken_objects):
    """Greedy by value; each worker takes whole objects (all its planned targets of that object)."""
    pool = [t for t in rows if eligible(t, lane)]
    pool.sort(key=lambda t: -(t.get('value') or 0))
    by_object = {}
    for t in pool:
        obj = (t.get('unit') or {}).get('component') or t['symbol']
        by_object.setdefault(obj, []).append(t)
    order = sorted(by_object, key=lambda o: -max(t.get('value') or 0 for t in by_object[o]))
    plans = [dict(name='%s-%s-%d' % (prefix, lane.lower(), i + 1), lane=lane, targets=[], objects=[]) for i in range(workers)]
    for obj in order:
        if obj in taken_objects:
            continue
        group = by_object[obj][:per_worker]
        worker = next((p for p in plans if len(p['targets']) + len(group) <= per_worker), None)
        if worker is None:
            worker = next((p for p in plans if len(p['targets']) < per_worker), None)
            if worker is None:
                break
            group = group[:per_worker - len(worker['targets'])]
        worker['targets'].extend(group)
        worker['objects'].append(obj)
        taken_objects.add(obj)
    return [p for p in plans if p['targets']]


def target_line(t):
    cur = t.get('current') or {}
    fd = t.get('first_divergence') or {}
    return '- %s (%s bytes, object %s): %s %s; class %s; first divergence %s; next: %s; families: %s' % (
        t['symbol'], t.get('size'), (t.get('unit') or {}).get('component'), cur.get('opcodes', 'no draft'), cur.get('draft') or '',
        t.get('blocker_class'), fd.get('kind'), t.get('next_tool', '').split('  #')[0], ', '.join(t.get('next_families') or []))


def plan(authoring=4, tail=2, compose=1, per_worker=4, prefix='f3', refresh=True, backlog_path=None):
    data = backlog(backlog_path, refresh)
    rows = data['functions']
    workers = []
    # Composition ownership is exclusive per object. Authoring/tail workers may investigate
    # functions of an owned object (they never compose it); they do not share an object
    # among themselves, so two agents never grow drafts for one unit at once.
    workers += assign(rows, 'COMPOSE', compose, per_worker + 2, prefix, set())
    investigation = set()
    workers += assign(rows, 'AUTHORING', authoring, per_worker, prefix, investigation)
    workers += assign(rows, 'TAIL', tail, per_worker, prefix, investigation)
    background = [t['symbol'] for t in rows if t.get('lane') == 'BACKGROUND_PERMUTER']
    parked = [dict(symbol=t['symbol'], reopen=bool(t.get('reopen_hint'))) for t in rows if t.get('lane') == 'PARKED']
    expected = sum(t.get('value') or 0 for w in workers for t in w['targets'])
    return dict(workers=[dict(name=w['name'], lane=w['lane'], objects=w['objects'],
                              targets=[dict(symbol=t['symbol'], value=t.get('value'), blocker_class=t.get('blocker_class'),
                                            opcodes=(t.get('current') or {}).get('opcodes'), next_families=t.get('next_families')) for t in w['targets']],
                              brief=BRIEF.format(name=w['name'], lane=w['lane'], lane_text=LANE_TEXT[w['lane']],
                                                 targets='\n'.join(target_line(t) for t in w['targets']),
                                                 owner_rule='you own: ' + ', '.join(w['objects']) if w['lane'] == 'COMPOSE' else
                                                 'python tools/unit_owner.py list shows the owner'))
                         for w in workers],
                background_permuter=background, parked=parked, lanes=data.get('lanes'),
                expected_debt_bytes_per_agent_hour=round(expected, 1),
                rule='ranked by triage value (expected debt bytes per agent-hour); tails only with an untried family; one owner per object')


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('--authoring', type=int, default=4)
    ap.add_argument('--tail', type=int, default=2)
    ap.add_argument('--compose', type=int, default=1)
    ap.add_argument('--per-worker', type=int, default=4)
    ap.add_argument('--prefix', default='f3')
    ap.add_argument('--backlog', help='reuse a triage backlog JSON instead of recomputing')
    ap.add_argument('--write', action='store_true')
    ap.add_argument('--claim', action='store_true')
    args = ap.parse_args()
    if not 3 <= args.per_worker <= 6:
        raise FormatError('--per-worker should stay small (3..6 focused targets)')
    result = plan(args.authoring, args.tail, args.compose, args.per_worker, args.prefix, refresh=not args.backlog, backlog_path=args.backlog)
    if args.write:
        for w in result['workers']:
            folder = ROOT / 'build/workers' / w['name']
            folder.mkdir(parents=True, exist_ok=True)
            (folder / 'PROMPT.md').write_text(w['brief'], encoding='utf-8')
        write_json(ROOT / 'build/fleet/plan.json', result)
    if args.claim:
        import unit_owner
        for w in result['workers']:
            if w['lane'] == 'COMPOSE':
                for obj in w['objects']:
                    if ':' in obj:
                        unit_owner.claim(obj, w['name'], 'fleet_plan COMPOSE lane', hours=24)
    view = dict(result)
    view['workers'] = [{k: v for k, v in w.items() if k != 'brief'} for w in result['workers']]
    print(json.dumps(view, indent=2))


if __name__ == '__main__':
    try:
        main()
    except FormatError as exc:
        raise SystemExit('ERROR: ' + str(exc))
