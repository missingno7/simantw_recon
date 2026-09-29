"""Process metrics per worker from the structured attempt ledger (old fleet vs new-process pilot).

    python tools/fleet_metrics.py --prefix f2-              # every worker whose name starts with f2-
    python tools/fleet_metrics.py --workers f3-a,f3-b [--json OUT]

Per worker (and per group):
  sessions / compiles        search sessions and compiled candidates
  first_action_minutes       first search session after the worker's PROMPT.md was written
  no_op_sessions             sessions whose every object was identical to an earlier input's
  repeated_exhausted         sessions of a family that already had >=3 gainless sessions for that
                             function (no --why-repeat, no shared change in between)
  frontier_gains             sessions that improved the stored frontier (IMPROVED/BODY_EXACT/EXACT)
  exact                      sessions producing a strict member match
  stagnant_tail_sessions     gainless sessions on functions already at >=95% opcodes
Families come from declared records, or keyword inference for backfilled history.
"""
import argparse
import glob
import json
import os
import sys
from collections import defaultdict
from datetime import datetime, timezone
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from common import ROOT, write_json
import attempts


def _t(value):
    try:
        return datetime.fromisoformat(str(value).replace('Z', '+00:00'))
    except ValueError:
        return None


def all_records():
    rows = []
    for path in glob.glob(str(ROOT / 'evidence/recovery/attempts/*.jsonl')):
        with open(path, encoding='utf-8') as stream:
            for line in stream:
                try:
                    rows.append(json.loads(line))
                except ValueError:
                    pass
    rows.sort(key=lambda r: r.get('time') or '')
    return rows


def _sessions():
    """Every search session from build/search/*/history.jsonl in time order, with its worker and families."""
    fam_by_session = {}
    for r in all_records():
        key = r.get('session') or (r.get('source_key') or '').replace('search:', '')
        if key:
            fam_by_session[(r['symbol'].lstrip('_'), key)] = (r.get('families') or ['UNSPECIFIED'], r.get('why_repeat'))
    out = []
    for path in glob.glob(str(ROOT / 'build/search/*/history.jsonl')):
        plain = Path(path).parent.name
        with open(path, encoding='utf-8') as stream:
            for line in stream:
                try:
                    h = json.loads(line)
                except ValueError:
                    continue
                rows = h.get('rows') or []
                worker = attempts._worker(h) or ''
                fams, why = fam_by_session.get((plain, h.get('time')), (['UNSPECIFIED'], None))
                out.append(dict(symbol=plain, time=attempts._iso(h.get('time')), worker=worker, rows=rows, families=fams, why_repeat=why))
    out.sort(key=lambda s: s['time'] or '')
    return out


def _score(value):
    try:
        a, b = str(value).split('/')
        return int(a), int(b)
    except (TypeError, ValueError):
        return None, None


def metrics(select):
    best = {}
    seen_objects = defaultdict(set)
    history = defaultdict(lambda: defaultdict(int))  # symbol -> family -> consecutive gainless sessions
    out = defaultdict(lambda: dict(sessions=0, compiles=0, no_op_sessions=0, repeated_exhausted=0, unlabelled_sessions=0,
                                   frontier_gains=0, exact=0, stagnant_tail_sessions=0, first=None, last=None, symbols=set()))
    for s in _sessions():
        sym = s['symbol']
        scores = [_score(r.get('opcodes')) for r in s['rows']]
        scores = [(a, b) for a, b in scores if a is not None]
        top = max((a for a, _ in scores), default=None)
        total = max((b for _, b in scores), default=None)
        objects = {r.get('object') for r in s['rows'] if r.get('object')}
        no_op = bool(objects) and objects <= seen_objects[sym]
        exact = any(r.get('result') in ('CONFIRMED_MEMBER', 'STRONGLY_SUPPORTED_MEMBER') for r in s['rows'])
        prior = best.get(sym)
        gain = exact or (top is not None and (prior is None or top > prior))
        if select(s['worker']):
            m = out[s['worker']]
            m['sessions'] += 1
            m['compiles'] += len(s['rows'])
            m['no_op_sessions'] += int(no_op)
            m['frontier_gains'] += int(gain and prior is not None)
            m['exact'] += int(exact)
            if not gain and prior is not None and total and prior / total >= 0.95:
                m['stagnant_tail_sessions'] += 1
            labelled = [f for f in s['families'] if f != 'UNSPECIFIED']
            m['unlabelled_sessions'] += int(not labelled)
            if not gain and not s['why_repeat'] and any(history[sym][f] >= 3 for f in labelled):
                m['repeated_exhausted'] += 1
            m['first'] = m['first'] or s['time']
            m['last'] = s['time']
            m['symbols'].add(sym)
        for f in s['families']:
            history[sym][f] = 0 if gain else history[sym][f] + 1
        seen_objects[sym] |= objects
        if top is not None and (prior is None or top > prior):
            best[sym] = top
    result = {}
    for worker, m in out.items():
        prompt = ROOT / 'build/workers' / worker / 'PROMPT.md'
        start = datetime.fromtimestamp(prompt.stat().st_mtime, timezone.utc) if prompt.exists() else None
        first, last = _t(m['first']), _t(m['last'])
        result[worker] = dict({k: v for k, v in m.items() if k not in ('symbols', 'first', 'last')}, targets=len(m['symbols']),
                              first_action_minutes=round((first - start).total_seconds() / 60, 1) if start and first and first >= start else None,
                              active_hours=round((last - first).total_seconds() / 3600, 2) if first and last else None)
    return result


def totals(per_worker):
    keys = ('sessions', 'compiles', 'no_op_sessions', 'repeated_exhausted', 'unlabelled_sessions', 'frontier_gains', 'exact', 'stagnant_tail_sessions')
    t = {k: sum(w[k] for w in per_worker.values()) for k in keys}
    firsts = [w['first_action_minutes'] for w in per_worker.values() if w['first_action_minutes'] is not None]
    hours = sum(w['active_hours'] or 0 for w in per_worker.values())
    t.update(workers=len(per_worker), active_hours=round(hours, 1),
             median_first_action_minutes=sorted(firsts)[len(firsts) // 2] if firsts else None,
             no_op_rate=round(t['no_op_sessions'] / max(t['sessions'], 1), 3),
             repeated_exhausted_rate_of_labelled=round(t['repeated_exhausted'] / max(t['sessions'] - t['unlabelled_sessions'], 1), 3),
             unlabelled_rate=round(t['unlabelled_sessions'] / max(t['sessions'], 1), 3),
             stagnant_tail_rate=round(t['stagnant_tail_sessions'] / max(t['sessions'], 1), 3),
             gains_per_active_hour=round(t['frontier_gains'] / max(hours, 0.01), 2),
             compiles_per_gain=round(t['compiles'] / max(t['frontier_gains'], 1), 1))
    return t


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('--prefix')
    ap.add_argument('--workers')
    ap.add_argument('--json')
    args = ap.parse_args()
    names = set(args.workers.split(',')) if args.workers else None
    select = (lambda w: w in names) if names else (lambda w: bool(args.prefix) and w.startswith(args.prefix))
    per = metrics(select)
    report = dict(totals=totals(per), workers=per)
    if args.json:
        write_json(Path(args.json), report)
    print(json.dumps(report['totals'], indent=2))


if __name__ == '__main__':
    main()
