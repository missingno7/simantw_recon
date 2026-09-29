"""Evidence-gated parking for functions with a documented stagnant frontier.

    python tools/parking.py candidates [--root REPO] [--note-rounds N]
    python tools/parking.py park SYMBOL --class CLASS --reason TEXT
    python tools/parking.py reopen SYMBOL --because TEXT
    python tools/parking.py reopen --class CLASS --because TEXT
    python tools/parking.py list [--all]
    python tools/parking.py status [SYMBOL]

A frontier is ordered by drafts.frontier_rank: strict/body status, the earliest
meaningful divergence row (as classified by residue_clusters.classify), then
aligned opcode matches. The session rule requires two latest readable search
reports whose best rank does not exceed the stored frontier and whose sessions
both began after that frontier was recorded. The alternate note rule requires
N notes recorded after the current frontier (default 10). A proposal also needs
a readable, classifiable first divergence. Parking is assignment metadata only.
"""
import argparse
import json
import re
import sys
from datetime import date, datetime, timezone
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from common import ROOT, FormatError, read_json, write_json

PARKING_PATH = ROOT / 'layout/parking.json'
VOCABULARY = (
    'REGISTER_ALLOCATION', 'HOME_ORDER', 'FRAME_SIZE', 'SELECTOR_LIFETIME',
    'EXPRESSION_SHAPE', 'CFG_LAYOUT', 'PLACEMENT', 'SEMANTICS',
    'MISSING_HELPER', 'PROFILE', 'DATA_LAYOUT', 'TOOL_LIMIT',
)
RULE = (
    'Propose a function when its two latest readable search sessions both have '
    'frontier_rank <= the stored frontier rank and both began after the stored '
    'frontier timestamp, OR when at least N notes were recorded after that '
    'frontier timestamp (N defaults to 10). A proposal also requires an open '
    'GAME function and a readable first meaningful divergence classified by '
    'residue_clusters.classify. frontier_rank orders strict/body status, later '
    'first-divergence row, then opcode matches.'
)

REOPEN_KEYS = {
    'REGISTER_ALLOCATION': ['MSC7_REGISTER_ALLOCATION_RULE', 'NEW_COMPILER_TOOL', 'NEW_MACHINE_EVIDENCE'],
    'HOME_ORDER': ['MSC7_HOME_ORDER_RULE', 'NEW_FRAME_EVIDENCE', 'NEW_COMPILER_TOOL'],
    'FRAME_SIZE': ['MSC7_FRAME_RULE', 'NEW_PROFILE_EVIDENCE', 'NEW_COMPILER_TOOL'],
    'SELECTOR_LIFETIME': ['SELECTOR_LIFETIME_MECHANISM', 'NEW_UNIT_EVIDENCE', 'NEW_COMPILER_TOOL'],
    'EXPRESSION_SHAPE': ['MSC7_EXPRESSION_RULE', 'NEW_SOURCE_MECHANISM', 'NEW_COMPILER_TOOL'],
    'CFG_LAYOUT': ['CFG_LAYOUT_MECHANISM', 'NEW_CONTROL_FLOW_EVIDENCE', 'NEW_COMPILER_TOOL'],
    'PLACEMENT': ['UNIT_PLACEMENT_EVIDENCE', 'NEW_LINK_EVIDENCE', 'NEW_COMPILER_TOOL'],
    'SEMANTICS': ['NEW_SEMANTIC_EVIDENCE', 'MISSING_SOURCE_FACT', 'NEW_COMPILER_TOOL'],
    'MISSING_HELPER': ['HELPER_RECOVERY', 'NEW_SYMBOL_EVIDENCE', 'NEW_COMPILER_TOOL'],
    'PROFILE': ['COMPILER_PROFILE_EVIDENCE', 'NEW_PROFILE_PROBE', 'NEW_COMPILER_TOOL'],
    'DATA_LAYOUT': ['DATA_LAYOUT_EVIDENCE', 'NEW_UNIT_EVIDENCE', 'NEW_COMPILER_TOOL'],
    'TOOL_LIMIT': ['NEW_TOOL_VERSION', 'NEW_TOOL_CAPABILITY', 'NEW_MACHINE_EVIDENCE'],
}

DIAGNOSTIC_CLASS = {
    'WRONG_REGISTER': 'REGISTER_ALLOCATION',
    'WRONG_STACK_SLOT': 'HOME_ORDER',
    'RELOAD_OR_SPILL': 'HOME_ORDER',
    'FRAME_SIZE': 'FRAME_SIZE',
    'FAR_POINTER': 'SELECTOR_LIFETIME',
    'CFG_DESTINATION': 'CFG_LAYOUT',
    'BLOCK_ORDER': 'CFG_LAYOUT',
    'EXPRESSION_SHAPE': 'EXPRESSION_SHAPE',
    'SIGNEDNESS': 'EXPRESSION_SHAPE',
    'FLAG_TEST': 'EXPRESSION_SHAPE',
    'CALL_SEQUENCE': 'EXPRESSION_SHAPE',
    'RELOCATION_ONLY': 'PLACEMENT',
}


def parking_path(root=ROOT):
    return Path(root) / 'layout/parking.json'


def load_parking(root=ROOT):
    path = parking_path(root)
    return read_json(path) if path.exists() else {}


def save_parking(value, root=ROOT):
    write_json(parking_path(root), value)


def _parking_lock(root):
    from publication import file_lock
    return file_lock(Path(root) / 'build/locks/parking.lock', 120, 'parking ledger is busy')


def is_active(record):
    """Old-shaped records default to active; reopened records remain auditable."""
    return bool(record) and record.get('active', True) and not record.get('reopened')


def active_symbols(records):
    return {symbol for symbol, record in records.items() if is_active(record)}


def _parse_time(value):
    if not value:
        return None
    # Parse the search.py ID before fromisoformat: its trailing PID can resemble
    # a compact UTC offset to Python's permissive ISO parser.
    if re.match(r'^\d{8}T\d{6}-\d+$', str(value)):
        try:
            return datetime.strptime(str(value)[:15], '%Y%m%dT%H%M%S').replace(tzinfo=timezone.utc)
        except ValueError:
            return None
    try:
        parsed = datetime.fromisoformat(value.replace('Z', '+00:00'))
        return parsed if parsed.tzinfo else parsed.replace(tzinfo=timezone.utc)
    except (ValueError, AttributeError):
        pass
    # search.py session IDs are UTC YYYYMMDDTHHMMSS-PID.
    try:
        return datetime.strptime(value[:15], '%Y%m%dT%H%M%S').replace(tzinfo=timezone.utc)
    except (ValueError, TypeError):
        return None


def _report_path(repo_root, report):
    if not report:
        return None
    path = Path(report)
    return path if path.is_absolute() else Path(repo_root) / path


def _load_result_rows(repo_root, report):
    path = _report_path(repo_root, report)
    if not path or not path.is_file():
        return []
    try:
        value = read_json(path)
    except (OSError, ValueError):
        return []
    return value.get('results') or []


def _frontier_row(repo_root, entry):
    """Return the stored frontier comparison row when its search report survives."""
    frontier = entry.get('frontier') or entry.get('best') or {}
    rows = _load_result_rows(repo_root, frontier.get('origin'))
    candidate = frontier.get('candidate')
    found = next((r for r in rows if candidate is not None and r.get('candidate') == candidate), None)
    if found is None:
        found = next((r for r in rows if (r.get('comparison', {}).get('diagnostic') or {}).get('opcode_matches') == frontier.get('opcode_matches')), None)
    return frontier, found


def _comparison_rank(comparison):
    import drafts
    try:
        return drafts.frontier_rank(comparison)
    except (KeyError, TypeError, ValueError):
        return None


def _session_frontier(repo_root, session):
    best_rank, best_row = None, None
    for row in _load_result_rows(repo_root, session.get('report')):
        comparison = row.get('comparison') or {}
        rank = _comparison_rank(comparison)
        if rank is not None and (best_rank is None or rank > best_rank):
            best_rank, best_row = rank, row
    return best_rank, best_row


def _history(repo_root, symbol):
    path = Path(repo_root) / 'build/search' / symbol.lstrip('_') / 'history.jsonl'
    if not path.is_file():
        return []
    records = []
    for line in path.read_text(encoding='utf-8').splitlines():
        try:
            row = json.loads(line)
        except ValueError:
            continue
        records.append(row)
    records.sort(key=lambda row: _parse_time(row.get('time')) or datetime.min.replace(tzinfo=timezone.utc))
    # Most old reports are large. Only the latest readable two sessions matter;
    # walk backwards and stop as soon as those two have diagnostic ranks.
    sessions = []
    for row in reversed(records):
        rank, best = _session_frontier(repo_root, row)
        if rank is not None:
            sessions.append(dict(time=row.get('time'), report=row.get('report'), rank=rank,
                                 best_candidate=(best or {}).get('candidate')))
            if len(sessions) == 2:
                break
    return list(reversed(sessions))


def _stagnation(repo_root, symbol, entry, note_rounds):
    if note_rounds < 1:
        raise FormatError('note-rounds must be positive')
    frontier = entry.get('frontier') or entry.get('best') or {}
    stored_rank = frontier.get('key')
    frontier_time = _parse_time(frontier.get('recorded'))
    notes = entry.get('notes') or []
    notes_after = ([n for n in notes if _parse_time(n.get('recorded')) and _parse_time(n['recorded']) > frontier_time]
                   if frontier_time else [])
    notes_stagnant = len(notes_after) >= note_rounds
    history = [] if notes_stagnant else _history(repo_root, symbol)
    last_two = history[-2:]
    sessions_stagnant = bool(
        len(last_two) == 2 and stored_rank and frontier_time and
        all(_parse_time(s.get('time')) and _parse_time(s['time']) > frontier_time and s.get('rank') <= stored_rank
            for s in last_two)
    )
    if sessions_stagnant:
        basis = 'last_two_sessions_no_frontier_improvement'
    elif notes_stagnant:
        basis = 'note_rounds_since_frontier'
    else:
        basis = None
    return dict(qualified=bool(basis), basis=basis, note_rounds_after_frontier=len(notes_after),
                note_round_threshold=note_rounds, sessions=last_two,
                frontier_recorded=frontier.get('recorded'), stored_rank=stored_rank)


def _residue(repo_root, entry):
    import residue_clusters
    frontier, row = _frontier_row(repo_root, entry)
    comparison = (row or {}).get('comparison') or {}
    diagnostic = comparison.get('diagnostic') or {}
    rows = diagnostic.get('aligned_asm') or []
    kind, index, first = residue_clusters.classify(rows)
    if index is None and kind == 'RELOCATION_ONLY':
        # All opcodes agree, so the causal residue is the first aligned row
        # whose operands differ only because of selector/data placement.
        first = next((r for r in rows if r.get('differences')), None)
        if first is not None:
            index = first.get('alignment_index', rows.index(first))
    if index is None:
        return None, frontier, row
    blocker = DIAGNOSTIC_CLASS.get(kind)
    if not blocker:
        return None, frontier, row
    return dict(diagnostic_class=kind, first_divergence_row=index,
                target=(first or {}).get('target'), candidate=(first or {}).get('candidate'),
                differences=(first or {}).get('differences', [])), frontier, row


def _open_game_symbols(repo_root):
    cards_path = Path(repo_root) / 'evidence/disassembly/cards.jsonl'
    recovery_path = Path(repo_root) / 'src/recovery.json'
    if not cards_path.is_file() or not recovery_path.is_file():
        return None
    targets = read_json(recovery_path).get('targets', {})
    review_path = Path(repo_root) / 'layout/ownership-review.json'
    review = read_json(review_path).get('symbols', {}) if review_path.is_file() else {}
    symbols = set()
    for line in cards_path.read_text(encoding='utf-8').splitlines():
        try:
            card = json.loads(line)
        except ValueError:
            continue
        symbol = card.get('symbol')
        ownership = review.get(symbol, {}).get('ownership', card.get('ownership'))
        if symbol and ownership == 'GAME' and symbol not in targets:
            symbols.add(symbol)
    return symbols


def candidates(repo_root=ROOT, note_rounds=10, parked=()):
    """Build proposals without changing the parking ledger."""
    if note_rounds < 1:
        raise FormatError('note-rounds must be positive')
    root = Path(repo_root)
    index_path = root / 'evidence/recovery/drafts/index.json'
    ledger = read_json(index_path) if index_path.is_file() else {}
    open_symbols = _open_game_symbols(root)
    parked = set(parked)
    proposed, skipped = {}, {}
    for symbol, entry in ledger.items():
        canonical = symbol if str(symbol).startswith('_') else '_' + str(symbol)
        if open_symbols is not None and canonical not in open_symbols:
            continue
        if symbol in parked or canonical in parked:
            continue
        stagnation = _stagnation(root, canonical, entry, note_rounds)
        if not stagnation['qualified']:
            continue
        residue, frontier, result_row = _residue(root, entry)
        if residue is None:
            skipped[canonical] = 'stagnation evidence qualifies, but no readable classifiable first divergence is available'
            continue
        blocker = DIAGNOSTIC_CLASS[(residue['diagnostic_class'])]
        notes = entry.get('notes') or []
        later_notes = [n for n in notes if not stagnation.get('frontier_recorded') or
                       (_parse_time(n.get('recorded')) and _parse_time(n['recorded']) > _parse_time(stagnation['frontier_recorded']))]
        probe_notes = [n for n in notes if re.search(r'probe|permuter|compiler experiment', (n.get('text', '') + ' ' + n.get('origin', '')), re.I)]
        opcode_matches = frontier.get('opcode_matches')
        opcode_total = frontier.get('opcode_total')
        proposed[canonical] = dict(
            blocker_class=blocker,
            residue=residue,
            frontier=dict(draft=frontier.get('source'), opcodes='%s/%s' % (opcode_matches, opcode_total)
                          if opcode_matches is not None and opcode_total is not None else None,
                          rank=frontier.get('key'), first_divergence_row=frontier.get('first_divergence_row')),
            evidence=dict(notes=later_notes, probes=probe_notes, stagnation=stagnation),
            reopen_on=list(REOPEN_KEYS[blocker]),
        )
    return dict(rule=RULE, note_rounds=note_rounds, source=str(root), candidates=proposed, skipped=skipped)


def _validate_class(blocker_class):
    if blocker_class not in VOCABULARY:
        raise FormatError('unknown blocker class %r; choose one of %s' % (blocker_class, ', '.join(VOCABULARY)))


def park_symbol(symbol, blocker_class, reason, root=ROOT, evidence_root=None, note_rounds=10):
    _validate_class(blocker_class)
    reason = (reason or '').strip()
    if not reason:
        raise FormatError('park requires a specific --reason')
    evidence_root = Path(evidence_root or root)
    index_path = evidence_root / 'evidence/recovery/drafts/index.json'
    ledger = read_json(index_path) if index_path.is_file() else {}
    entry = ledger.get(symbol) or ledger.get(symbol.lstrip('_'))
    if not entry:
        raise FormatError('no draft ledger evidence for %s' % symbol)
    open_symbols = _open_game_symbols(evidence_root)
    canonical = symbol if symbol.startswith('_') else '_' + symbol
    if open_symbols is None or canonical not in open_symbols:
        raise FormatError('%s is not verified as an open GAME function in the evidence repository' % symbol)
    stagnation = _stagnation(evidence_root, canonical, entry, note_rounds)
    if not stagnation['qualified']:
        raise FormatError('%s does not meet the parking rule: two stagnant readable sessions or %d notes after its frontier' %
                          (symbol, note_rounds))
    residue, frontier, result_row = _residue(evidence_root, entry)
    if residue is None:
        raise FormatError('cannot park %s: frontier has no readable first meaningful divergence' % symbol)
    notes = list(entry.get('notes') or [])
    notes.append(dict(text=reason, origin='parking.py park', recorded=datetime.now(timezone.utc).isoformat()))
    probe_notes = [n for n in notes if re.search(r'probe|permuter|compiler experiment', (n.get('text', '') + ' ' + n.get('origin', '')), re.I)]
    record = dict(blocker_class=blocker_class, residue=residue,
                  frontier=dict(draft=frontier.get('source'),
                                opcodes='%s/%s' % (frontier.get('opcode_matches'), frontier.get('opcode_total'))
                                if frontier.get('opcode_matches') is not None and frontier.get('opcode_total') is not None else None,
                                rank=frontier.get('key'), first_divergence_row=frontier.get('first_divergence_row')),
                  evidence=dict(notes=notes, probes=probe_notes, stagnation=stagnation), parked=date.today().isoformat(),
                  reopen_on=list(REOPEN_KEYS[blocker_class]), active=True)
    import shared_state
    # Shared-state fingerprint at parking time: triage lists the components that changed since
    # as reopen candidates (a hint; reopening still needs an explicit --because).
    record['state'] = shared_state.fingerprint(root)
    with _parking_lock(root):
        records = load_parking(root)
        old = records.get(symbol) or {}
        record['reopen_history'] = list(old.get('reopen_history') or [])
        records[symbol] = record
        save_parking(records, root)
    return record


def _reopen_one(records, symbol, because):
    record = records.get(symbol)
    if not is_active(record):
        return False
    event = dict(at=datetime.now(timezone.utc).isoformat(), because=because)
    record.setdefault('reopen_history', []).append(event)
    record['reopened'] = event
    record['active'] = False
    return True


def reopen(symbol=None, blocker_class=None, because='', root=ROOT):
    if bool(symbol) == bool(blocker_class):
        raise FormatError('give exactly one of SYMBOL or --class CLASS')
    if blocker_class:
        _validate_class(blocker_class)
    because = (because or '').strip()
    if len(because) < 8:
        raise FormatError('--because must identify the new fact or tool (at least 8 characters)')
    with _parking_lock(root):
        records = load_parking(root)
        if symbol:
            symbols = [symbol]
        else:
            symbols = [s for s, r in records.items() if is_active(r) and r.get('blocker_class') == blocker_class]
        reopened = [s for s in symbols if _reopen_one(records, s, because)]
        if symbol and not reopened:
            raise FormatError('%s is not actively parked' % symbol)
        if blocker_class and not reopened:
            raise FormatError('no actively parked functions under %s' % blocker_class)
        save_parking(records, root)
    return dict(reopened=reopened, because=because)


def status(symbol=None, root=ROOT, include_all=False):
    records = load_parking(root)
    if symbol:
        record = records.get(symbol)
        if record is None:
            return dict(symbol=symbol, status='NOT_PARKED')
        return dict(symbol=symbol, status='PARKED' if is_active(record) else 'REOPENED', record=record)
    selected = {s: r for s, r in records.items() if include_all or is_active(r)}
    counts = {key: sum(1 for r in selected.values() if r.get('blocker_class') == key and is_active(r)) for key in VOCABULARY}
    return dict(count=len(selected), active=sum(is_active(r) for r in selected.values()), by_class={k: v for k, v in counts.items() if v}, functions=selected)


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = ap.add_subparsers(dest='command', required=True)
    p = sub.add_parser('candidates', help='propose stagnant open functions without parking them')
    p.add_argument('--root', type=Path, default=ROOT, help='repository whose read-only ledger and search history are analyzed')
    p.add_argument('--note-rounds', type=int, default=10, help='stagnant notes since frontier needed by the alternate rule (default: 10)')
    p.add_argument('--output', type=Path, help='write proposal JSON to this path')
    p = sub.add_parser('park', help='park one function with current diagnostic residue and a reason')
    p.add_argument('symbol')
    p.add_argument('--class', dest='blocker_class', required=True, choices=VOCABULARY)
    p.add_argument('--reason', required=True)
    p.add_argument('--evidence-root', type=Path, help='read the draft ledger from another repository')
    p.add_argument('--note-rounds', type=int, default=10, help='same note threshold used by candidates (default: 10)')
    p = sub.add_parser('reopen', help='reopen one function or every function in a blocker class')
    p.add_argument('symbol', nargs='?')
    p.add_argument('--class', dest='blocker_class', choices=VOCABULARY)
    p.add_argument('--because', required=True, help='new mechanism-level fact or tool that justifies reopening')
    p = sub.add_parser('list', help='list active parked functions')
    p.add_argument('--all', action='store_true', help='include reopened records')
    p = sub.add_parser('status', help='show one record or active counts by class')
    p.add_argument('symbol', nargs='?')
    args = ap.parse_args(argv)
    if args.command == 'candidates':
        result = candidates(args.root, args.note_rounds, active_symbols(load_parking()))
        if args.output:
            try:
                args.output.resolve().relative_to(ROOT.resolve())
            except ValueError as exc:
                raise FormatError('candidate output must stay inside this worktree') from exc
            write_json(args.output, result)
            result = dict(rule=result['rule'], source=result['source'], note_rounds=result['note_rounds'],
                          candidate_count=len(result['candidates']), skipped_count=len(result['skipped']),
                          output=str(args.output))
    elif args.command == 'park':
        result = dict(symbol=args.symbol, status='PARKED', record=park_symbol(args.symbol, args.blocker_class, args.reason,
                                                                              evidence_root=args.evidence_root, note_rounds=args.note_rounds))
    elif args.command == 'reopen':
        result = reopen(args.symbol, args.blocker_class, args.because)
    elif args.command == 'list':
        result = status(root=ROOT, include_all=args.all)
    else:
        result = status(args.symbol)
    print(json.dumps(result, indent=2))


if __name__ == '__main__':
    try:
        main()
    except (FormatError, FileNotFoundError) as exc:
        raise SystemExit('ERROR: ' + str(exc))
