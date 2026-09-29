"""Re-evaluate every preserved draft of the OPEN functions against the CURRENT repository state.

    python tools/sweep.py                       # incremental: only drafts whose evaluation key changed
    python tools/sweep.py --since-last          # same, and print which shared components changed
    python tools/sweep.py --triggers            # just report shared changes since the last sweep
    python tools/sweep.py --symbols _A,_B --force
    python tools/sweep.py --derive typedb       # also compile a typedb-resynced variant of each best draft
    python tools/sweep.py --verify --compose    # fresh promote.py --verify-only / bounded unit composition
    python tools/sweep.py --verify --compose --admit   # supervisor: admit what passed the normal gates

A draft's C source is self-contained, so its result changes only when a shared
component changes (tools/shared_state.py). The draft is recompiled under the
symbol's CURRENT profile when any of these changed since its last evaluation:
the toolchain lock, the compiler implementation, the matcher, or the profile
assignment. Identical (source, flags, implementation) compiles come from the
content-addressed compiler cache. Derived typedb variants additionally depend on
admissions and the typedb tool.

The sweep only refreshes the drafts ledger through drafts.refresh()/store() and
appends SHARED_STATE_RESWEEP attempt records. It never admits on its own
comparison:
  NEWLY_EXACT       strict member match   -> promote.py SYMBOL DRAFT --verify-only (with --verify)
  NEWLY_BODY_EXACT  exact body, blocked only by unit/private placement
                    -> tu_assembly.py compose OBJECT --add SYMBOL=DRAFT (with --compose, scratch only)
  IMPROVED / UNCHANGED / REGRESSED / COMPILE_FAILED
With --admit, candidates that passed --verify are admitted with the normal
promote.py command, and strictly passing compositions are persisted and
admitted with promote.py --unit; both re-run every gate from scratch.

Reports: build/sweep/latest.json (full) and evidence/recovery/sweeps/STAMP.json (compact).
"""
import argparse
import hashlib
import json
import os
import subprocess
import sys
import time
from contextlib import redirect_stdout
from datetime import datetime, timezone
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from common import ROOT, FormatError, cards, fixture, identity, read_json, recipes, relative, sha256, write_json
import attempts
import drafts
import shared_state

OUT = ROOT / 'build/sweep'
STATE = OUT / 'state.json'
DIAGNOSTICS = OUT / 'diagnostics'
DURABLE = ROOT / 'evidence/recovery/sweeps'
GOOD = ('CONFIRMED_MEMBER', 'STRONGLY_SUPPORTED_MEMBER')


def stamp():
    return datetime.now(timezone.utc).strftime('%Y%m%dT%H%M%S')


def open_functions():
    """OPEN GAME functions (not admitted) keyed by symbol, with their card."""
    admitted = recipes()
    return {c['symbol']: c for c in cards() if c.get('ownership') == 'GAME' and c['symbol'] not in admitted}


def ledger_symbol(key, open_cards):
    return key if key in open_cards else '_' + key if '_' + key in open_cards else None


def eval_key(source_sha, flags, fp, derived=None):
    parts = dict(source=source_sha, flags=flags, recompile=shared_state.recompile_key(fp))
    if derived:
        parts.update(derived=derived, admissions=fp['admissions'], typedb=fp['typedb'])
    return hashlib.sha256(json.dumps(parts, sort_keys=True).encode()).hexdigest()[:20]


def collect(symbols=None):
    """Stored best/frontier drafts per open function: {symbol: [(kind, path, sha)]}."""
    open_cards = open_functions()
    ledger = drafts.load()
    found = {}
    for key, row in ledger.items():
        symbol = ledger_symbol(key, open_cards)
        if symbol is None or (symbols and symbol not in symbols):
            continue
        for kind in ('best', 'frontier'):
            rec = row.get(kind)
            if not rec or not rec.get('source'):
                continue
            path = ROOT / rec['source']
            if not path.is_file() or path.suffix.lower() != '.c':
                continue
            items = found.setdefault(symbol, [])
            if all(i['sha'] != rec['sha256'] for i in items):
                items.append(dict(kind=kind, path=path, sha=rec['sha256'], ledger_key=key))
            else:
                next(i for i in items if i['sha'] == rec['sha256'])['kind'] += '+' + kind
    return found, open_cards


def derive_typedb(symbol, item, out):
    """typedb-resynced variant of a stored draft, or None when resync changes nothing/fails."""
    import typedb
    dest = out / 'derived' / symbol.lstrip('_') / (item['sha'][:12] + '.typedb.c')
    dest.parent.mkdir(parents=True, exist_ok=True)
    try:
        with redirect_stdout(sys.stderr):
            result = typedb.resync_source(item['path'], dest)
    except Exception as exc:  # resync is a derived hypothesis; its failure never stops the sweep
        return None, 'typedb resync failed: %s' % str(exc)[:200]
    if not dest.is_file() or not (result or {}).get('change_count'):
        return None, None
    if dest.read_bytes() == item['path'].read_bytes():
        return None, None
    return dest, None


def score(jobs):
    """Compile (cached) and strictly compare each job {symbol, source, flags}; returns comparisons."""
    import ne, mapsym, omf
    from codegen_cache import compile_cached
    from codegen_grinder import score_object
    from codegen_diff import diagnose
    from library_match import import_symbols
    if not jobs:
        return [], dict(hits=0, misses=0)
    with redirect_stdout(sys.stderr):
        compiled, stats = compile_cached([dict(source=relative(j['source']), flags=j['flags']) for j in jobs])
    raw = fixture('SIMANTW.EXE'); image = ne.parse(raw); symbols = mapsym.parse(fixture('SIMANTW.SYM'))
    imports = import_symbols(ROOT / 'toolchain/sdk300/WLIB/LIBW.LIB')
    out = []
    for job, (obj, receipt) in zip(jobs, compiled):
        if not obj or receipt.get('unsupported_option'):
            out.append(dict(result='COMPILE_FAILED', issues=[(receipt.get('stdout') or '')[-600:]]))
            continue
        try:
            module = omf.parse(obj.read_bytes())
            try:
                comparison = score_object(module, raw, image, symbols, imports, job['symbol'])
            except FormatError as exc:
                comparison = dict(result='UNSUPPORTED_COMPARISON', issues=[str(exc)])
            comparison['diagnostic'] = diagnose(module, raw, image, symbols, job['symbol'], comparison)
            comparison['object_sha256'] = (receipt.get('object_identity') or {}).get('sha256')
        except (FormatError, StopIteration, KeyError, ValueError, IndexError) as exc:
            # e.g. a stored draft that no longer defines the public: a diagnostic failure, not a crash
            comparison = dict(result='UNSUPPORTED_COMPARISON', issues=['%s: %s' % (type(exc).__name__, exc)])
        out.append(comparison)
    return out, stats


def compact(comparison):
    """What triage needs from a comparison: counts, first divergence, aligned rows."""
    from residue_clusters import classify
    from tu_assembly import body_exact
    d = comparison.get('diagnostic') or {}
    rows = d.get('aligned_asm') or []
    kind, index, row = classify(rows) if rows else (None, None, None)
    return dict(result=comparison.get('result'), strict=comparison.get('result') in GOOD, body_exact=bool(d) and body_exact(comparison),
                rank=drafts.rank(comparison), frontier_rank=drafts.frontier_rank(comparison),
                opcode_matches=d.get('opcode_matches'), opcode_total=d.get('opcode_total'),
                candidate_bytes=d.get('candidate_bytes'), target_bytes=d.get('target_bytes'),
                instruction_layout_match=d.get('instruction_layout_match'),
                register_only_differences=d.get('register_only_differences'), stack_local_differences=d.get('stack_local_differences'),
                branch_target_differences=d.get('branch_target_differences'), memory_operand_differences=d.get('memory_operand_differences'),
                immediate_differences=d.get('immediate_differences'), categories=d.get('categories'),
                first_structural_difference=d.get('first_structural_difference'),
                fixups='%s/%s' % (comparison.get('fixups_equal'), comparison.get('fixups_total')),
                first_divergence=dict(kind=kind, row=index, target=(row or {}).get('target'), candidate=(row or {}).get('candidate'),
                                      differences=(row or {}).get('differences')) if rows else None,
                features=dict(target=comparison.get('target_features'), candidate=comparison.get('features')),
                issues=(comparison.get('issues') or [])[:4], aligned_asm=rows)


def classify_change(before_best, before_front, results):
    """Symbol-level sweep outcome. Code-level progress is judged on drafts.rank (strict, exact body,
    opcode matches, size delta); a first-divergence row that moved only because the classifier or
    the stored frontier changed is RESCORED bookkeeping, not progress."""
    usable = [r for r in results if r['eval'].get('rank') is not None]
    if not usable:
        return 'COMPILE_FAILED'
    if any(r['eval']['strict'] for r in usable):
        return 'NEWLY_EXACT'
    if any(r['eval']['body_exact'] for r in usable):
        return 'NEWLY_BODY_EXACT' if not (before_best or {}).get('key', [0, 0])[1] else 'BODY_EXACT'
    best_new = max(r['eval']['rank'] for r in usable)
    old_best = (before_best or {}).get('key')
    if old_best and best_new > old_best:
        return 'IMPROVED'
    # REGRESSED only when the SAME stored best draft now scores lower. A worker may store a newer
    # best while the sweep runs; comparing an older draft against it is a race, not a regression.
    same = [r for r in usable if r.get('job', {}).get('variant', {}).get('sha') == (before_best or {}).get('sha256')]
    if old_best and same and max(r['eval']['rank'] for r in same) < old_best:
        return 'REGRESSED'
    if old_best and best_new < old_best:
        return 'SUPERSEDED'
    front_new = max((r['eval']['frontier_rank'] for r in usable if r['eval']['frontier_rank']), default=None)
    if front_new and (before_front or {}).get('key') and front_new != before_front['key']:
        return 'RESCORED'
    return 'UNCHANGED'


def change_cause(before_best, results, flags):
    """Why the result moved: the profile (flags) changed, a derived typedb variant won, or the tools re-ranked it."""
    causes = []
    if before_best and before_best.get('flags') and before_best['flags'] != flags:
        causes.append('PROFILE_CHANGED %s -> %s' % (' '.join(before_best['flags'][3:-1]), ' '.join(flags[3:-1])))
    usable = [r for r in results if r['eval'].get('rank') is not None]
    if usable:
        top = max(usable, key=lambda r: r['eval']['rank'])
        if top['origin_kind'] == 'derived':
            causes.append('TYPEDB_RESYNC_VARIANT')
    return causes or ['TOOLING_OR_RANKING']


def run_promote_verify(symbol, source):
    cmd = [sys.executable, str(ROOT / 'tools/promote.py'), symbol, relative(source), '--verify-only']
    proc = subprocess.run(cmd, cwd=ROOT, capture_output=True, text=True, timeout=1800)
    return dict(command=' '.join(cmd[1:]), exit_code=proc.returncode, passed=proc.returncode == 0,
                tail=(proc.stdout + proc.stderr)[-1500:])


def run_compose(symbol, source, component, out_name, persist=False):
    cmd = [sys.executable, str(ROOT / 'tools/tu_assembly.py'), 'compose', component, '--add', '%s=%s' % (symbol, relative(source)),
           '--out', out_name, '--max-arrangements', '12'] + (['--persist'] if persist else [])
    proc = subprocess.run(cmd, cwd=ROOT, capture_output=True, text=True, timeout=3600)
    result = dict(command=' '.join(cmd[1:]), exit_code=proc.returncode)
    text = proc.stdout
    start = text.find('\n{') + 1 if not text.startswith('{') else 0
    try:
        data = json.loads(text[start:]) if proc.returncode == 0 and '{' in text else None
    except ValueError:
        data = None
    if data:
        unit = data.get('unit_result') or {}
        result.update(strict_pass=bool(unit.get('strict_pass')), result=unit.get('result'), unit=data.get('unit'),
                      issues=(unit.get('issues') or [])[:4], best_source=data.get('best_source'), note=data.get('note'))
    else:
        err = (proc.stderr.strip().splitlines() or proc.stdout.strip().splitlines() or [''])[-1]
        result.update(strict_pass=False, error=err[-600:])
        if 'no admitted unit source' in err:
            result['next'] = ('no admitted unit for %s yet: build one with python tools/tu_assembly.py build %s --members %s --scaffold '
                              '(docs/build-topology.md)' % (component, component, symbol))
        elif 'composable' in err:
            result['next'] = 'draft hygiene: remove the rejected directive from the draft, re-run search.py, then compose'
    return result


def triggers():
    last = read_json(OUT / 'last.json') if (OUT / 'last.json').exists() else {}
    now = shared_state.fingerprint()
    old = last.get('fingerprint')
    return dict(last_sweep=last.get('stamp'), changed=shared_state.changed(old, now) if old else sorted(now),
                sweep_triggers=shared_state.changed(old, now, shared_state.SWEEP_TRIGGERS) if old else list(shared_state.SWEEP_TRIGGERS),
                recompile_triggers=shared_state.changed(old, now, shared_state.RECOMPILE) if old else list(shared_state.RECOMPILE),
                fingerprint=now)


def sweep(symbols=None, force=False, derive=(), verify=False, compose=False, admit=False, limit=None):
    began = time.perf_counter()
    run_stamp = stamp()
    fp = shared_state.fingerprint()
    OUT.mkdir(parents=True, exist_ok=True)
    DIAGNOSTICS.mkdir(parents=True, exist_ok=True)
    # --force bypasses the cache for this run's symbols but must never discard other entries.
    state = read_json(STATE) if STATE.exists() else {}
    found, open_cards = collect(symbols)
    if limit:
        found = dict(list(sorted(found.items()))[:limit])
    import compiler_profiles
    if 'typedb' in derive:
        import typedb
        with redirect_stdout(sys.stderr):
            typedb.build_database()
    jobs, skipped = [], 0
    notes, reused = {}, {}
    for symbol, items in sorted(found.items()):
        card = open_cards[symbol]
        try:
            flags = compiler_profiles.flags_for(symbol, card['segment_name'])
        except FormatError as exc:
            notes[symbol] = 'profile: %s' % exc
            continue
        variants = [dict(item, origin_kind=item['kind']) for item in items]
        if 'typedb' in derive:
            best_item = next((i for i in items if 'best' in i['kind']), items[0])
            dkey = eval_key(best_item['sha'], flags, fp, 'typedb')
            if state.get(dkey, {}).get('no_variant') and not force:
                pass
            else:
                path, err = derive_typedb(symbol, best_item, OUT)
                if err:
                    notes[symbol] = err
                if path is None:
                    state[dkey] = dict(no_variant=True, symbol=symbol)
                else:
                    variants.append(dict(kind='derived', origin_kind='derived', path=path, sha=identity(path)['sha256'], derived='typedb',
                                         parent=best_item['sha'], ledger_key=best_item['ledger_key']))
        previous = {}
        diag_path = DIAGNOSTICS / (symbol.lstrip('_').replace(':', '_') + '.json')
        if diag_path.exists() and not force:
            previous = {(d['sha256'], tuple(d['flags'])): d for d in read_json(diag_path).get('drafts', [])}
        for v in variants:
            key = eval_key(v['sha'], flags, fp, v.get('derived'))
            cached = state.get(key)
            prior = previous.get((v['sha'], tuple(flags)))
            if cached and cached.get('eval') and prior is not None and not force:
                # Unchanged evaluation key: reuse the stored evaluation (with its aligned rows) so the
                # symbol is still judged on its complete draft set.
                skipped += 1
                reused.setdefault(symbol, []).append(dict(variant=v, flags=flags, eval=prior))
                continue
            jobs.append(dict(symbol=symbol, source=v['path'], flags=flags, key=key, variant=v))
    comparisons, cache_stats = score(jobs)
    by_symbol = {}
    for job, comparison in zip(jobs, comparisons):
        ev = compact(comparison)
        v = job['variant']
        # Keep the compact evaluation (without aligned rows) in the state cache; rows go to diagnostics.
        state[job['key']] = dict(symbol=job['symbol'], sha=v['sha'], flags=job['flags'], kind=v['origin_kind'], evaluated=run_stamp,
                                 eval={k: val for k, val in ev.items() if k != 'aligned_asm'})
        by_symbol.setdefault(job['symbol'], []).append(dict(job=job, comparison=comparison, eval=ev, origin_kind=v['origin_kind']))
    for symbol in reused:
        by_symbol.setdefault(symbol, [])
        for item in reused.get(symbol, []):
            v = item['variant']
            job = dict(symbol=symbol, source=v['path'], flags=item['flags'], key=None, variant=v)
            ev = {k: val for k, val in item['eval'].items() if k not in ('kind', 'source', 'sha256', 'flags')}
            by_symbol[symbol].append(dict(job=job, comparison=None, eval=ev, origin_kind=v['origin_kind'], reused=True))
    ledger = drafts.load()
    report_rows = []
    for symbol, results in sorted(by_symbol.items()):
        key = results[0]['job']['variant'].get('ledger_key') or symbol
        entry = ledger.get(key) or ledger.get(symbol) or {}
        before_best, before_front = entry.get('best'), entry.get('frontier')
        outcome = classify_change(before_best, before_front, results)
        refreshed = []
        origin = relative(OUT / (run_stamp + '.json'))
        usable = [r for r in results if r['eval'].get('rank') is not None and not r.get('reused')]
        # Re-score stored drafts first, then offer every evaluation to store(): a dropped
        # stub frontier is re-seeded and a now-better frontier/derived draft can replace the best.
        for r in usable:
            job = r['job']
            if r['origin_kind'] != 'derived':
                refreshed += drafts.refresh(job['variant']['ledger_key'], job['variant']['sha'], r['comparison'], origin, job['flags'], state=dict(sweep=run_stamp))
        for r in usable:
            job = r['job']
            if drafts.store(job['variant'].get('ledger_key') or symbol, job['source'], r['comparison'], origin, job['flags'],
                            basis='EXACT_BODY_CANDIDATE' if r['eval']['body_exact'] else None):
                refreshed.append('stored:' + r['origin_kind'])
        best = max(results, key=lambda r: (r['eval'].get('frontier_rank') is not None, r['eval'].get('rank') or [], r['eval'].get('frontier_rank') or []))
        diag = dict(symbol=symbol, evaluated=run_stamp, fingerprint=fp, drafts=[dict(kind=r['origin_kind'], source=relative(r['job']['source']),
                                                                                    sha256=r['job']['variant']['sha'], flags=r['job']['flags'], **r['eval'])
                                                                              for r in results])
        write_json(DIAGNOSTICS / (symbol.lstrip('_').replace(':', '_') + '.json'), diag)
        row = dict(symbol=symbol, outcome=outcome, drafts=len(results), best_kind=best['origin_kind'], best_source=relative(best['job']['source']),
                   before=dict(best=(before_best or {}).get('key'), frontier=(before_front or {}).get('key')),
                   after=dict(rank=best['eval'].get('rank'), frontier_rank=best['eval'].get('frontier_rank'),
                              opcodes='%s/%s' % (best['eval'].get('opcode_matches'), best['eval'].get('opcode_total')),
                              first_divergence=(best['eval'].get('first_divergence') or {}).get('kind')),
                   ledger_changes=refreshed or None, note=notes.get(symbol))
        if outcome != 'UNCHANGED':
            row['cause'] = change_cause(before_best, results, results[0]['job']['flags'])
        component = (compiler_profiles.component_of(symbol) or {}).get('id')
        if outcome == 'NEWLY_EXACT':
            winner = next(r for r in results if r['eval']['strict'])
            row['route'] = dict(action='PROMOTE', command='python tools/promote.py %s %s' % (symbol, relative(winner['job']['source'])))
            if verify:
                row['route']['verify'] = run_promote_verify(symbol, winner['job']['source'])
                if admit and row['route']['verify']['passed']:
                    row['route']['admit'] = run_admit([symbol, relative(winner['job']['source'])])
        elif outcome in ('NEWLY_BODY_EXACT', 'BODY_EXACT'):
            winner = next(r for r in results if r['eval']['body_exact'])
            row['route'] = dict(action='COMPOSE', component=component,
                                command='python tools/tu_assembly.py compose %s --add %s=%s' % (component, symbol, relative(winner['job']['source'])))
            if compose and component:
                import unit_owner
                owner = unit_owner.owner_of(component)
                if owner and owner.get('owner') not in ('sweep', 'supervisor'):
                    row['route']['compose'] = dict(skipped='component %s is owned by %s' % (component, owner.get('owner')))
                else:
                    name = 'sweep-%s/%s' % (run_stamp, symbol.lstrip('_'))
                    row['route']['compose'] = run_compose(symbol, winner['job']['source'], component, name)
                    c = row['route']['compose']
                    attempts.record(symbol, dict(worker='sweep', families=['TU_COMPOSITION'], family_source='declared',
                                                 hypothesis='sweep compose into %s: %s' % (component, 'strict pass' if c.get('strict_pass') else
                                                             (c.get('error') or '; '.join(c.get('issues') or []) or c.get('result') or 'failed')[:300]),
                                                 candidates=1, outcome='EXACT' if c.get('strict_pass') else 'NEUTRAL', report=c.get('note'),
                                                 session=run_stamp, state=fp))
                    if admit and row['route']['compose'].get('strict_pass'):
                        persisted = run_compose(symbol, winner['job']['source'], component, name + '-persist', persist=True)
                        row['route']['persist'] = persisted
                        if persisted.get('strict_pass') and persisted.get('unit'):
                            row['route']['admit'] = run_admit(['--unit', persisted['unit'], '--reason',
                                                               'sweep %s: body-exact %s composed into %s' % (run_stamp, symbol, component)])
        if outcome not in ('UNCHANGED', 'RESCORED', 'BODY_EXACT'):
            attempts.record(symbol, dict(worker='sweep', families=['SHARED_STATE_RESWEEP'], family_source='declared',
                                         hypothesis='re-evaluation of preserved drafts under the current shared state',
                                         candidates=len(results), before=attempts.ledger_snapshot(entry),
                                         after=attempts.snapshot_from_key(best['eval'].get('frontier_rank'), dict(opcode_total=best['eval'].get('opcode_total'),
                                                                          divergence_class=(best['eval'].get('first_divergence') or {}).get('kind'))),
                                         outcome={'NEWLY_EXACT': 'EXACT', 'NEWLY_BODY_EXACT': 'BODY_EXACT', 'BODY_EXACT': 'NEUTRAL', 'IMPROVED': 'IMPROVED', 'RESCORED': 'NEUTRAL',
                                                  'REGRESSED': 'REGRESSED', 'COMPILE_FAILED': 'COMPILE_FAILED'}.get(outcome, 'NEUTRAL'),
                                         report=relative(OUT / (run_stamp + '.json')), session=run_stamp, state=fp))
        report_rows.append(row)
    write_json(STATE, state)
    counts = {}
    for row in report_rows:
        counts[row['outcome']] = counts.get(row['outcome'], 0) + 1
    report = dict(stamp=run_stamp, fingerprint=fp, seconds=round(time.perf_counter() - began, 1), functions_with_drafts=len(found),
                  compiled=len(jobs), skipped_unchanged_key=skipped, cache=cache_stats, derive=list(derive), counts=counts,
                  newly_exact=[r['symbol'] for r in report_rows if r['outcome'] == 'NEWLY_EXACT'],
                  newly_body_exact=[r['symbol'] for r in report_rows if r['outcome'] == 'NEWLY_BODY_EXACT'],
                  composition_blocked=[r['symbol'] for r in report_rows if r['outcome'] in ('NEWLY_BODY_EXACT', 'BODY_EXACT')],
                  improved=[r['symbol'] for r in report_rows if r['outcome'] == 'IMPROVED'],
                  regressed=[r['symbol'] for r in report_rows if r['outcome'] == 'REGRESSED'],
                  rescored=[r['symbol'] for r in report_rows if r['outcome'] == 'RESCORED'],
                  causes={r['symbol']: r['cause'] for r in report_rows if r.get('cause')},
                  compile_failed=[r['symbol'] for r in report_rows if r['outcome'] == 'COMPILE_FAILED'],
                  rows=report_rows, notes=notes,
                  promotion='NONE by the sweep itself: every admission above ran promote.py fresh gates')
    if not symbols and not limit:
        write_json(OUT / 'latest.json', report)
    write_json(OUT / (run_stamp + '.json'), report)
    if not symbols and not limit:
        write_json(OUT / 'last.json', dict(stamp=run_stamp, fingerprint=fp))
    DURABLE.mkdir(parents=True, exist_ok=True)
    durable = {k: report[k] for k in ('stamp', 'fingerprint', 'seconds', 'functions_with_drafts', 'compiled', 'skipped_unchanged_key', 'derive',
                                      'counts', 'newly_exact', 'newly_body_exact', 'composition_blocked', 'improved', 'regressed', 'rescored', 'compile_failed', 'causes')}
    durable['routes'] = {r['symbol']: {k: v for k, v in r['route'].items() if k in ('action', 'command', 'component')} |
                         {k: (v.get('passed') if k == 'verify' else v.get('strict_pass') if isinstance(v, dict) else v)
                          for k, v in r['route'].items() if k in ('verify', 'compose', 'persist', 'admit')}
                         for r in report_rows if r.get('route')}
    meaningful = any(k not in ('UNCHANGED', 'RESCORED') for k in counts)
    # Durable audit only for full sweeps or real changes; triage's per-function refreshes stay in build/.
    if report['compiled'] and (not symbols or meaningful):
        write_json(DURABLE / (run_stamp + '.json'), durable)
    return report


def run_admit(args):
    cmd = [sys.executable, str(ROOT / 'tools/promote.py')] + args
    proc = subprocess.run(cmd, cwd=ROOT, capture_output=True, text=True, timeout=3600)
    return dict(command=' '.join(cmd[1:]), exit_code=proc.returncode, strict_pass=proc.returncode == 0, tail=(proc.stdout + proc.stderr)[-1500:])


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('--symbols', help='comma-separated symbols (default: every open function with a preserved draft)')
    ap.add_argument('--force', action='store_true', help='ignore the evaluation-key cache')
    ap.add_argument('--since-last', action='store_true', help='print the shared changes since the last full sweep, then sweep')
    ap.add_argument('--triggers', action='store_true', help='only report shared changes since the last full sweep')
    ap.add_argument('--derive', action='append', default=[], choices=['typedb'], help='also evaluate derived variants')
    ap.add_argument('--verify', action='store_true', help='run promote.py --verify-only on strict candidates')
    ap.add_argument('--compose', action='store_true', help='run a bounded scratch unit composition for body-exact candidates')
    ap.add_argument('--admit', action='store_true', help='supervisor only: admit candidates that passed the normal fresh gates')
    ap.add_argument('--limit', type=int, help='evaluate at most N functions (pilot)')
    args = ap.parse_args()
    if args.triggers:
        print(json.dumps(triggers(), indent=2))
        return
    if args.admit and not (args.verify or args.compose):
        raise FormatError('--admit needs --verify and/or --compose so every admission is preceded by the fresh gate')
    info = triggers() if args.since_last else None
    report = sweep(set(args.symbols.split(',')) if args.symbols else None, args.force, tuple(args.derive), args.verify, args.compose, args.admit, args.limit)
    summary = {k: report[k] for k in ('stamp', 'seconds', 'functions_with_drafts', 'compiled', 'skipped_unchanged_key', 'cache', 'counts',
                                      'newly_exact', 'newly_body_exact', 'composition_blocked', 'improved', 'regressed', 'compile_failed', 'causes')}
    if info:
        summary['shared_changes'] = {k: info[k] for k in ('last_sweep', 'changed', 'sweep_triggers')}
    summary['routes'] = {r['symbol']: r['route'] for r in report['rows'] if r.get('route')}
    summary['report'] = relative(OUT / (report['stamp'] + '.json'))
    print(json.dumps(summary, indent=2, default=str))


if __name__ == '__main__':
    try:
        main()
    except FormatError as exc:
        raise SystemExit('ERROR: ' + str(exc))
