"""Structured experiment history per function (append-only), alongside the free-text notes.

    python tools/attempts.py summary SYMBOL [--json]
    python tools/attempts.py list SYMBOL [--limit N]
    python tools/attempts.py families                      # controlled vocabulary
    python tools/attempts.py backfill [--symbols A,B]       # import build/search history + ledger notes

Every search.py session appends one record to evidence/recovery/attempts/SYMBOL.jsonl:
families (controlled vocabulary), hypothesis, prediction, falsifier, profile, inputs,
frontier before/after, first divergence before/after, outcome, report path and the
shared-state fingerprint at the time. sweep.py and permuter_queue.py append records
too. Backfilled records come from older free-text search metadata and notes; their
families are inferred by keyword and marked family_source='inferred'.

This is decision support and anti-duplication metadata, never a gate: nothing here
blocks search.py or promote.py. Notes in the drafts ledger are kept unchanged.
"""
import argparse
import hashlib
import json
import os
import re
import sys
from collections import Counter, defaultdict
from datetime import datetime, timezone
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from common import ROOT, FormatError

ATTEMPTS = ROOT / 'evidence/recovery/attempts'
LOCK = ROOT / 'build/locks/attempts.lock'
SCHEMA = 1

FAMILIES = {
    'SEMANTICS': 'observable behaviour: missing/extra calls, stores, conditions, constants (emu_diff first)',
    'TYPE': 'variable/field/global widths, char/int/long, struct shapes',
    'PROTOTYPE': 'function prototypes, argument/return types, near/far, K&R vs ANSI',
    'SIGNEDNESS': 'signed/unsigned declared types driving jl/jb and cbw/xor',
    'DECLARATION_ORDER': 'order of file-scope externs/statics/prototypes',
    'LOCAL_ORDER': 'order of local declarations',
    'REGISTER_HINT': 'adding/removing the register keyword',
    'EXPRESSION_SHAPE': 'operand order, algebraic form, addressing, casts inside expressions',
    'CSE_SUBEXPRESSION': 'repeated vs shared subexpressions, named temporaries vs recomputation (MSC7-R0: /Oe allocates subexpressions too)',
    'LOOP_STRUCTURE': 'for/while/do form, induction variables, loop nesting, exit tests',
    'CFG_STRUCTURE': 'branch polarity, if/else layout, switch form, early return, shared tails, goto',
    'LOCAL_LIFETIME': 'scope/lifetime of locals, block-local variables, splitting/merging variables',
    'FRAME_LAYOUT': 'locals that exist in the frame: arrays, structs, spare members, frame size',
    'HOME_ORDER': 'which BP home each local gets',
    'REGISTER_ALLOCATION': 'which value gets SI/DI/CX, spills and reloads (use frequency, loop weight)',
    'FAR_POINTER_LIFETIME': 'far pointer temporaries, LES reloads, ES/DX selector lifetime',
    'SELECTOR_PLACEMENT': 'selector-pool/far data bindings resolved by unit placement',
    'TU_COMPOSITION': 'unit assembly, neighbours in the object, private data placement',
    'DATA_LAYOUT': 'private DATA/BSS/CONST placement, string literals, statics',
    'COMPILER_PROFILE': 'which catalogued profile the object context uses',
    'OPTIMIZATION_PROFILE': 'reviewed per-function #pragma optimize trials',
    'STEERING': 'code-free steering constructs (EXACT_STEERED)',
    'SHARED_STATE_RESWEEP': 'unchanged draft re-evaluated after a shared change (sweep.py)',
    'PERMUTER_SEARCH': 'automated semantics-preserving mutation search (permuter.py / permuter_queue.py)',
    'OTHER': 'anything else',
    'UNSPECIFIED': 'no family recorded or inferable',
}

OUTCOMES = ('EXACT', 'BODY_EXACT', 'IMPROVED', 'NEUTRAL', 'NO_OP', 'REGRESSED', 'COMPILE_FAILED')

# Keyword inference for free-text families/notes (backfill and meta without a controlled family).
KEYWORDS = [
    ('SEMANTICS', r'semantic|behaviou?r|emu_?diff|missing call|missing region|author|missing store|wrong constant|observable'),
    ('SIGNEDNESS', r'signed|signedness|jl/jb|cbw'),
    ('PROTOTYPE', r'prototype|k&r|extern decl|return type|near/far|far/near|argument type|param(eter)? type'),
    ('TYPE', r'\btypes?\b|width|typedb|resync|narrowing|struct shape|field type'),
    ('LOCAL_ORDER', r'local (declaration )?order|locals? order|declaration order of locals|local-order'),
    ('DECLARATION_ORDER', r'declaration[- ]order|decl(aration)? order|extern order|file-scope order'),
    ('REGISTER_HINT', r'register (keyword|hint|decl)|`register`|register-hint'),
    ('CSE_SUBEXPRESSION', r'\bcse\b|subexpression|recompute|recomputation|temporar|alias|common expression'),
    ('LOOP_STRUCTURE', r'\bloop|induction|for-loop|while|do-while|interchange'),
    ('CFG_STRUCTURE', r'branch|polarity|switch|goto|control[- ]flow|\bcfg\b|else|early return|shared tail|fallthrough|block order'),
    ('LOCAL_LIFETIME', r'lifetime|liveness|scope|block-local|split|merge'),
    ('FRAME_LAYOUT', r'frame|enter \d|spare member|array extent'),
    ('HOME_ORDER', r'\bhome|stack slot|bp-|bp -|stack-home'),
    ('REGISTER_ALLOCATION', r'allocat|si/di|register choice|register residue|wrong register|spill'),
    ('FAR_POINTER_LIFETIME', r'far pointer|far-pointer|\bles\b|selector lifetime|far base|es:'),
    ('SELECTOR_PLACEMENT', r'pool|selector cell|rebind|selector-backed|placement'),
    ('TU_COMPOSITION', r'\bunit\b|compose|composer|\btu\b|translation unit|neighbou?r'),
    ('DATA_LAYOUT', r'\bbss\b|\bconst\b|data layout|string literal|static data|_data'),
    ('COMPILER_PROFILE', r'profile|/og|\bogi\b|\boi\b|/ga'),
    ('OPTIMIZATION_PROFILE', r'#pragma optimize|pragma'),
    ('STEERING', r'steer'),
    ('EXPRESSION_SHAPE', r'expression|operand order|addressing|algebra|index|shift|cast|arithmetic|operand'),
]


def now():
    return datetime.now(timezone.utc).strftime('%Y-%m-%dT%H:%M:%SZ')


def path_for(symbol, root=None):
    base = Path(root) / 'evidence/recovery/attempts' if root else ATTEMPTS
    return base / (re.sub(r'[^A-Za-z0-9_.-]', '_', symbol.lstrip('_')) + '.jsonl')


def normalize_family(value):
    """Controlled family for a declared value, or None when the value is not in the vocabulary."""
    if not value:
        return None
    key = re.sub(r'[^A-Z0-9]+', '_', str(value).upper()).strip('_')
    aliases = {'CSE': 'CSE_SUBEXPRESSION', 'SUBEXPRESSION': 'CSE_SUBEXPRESSION', 'CFG': 'CFG_STRUCTURE',
               'LOOP': 'LOOP_STRUCTURE', 'FRAME': 'FRAME_LAYOUT', 'HOME': 'HOME_ORDER', 'REGISTER': 'REGISTER_ALLOCATION',
               'ALLOCATION': 'REGISTER_ALLOCATION', 'PROFILE': 'COMPILER_PROFILE', 'PLACEMENT': 'SELECTOR_PLACEMENT',
               'DECLARATION': 'DECLARATION_ORDER', 'FAR_POINTER': 'FAR_POINTER_LIFETIME', 'PRAGMA': 'OPTIMIZATION_PROFILE',
               'LIFETIME': 'LOCAL_LIFETIME', 'COMPOSITION': 'TU_COMPOSITION', 'EXPRESSION': 'EXPRESSION_SHAPE'}
    key = aliases.get(key, key)
    return key if key in FAMILIES else None


def infer_families(text, limit=3):
    """Keyword families for free text, most specific first (heuristic; recorded as inferred)."""
    if not text:
        return []
    low = str(text).lower()
    found = []
    for family, pattern in KEYWORDS:
        if re.search(pattern, low) and family not in found:
            found.append(family)
    return found[:limit]


def families_from(declared=None, text=None):
    """(families, family_source): declared controlled values win; otherwise keyword inference."""
    values = declared if isinstance(declared, (list, tuple)) else [declared] if declared else []
    controlled = [f for f in (normalize_family(v) for v in values) if f]
    if controlled:
        return list(dict.fromkeys(controlled)), 'declared'
    inferred = infer_families(' '.join(str(v) for v in values if v) + ' ' + (text or ''))
    if inferred:
        return inferred, 'inferred'
    return ['UNSPECIFIED'], 'none'


def _lock():
    from publication import file_lock
    return file_lock(LOCK, 120, 'attempt ledger is busy')


def record(symbol, entry, root=None):
    """Append one attempt record (fills schema/time/id); returns the stored record."""
    families = entry.get('families') or ['UNSPECIFIED']
    bad = [f for f in families if f not in FAMILIES]
    if bad:
        raise FormatError('unknown attempt families: ' + ', '.join(bad))
    if entry.get('outcome') and entry['outcome'] not in OUTCOMES:
        raise FormatError('unknown attempt outcome: ' + entry['outcome'])
    row = dict(schema=SCHEMA, symbol=symbol, time=entry.get('time') or now())
    row.update(entry)
    row['id'] = row.get('id') or hashlib.sha256(json.dumps(row, sort_keys=True, default=str).encode()).hexdigest()[:12]
    path = path_for(symbol, root)
    path.parent.mkdir(parents=True, exist_ok=True)
    with _lock():
        with path.open('a', encoding='utf-8', newline='\n') as stream:
            stream.write(json.dumps(row, sort_keys=True) + '\n')
    return row


def load(symbol, root=None):
    path = path_for(symbol, root)
    if not path.exists():
        return []
    rows = []
    for line in path.read_text(encoding='utf-8').splitlines():
        try:
            rows.append(json.loads(line))
        except ValueError:
            continue
    return rows


def outcome_of(before, after, same_output=False, reevaluation=False):
    """Classify an attempt from frontier snapshots {strict, body_exact, row, opcodes}.

    A search session that stays below the stored frontier is NEUTRAL (the family did not
    help); REGRESSED is reserved for re-evaluating the SAME draft under a newer state."""
    if not after or after.get('opcodes') is None:
        return 'COMPILE_FAILED'
    if after.get('strict'):
        return 'EXACT'
    if after.get('body_exact') and not (before or {}).get('body_exact'):
        return 'BODY_EXACT'
    if same_output:
        return 'NO_OP'
    if not before or before.get('opcodes') is None:
        return 'IMPROVED'
    key_a = [bool(after.get('strict')), bool(after.get('body_exact')), after.get('row') or 0, after.get('opcodes') or 0]
    key_b = [bool(before.get('strict')), bool(before.get('body_exact')), before.get('row') or 0, before.get('opcodes') or 0]
    if key_a > key_b:
        return 'IMPROVED'
    if reevaluation and key_a < key_b:
        return 'REGRESSED'
    return 'NEUTRAL'


def stale_components(row, current_fp, components=None):
    """Shared-state components that changed since the attempt (its conclusion may be stale)."""
    import shared_state
    old = row.get('state') or {}
    if not old:
        return []
    return shared_state.changed(old, current_fp, components or shared_state.CONCLUSION)


def summary(symbol, root=None, current_fp=None, rows=None):
    """Per-family aggregate: attempts, variants, outcomes, best gain, last time, stale flag."""
    rows = load(symbol, root) if rows is None else rows
    # The ledger is append-only: a later record with `corrects: ID` replaces that record.
    corrected = {r['corrects'] for r in rows if r.get('corrects')}
    rows = [r for r in rows if r.get('id') not in corrected]
    per = defaultdict(lambda: dict(attempts=0, variants=0, outcomes=Counter(), best_gain=None, last=None,
                                   declared=0, inferred=0, stale=False, stale_components=set(), hypotheses=[]))
    for row in rows:
        gain = None
        b, a = row.get('before') or {}, row.get('after') or {}
        if a.get('opcodes') is not None and b.get('opcodes') is not None:
            gain = a['opcodes'] - b['opcodes']
        stale = stale_components(row, current_fp) if current_fp else []
        for fam in row.get('families') or ['UNSPECIFIED']:
            p = per[fam]
            p['attempts'] += int(row.get('aggregate_sessions') or 1)
            p['variants'] += int(row.get('candidates') or 1)
            p['outcomes'][row.get('outcome') or 'NEUTRAL'] += 1
            if gain is not None and (p['best_gain'] is None or gain > p['best_gain']):
                p['best_gain'] = gain
            if not p['last'] or (row.get('time') or '') > p['last']:
                p['last'] = row.get('time')
            p['declared' if row.get('family_source') == 'declared' else 'inferred'] += 1
            if row.get('hypothesis') and len(p['hypotheses']) < 3:
                p['hypotheses'].append(row['hypothesis'][:120])
            if stale:
                p['stale_components'].update(stale)
    result = {}
    for fam, p in per.items():
        out = p['outcomes']
        productive = out['EXACT'] + out['BODY_EXACT'] + out['IMPROVED']
        # Keyword-inferred rows are weaker evidence than declared families: two count as one.
        weight = p['declared'] + p['inferred'] / 2.0
        verdict = ('EXACT' if out['EXACT'] else 'PRODUCTIVE' if productive else
                   'NO_EFFECT' if out['NO_OP'] and out['NO_OP'] >= p['attempts'] - out['COMPILE_FAILED'] else
                   'EXHAUSTED' if weight >= 3 else 'TRIED')
        result[fam] = dict(attempts=p['attempts'], variants=p['variants'], outcomes=dict(out), best_gain=p['best_gain'],
                           last=p['last'], verdict=verdict, declared=p['declared'], inferred=p['inferred'],
                           stale_since=sorted(p['stale_components']) or None, examples=p['hypotheses'])
    return result


def summary_lines(fam_summary, relevant=None):
    """Compact human view: one line per family, untried relevant families listed."""
    lines = []
    for fam, s in sorted(fam_summary.items(), key=lambda kv: (-kv[1]['attempts'], kv[0])):
        gain = '' if s['best_gain'] is None else (', best %+d opcodes' % s['best_gain']) if s['best_gain'] > 0 else ', no opcode gain'
        stale = '' if not s['stale_since'] else ' [stale: %s changed since]' % ','.join(s['stale_since'])
        src = '' if not s['inferred'] else ' (%d inferred)' % s['inferred']
        lines.append('%s: %d sessions / %d variants, %s%s%s%s' % (fam, s['attempts'], s['variants'], s['verdict'].lower().replace('_', ' '), gain, src, stale))
    for fam in relevant or []:
        if fam not in fam_summary:
            lines.append('%s: not tried' % fam)
    return lines


def snapshot_from_key(key, extra=None):
    """Frontier snapshot from a drafts.frontier_rank key [strict, body, row, opcodes]."""
    if not key or len(key) < 4:
        return None
    snap = dict(strict=bool(key[0]), body_exact=bool(key[1]), row=key[2], opcodes=key[3])
    snap.update({k: v for k, v in (extra or {}).items() if v is not None})
    return snap


def ledger_snapshot(entry):
    """Current stored frontier (or best) of a drafts-ledger entry as a snapshot."""
    front = (entry or {}).get('frontier')
    if front and front.get('key'):
        return snapshot_from_key(front['key'], dict(opcode_total=front.get('opcode_total'), divergence_class=front.get('first_divergence_class'),
                                                    draft=front.get('sha256', '')[:12] or None))
    best = (entry or {}).get('best')
    if best and best.get('opcode_matches') is not None:
        return dict(strict=best.get('result') in ('CONFIRMED_MEMBER', 'STRONGLY_SUPPORTED_MEMBER'), body_exact=bool((best.get('key') or [0, 0])[1]),
                    row=None, opcodes=best['opcode_matches'], opcode_total=best.get('opcode_total'), draft=best.get('sha256', '')[:12] or None)
    return None


def advice(symbol, families, why_repeat=None, current_fp=None, fam_summary=None):
    """Decision support: warn when a family was already exhausted or had no effect and nothing changed."""
    if why_repeat:
        return []
    fam_summary = summary(symbol, current_fp=current_fp) if fam_summary is None else fam_summary
    out = []
    for fam in families:
        s = fam_summary.get(fam)
        if s and s['verdict'] in ('EXHAUSTED', 'NO_EFFECT') and not s['stale_since']:
            out.append('%s was already tried for %s (%d sessions, %s) and no shared state changed since; prefer an untried family, '
                       'or pass --why-repeat naming the new fact, tool or evidence' % (fam, symbol, s['attempts'], s['verdict'].lower()))
    return out


def session_entry(meta=None, families=None, hypothesis=None, prediction=None, falsifier=None, why_repeat=None, note=None):
    """Merge search.py --meta JSON and CLI fields into attempt fields with controlled families."""
    meta = dict(meta or {})
    declared = list(families or []) + ([meta['families']] if isinstance(meta.get('families'), str) else list(meta.get('families') or []))
    if meta.get('family'):
        declared.append(meta['family'])
    hyp = hypothesis or meta.get('hypothesis') or meta.get('transformation')
    text = ' '.join(str(x) for x in (hyp, meta.get('family'), note) if x)
    fams, source = families_from(declared, text)
    unknown = [str(d) for d in declared if d and not normalize_family(d)]
    return dict(families=fams, family_source=source, family_text=('; '.join(unknown)[:200] or None),
                hypothesis=(str(hyp)[:400] if hyp else (note[:400] if note else None)),
                prediction=(str(prediction or meta.get('prediction'))[:300] if (prediction or meta.get('prediction')) else None),
                falsifier=(str(falsifier or meta.get('falsifier'))[:300] if (falsifier or meta.get('falsifier')) else None),
                why_repeat=(why_repeat or meta.get('why_repeat') or meta.get('reason_for_repeat')),
                declared_verdict=meta.get('verdict'))


# ---------------------------------------------------------------- backfill

def _score(row):
    try:
        return int(str(row.get('opcodes')).split('/')[0])
    except (TypeError, ValueError):
        return None


def backfill(symbols=None, root=ROOT):
    """Import build/search/*/history.jsonl sessions and drafts-ledger notes as inferred attempts.

    Idempotent: each imported session/note carries a source key; already imported keys are skipped."""
    import drafts
    from common import cards
    ledger = drafts.load()
    card_symbols = {c['symbol'] for c in cards()}

    def canon(name):
        return name if name in card_symbols else '_' + name if '_' + name in card_symbols else name

    search_root = Path(root) / 'build/search'
    names = set()
    if search_root.is_dir():
        names.update(canon(p.parent.name) for p in search_root.glob('*/history.jsonl'))
    notes_by_symbol = defaultdict(list)
    for key, row in ledger.items():
        names.add(canon(key))
        notes_by_symbol[canon(key)].extend(row.get('notes', []))
    if symbols:
        wanted = {canon(x) for x in symbols} | set(symbols)
        names = {s for s in names if s in wanted}
    written = Counter()
    for symbol in sorted(names):
        plain = symbol.lstrip('_')
        existing = {r.get('source_key') for r in load(symbol, root if root != ROOT else None)}
        new_rows = []
        hist = search_root / plain / 'history.jsonl'
        best = None
        seen_objects = set()
        unlabelled = dict(sessions=0, candidates=0, no_op=0, improved=0, first=None, last=None, best_before=None, best_after=None)
        if hist.is_file():
            for line in hist.read_text(encoding='utf-8').splitlines():
                try:
                    h = json.loads(line)
                except ValueError:
                    continue
                rows = h.get('rows') or []
                scores = [s for s in (_score(r) for r in rows) if s is not None]
                after = max(scores) if scores else None
                objects = {r.get('object') for r in rows if r.get('object')}
                same = bool(objects) and objects <= seen_objects
                seen_objects |= objects
                strict = any(r.get('result') in drafts.GOOD for r in rows)
                body = any(r.get('exact_body') for r in rows)
                before_s = dict(opcodes=best) if best is not None else None
                after_s = dict(opcodes=after, strict=strict, body_exact=body) if after is not None else None
                outcome = outcome_of(before_s, after_s, same)
                meta = h.get('meta') or {}
                text = ' '.join(str(meta.get(k, '')) for k in ('family', 'families', 'hypothesis', 'prediction')) + ' ' + (h.get('note') or '')
                key = 'search:%s' % h.get('time')
                if meta or h.get('note'):
                    if key not in existing:
                        fams, source = families_from(meta.get('families') or meta.get('family'), text)
                        new_rows.append(dict(time=_iso(h.get('time')), worker=_worker(h), families=fams, family_source='inferred' if source != 'declared' else 'declared',
                                             family_text=str(meta.get('family') or '')[:200] or None, hypothesis=(meta.get('hypothesis') or h.get('note') or '')[:240] or None,
                                             prediction=(str(meta.get('prediction'))[:160] if meta.get('prediction') else None),
                                             falsifier=(str(meta.get('falsifier'))[:160] if meta.get('falsifier') else None),
                                             candidates=len(rows), distinct_outputs=len(objects), before=before_s, after=after_s,
                                             outcome=outcome, report=h.get('report'), source_key=key, backfilled=True))
                else:
                    u = unlabelled
                    u['sessions'] += 1; u['candidates'] += len(rows); u['no_op'] += int(same)
                    u['improved'] += int(outcome in ('IMPROVED', 'EXACT', 'BODY_EXACT'))
                    u['first'] = u['first'] or _iso(h.get('time')); u['last'] = _iso(h.get('time'))
                    u['best_before'] = best if u['best_before'] is None else u['best_before']
                if after is not None and (best is None or after > best):
                    best = after
                unlabelled['best_after'] = best
        if unlabelled['sessions']:
            key = 'search-unlabelled:%s' % unlabelled['last']
            if key not in existing and not any(k and k.startswith('search-unlabelled:') for k in existing):
                new_rows.append(dict(time=unlabelled['last'], worker='backfill', families=['UNSPECIFIED'], family_source='none',
                                     hypothesis='%d search sessions without --meta or --note (%d candidates, %d identical to earlier output)'
                                                % (unlabelled['sessions'], unlabelled['candidates'], unlabelled['no_op']),
                                     candidates=unlabelled['candidates'], aggregate_sessions=unlabelled['sessions'],
                                     before=dict(opcodes=unlabelled['best_before']) if unlabelled['best_before'] is not None else None,
                                     after=dict(opcodes=unlabelled['best_after']) if unlabelled['best_after'] is not None else None,
                                     outcome='IMPROVED' if unlabelled['improved'] else 'NEUTRAL', source_key=key, backfilled=True))
        for n in notes_by_symbol.get(symbol, []):
            if str(n.get('origin') or '').startswith('build/search/') and hist.is_file():
                continue  # the search session carrying this note was imported above
            key = 'note:%s:%s' % (n.get('recorded'), hashlib.sha256((n.get('text') or '').encode()).hexdigest()[:8])
            if key in existing:
                continue
            fams, source = families_from(None, n.get('text'))
            new_rows.append(dict(time=n.get('recorded'), worker=_origin_worker(n.get('origin')), families=fams, family_source='inferred' if fams != ['UNSPECIFIED'] else 'none',
                                 hypothesis=(n.get('text') or '')[:240], kind='note', candidates=0, outcome='NEUTRAL', source_key=key,
                                 report=n.get('origin'), backfilled=True))
        if new_rows:
            path = path_for(symbol, root if root != ROOT else None)
            path.parent.mkdir(parents=True, exist_ok=True)
            with _lock():
                with path.open('a', encoding='utf-8', newline='\n') as stream:
                    for r in new_rows:
                        r = dict(schema=SCHEMA, symbol=symbol, **r)
                        r['id'] = hashlib.sha256(json.dumps(r, sort_keys=True, default=str).encode()).hexdigest()[:12]
                        stream.write(json.dumps(r, sort_keys=True) + '\n')
            written[symbol] = len(new_rows)
    return dict(symbols=len(written), records=sum(written.values()))


def _iso(stamp):
    if not stamp:
        return None
    m = re.match(r'^(\d{4})(\d{2})(\d{2})T(\d{2})(\d{2})(\d{2})', str(stamp))
    return '%s-%s-%sT%s:%s:%sZ' % m.groups() if m else str(stamp)


def _worker(h):
    for r in h.get('rows') or []:
        m = re.search(r'build[/\\]workers[/\\]([^/\\]+)', str(r.get('input') or ''))
        if m:
            return m.group(1)
    return None


def _origin_worker(origin):
    m = re.search(r'build[/\\]workers[/\\]([^/\\]+)', str(origin or ''))
    return m.group(1) if m else None


def current_worker(paths=()):
    """Worker name from $SIMANTW_WORKER or a build/workers/NAME/ input path."""
    if os.environ.get('SIMANTW_WORKER'):
        return os.environ['SIMANTW_WORKER']
    for p in paths:
        m = re.search(r'build[/\\]workers[/\\]([^/\\]+)', str(Path(p).resolve()) if p else '')
        if m:
            return m.group(1)
    return None


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = ap.add_subparsers(dest='command', required=True)
    p = sub.add_parser('summary'); p.add_argument('symbol'); p.add_argument('--json', action='store_true')
    p = sub.add_parser('list'); p.add_argument('symbol'); p.add_argument('--limit', type=int, default=30)
    sub.add_parser('families')
    p = sub.add_parser('backfill'); p.add_argument('--symbols')
    args = ap.parse_args()
    if args.command == 'families':
        print(json.dumps(FAMILIES, indent=2))
    elif args.command == 'summary':
        import shared_state
        s = summary(args.symbol, current_fp=shared_state.fingerprint())
        print(json.dumps(s, indent=2) if args.json else '\n'.join(summary_lines(s)) or 'no recorded attempts')
    elif args.command == 'list':
        for r in load(args.symbol)[-args.limit:]:
            print(json.dumps({k: r.get(k) for k in ('time', 'worker', 'families', 'outcome', 'before', 'after', 'hypothesis')}))
    elif args.command == 'backfill':
        print(json.dumps(backfill(set(args.symbols.split(',')) if args.symbols else None), indent=2))


if __name__ == '__main__':
    try:
        main()
    except FormatError as exc:
        raise SystemExit('ERROR: ' + str(exc))
