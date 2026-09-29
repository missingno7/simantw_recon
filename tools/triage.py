"""Evidence-based next action for an open function (or the whole backlog).

    python tools/triage.py SYMBOL [--json] [--typedb] [--emu]
    python tools/triage.py --open [--lane LANE] [--limit N] [--json OUT]

Combines what a worker otherwise re-derives by hand:
  - best/frontier drafts and their CURRENT evaluation (build/sweep/diagnostics, written by sweep.py);
  - the first meaningful divergence (residue_clusters.classify) and diagnostic counts;
  - body-exact / strict status, relocation-only residue, the assigned compiler profile;
  - parking status, the structured attempt history (tools/attempts.py) and what went stale since;
  - the unit/component, its admitted unit and its current owner (tools/unit_owner.py);
  - relevant MSC 7.00 fact-register entries (FALSIFIED ones are listed as "do not retry");
  - typedb disagreement (sweep's resynced variant, or --typedb for a live check);
  - emu_diff verdict (cached build/emu_diff/SYMBOL.json, or --emu to run 20 samples);
  - Mac SimAnt correspondence when a structural pair exists (supporting evidence only).

It then recommends a blocker class, the next tool, the next hypothesis families
(untried first), and a lane:
  PROMOTE              strict candidate: run promote.py (fresh gate)
  COMPOSE              exact body, residue is unit/private placement: tu_assembly compose
  AUTHORING            large structural/semantic gap: author regions, emu_diff first
  TAIL_INTERACTIVE     near-exact with an untried mechanism family worth an agent
  BACKGROUND_PERMUTER  near-exact allocation/home residue, manual families exhausted
  PARKED               evidence-gated parking holds; reopen only with a new fact/tool
Triage is routing metadata: it never blocks search.py or promote.py.
"""
import argparse
import json
import re
import sys
from functools import lru_cache
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from common import ROOT, FormatError, cards, read_json, recipes, relative, write_json
import attempts
import drafts
import parking
import shared_state

SWEEP_DIAG = ROOT / 'build/sweep/diagnostics'
FACTS_DOC = ROOT / 'docs/msc7-codegen.md'
MAC_CORR = ROOT / 'build/mac/correspondence.json'

# First-divergence kind (residue_clusters) -> blocker class.
KIND_CLASS = {
    'FRAME_SIZE': 'FRAME_SIZE', 'SIGNEDNESS': 'DECLARATION_TYPE', 'CFG_DESTINATION': 'CFG_STRUCTURE', 'BLOCK_ORDER': 'CFG_STRUCTURE',
    'WRONG_REGISTER': 'REGISTER_ALLOCATION', 'WRONG_STACK_SLOT': 'HOME_ORDER', 'RELOAD_OR_SPILL': 'HOME_ORDER',
    'FAR_POINTER': 'FAR_POINTER_LIFETIME', 'FLAG_TEST': 'EXPRESSION_SHAPE', 'EXPRESSION_SHAPE': 'EXPRESSION_SHAPE',
    'CALL_SEQUENCE': 'EXPRESSION_SHAPE', 'RELOCATION_ONLY': 'PLACEMENT',
}

# Blocker class -> (recommended families in priority order, families not to lead with, fact prefixes, tool).
PLAYBOOK = {
    'SEMANTICS': (['SEMANTICS', 'CFG_STRUCTURE', 'LOOP_STRUCTURE', 'TYPE'], ['REGISTER_HINT', 'LOCAL_ORDER', 'DECLARATION_ORDER'],
                  ['MSC7-C', 'MSC7-S'], 'python tools/emu_diff.py {sym} {draft} --runs 50  # repair behaviour before codegen tuning'),
    'AUTHORING': (['SEMANTICS', 'CFG_STRUCTURE', 'LOOP_STRUCTURE', 'TYPE', 'FRAME_LAYOUT'], ['REGISTER_HINT', 'LOCAL_ORDER', 'DECLARATION_ORDER'],
                  ['MSC7-C', 'MSC7-L', 'MSC7-S'], 'python tools/search.py {sym} {draft} --full  # author gap_regions (target code the draft lacks) one region per round; emu_diff checks behaviour'),
    'FRAME_SIZE': (['FRAME_LAYOUT', 'LOCAL_LIFETIME', 'TYPE', 'CSE_SUBEXPRESSION'], ['REGISTER_HINT', 'LOCAL_ORDER'],
                   ['MSC7-F', 'MSC7-L'], 'python tools/search.py {sym} {draft} --frame  # named-local homes vs target frame'),
    'HOME_ORDER': (['LOCAL_LIFETIME', 'CSE_SUBEXPRESSION', 'EXPRESSION_SHAPE', 'FRAME_LAYOUT', 'TYPE'], ['LOCAL_ORDER', 'REGISTER_HINT', 'DECLARATION_ORDER'],
                   ['MSC7-F1', 'MSC7-F7', 'MSC7-F8', 'MSC7-X2', 'MSC7-R0'], 'python tools/search.py {sym} {draft} --frame  # static use counts rank homes (F1A/F1F)'),
    'REGISTER_ALLOCATION': (['CSE_SUBEXPRESSION', 'LOCAL_LIFETIME', 'EXPRESSION_SHAPE', 'LOOP_STRUCTURE', 'FAR_POINTER_LIFETIME'],
                            ['REGISTER_HINT', 'LOCAL_ORDER', 'DECLARATION_ORDER', 'OPTIMIZATION_PROFILE'],
                            ['MSC7-R', 'MSC7-F2', 'MSC7-F3', 'MSC7-F6', 'MSC7-X2', 'MSC7-P1'],
                            'python tools/search.py {sym} {draft} --frame  # count uses of variables AND repeated subexpressions (MSC7-R0)'),
    'EXPRESSION_SHAPE': (['EXPRESSION_SHAPE', 'CSE_SUBEXPRESSION', 'TYPE', 'SIGNEDNESS', 'PROTOTYPE'], ['REGISTER_HINT', 'LOCAL_ORDER'],
                         ['MSC7-E', 'MSC7-S', 'MSC7-C1'], 'python tools/probe.py SPEC.json  # controlled expression-shape axes'),
    'CFG_STRUCTURE': (['CFG_STRUCTURE', 'LOOP_STRUCTURE', 'SEMANTICS', 'EXPRESSION_SHAPE'], ['REGISTER_HINT', 'LOCAL_ORDER'],
                      ['MSC7-C'], 'python tools/search.py {sym} {draft}  # read branch_destinations; restructure the first mismatching block'),
    'FAR_POINTER_LIFETIME': (['FAR_POINTER_LIFETIME', 'PROTOTYPE', 'TYPE', 'CSE_SUBEXPRESSION'], ['REGISTER_HINT', 'LOCAL_ORDER'],
                             ['MSC7-F5', 'MSC7-E23', 'MSC7-P'], 'python tools/typedb.py check {draft}  # far/near and pointer types first'),
    'DECLARATION_TYPE': (['TYPE', 'SIGNEDNESS', 'PROTOTYPE', 'DECLARATION_ORDER'], ['REGISTER_HINT'],
                         ['MSC7-S'], 'python tools/typedb.py resync {draft} -o build/workers/NAME/{plain}_typedb.c'),
    'PLACEMENT': (['TU_COMPOSITION', 'SELECTOR_PLACEMENT', 'DATA_LAYOUT'], ['EXPRESSION_SHAPE', 'REGISTER_HINT', 'LOCAL_ORDER'],
                  ['LINK-'], 'python tools/tu_assembly.py compose {component} --add {sym}={draft}  # do not grind the body'),
    'BINDING': (['SELECTOR_PLACEMENT', 'DATA_LAYOUT', 'PROTOTYPE', 'TYPE'], ['EXPRESSION_SHAPE', 'REGISTER_HINT', 'LOCAL_ORDER'],
                ['LINK-'], 'python tools/search.py {sym} {draft} --pool --full  # every opcode matches; fix the wrongly resolved data/selector bindings, then compose'),
    'EXACT_PENDING': (['STEERING'], [], [], 'python tools/promote.py {sym} {draft}'),
    'NO_DRAFT': (['SEMANTICS', 'CFG_STRUCTURE', 'TYPE'], [], ['MSC7-C'], 'python tools/context.py {sym}  # write the first complete draft'),
}

ALLOCATION_ADVICE = ('MSC7-R0: /Oe allocates registers to variables OR SUBEXPRESSIONS by frequency of use. Repeated address '
                     'calculations, index expressions, far-pointer halves and compiler temporaries compete with named locals. '
                     'Count uses of every repeated expression on both sides before touching declaration order or `register` '
                     '(MSC7-F7/F8/R13 FALSIFIED those as causes).')


@lru_cache(maxsize=1)
def facts():
    """Fact register entries {id: (status, title)} parsed from the bold headers."""
    return parse_facts(FACTS_DOC.read_text(encoding='utf-8')) if FACTS_DOC.exists() else {}


def facts_snapshot():
    """{fact id: status} of the current register (stored with parking records)."""
    return {k: v[0] for k, v in facts().items()}


def new_relevant_facts(snapshot, blocker_class):
    """Facts relevant to BLOCKER_CLASS that are new, or changed status, since SNAPSHOT."""
    prefixes = PLAYBOOK.get(blocker_class, PLAYBOOK['EXPRESSION_SHAPE'])[2]
    out = []
    for fid, (status, text) in sorted(facts().items()):
        if any(fid == p or fid.startswith(p) for p in prefixes) and (snapshot or {}).get(fid) != status:
            out.append('%s %s%s' % (fid, status, '' if fid not in (snapshot or {}) else ' (was %s)' % snapshot[fid]))
    return out


def parse_facts(text):
    out = {}
    for m in re.finditer(r'\*\*((?:MSC7|LINK)-[A-Z0-9]+(?:\s*/\s*(?:MSC7|LINK)-[A-Z0-9]+)*)[^*]*?:\s*(.*?)\*\*', text):
        ids = [x.strip() for x in m.group(1).split('/')]
        text = m.group(2)
        found = [s for s in ('FALSIFIED', 'VERIFIED', 'SUPPORTED', 'OPEN') if s in text]
        status = 'MIXED(%s)' % '/'.join(found) if len(found) > 1 else found[0] if found else 'NOTE'
        for i in ids:
            out.setdefault(i, (status, text[:140]))
    return out


def relevant_facts(prefixes):
    rows = []
    for fid, (status, text) in sorted(facts().items()):
        if any(fid == p or fid.startswith(p) for p in prefixes):
            rows.append(dict(id=fid, status=status, rule=text))
    return rows


@lru_cache(maxsize=1)
def _cards():
    return {c['symbol']: c for c in cards()}


@lru_cache(maxsize=1)
def _mac():
    try:
        return read_json(MAC_CORR)
    except (OSError, ValueError):
        return None


def mac_evidence(symbol):
    corr = _mac()
    if not corr:
        return dict(status='UNAVAILABLE', note='build/mac/correspondence.json missing (tools/mac_ref.py --rebuild-correspondence)')
    sym = (corr.get('symbols') or {}).get(symbol)
    review = [r for r in corr.get('review_candidates', []) if r.get('win16_symbol') == symbol]
    if not sym or not sym.get('mac'):
        cov = corr.get('coverage', {})
        out = dict(status='NO_PAIR', coverage='%s of %s open functions have a structural Mac pair' % (cov.get('open_with_mac_counterpart'), cov.get('open')))
        if review:
            out.update(status='REVIEW_CANDIDATE', candidate=review[0].get('mac_id'), reason=review[0].get('reason'))
        return out
    pair = sym['mac'][0]
    mac_id = '%s:%s' % (pair['code_id'], pair['offset'])
    feat = next((f for f in corr['function_features']['mac'] if f.get('mac_id') == mac_id), {})
    win = next((f for f in corr['function_features']['win16'] if f.get('symbol') == symbol), {})
    return dict(status='PAIRED', mac_id=mac_id, confidence=pair.get('confidence'), band=pair.get('confidence_band'),
                mac_shape=dict(backward_branches=(feat.get('control_flow') or {}).get('backward_branches'),
                               switch_case_counts=(feat.get('control_flow') or {}).get('switch_case_counts'),
                               register_local_candidates=(feat.get('source_shape') or {}).get('register_allocated_local_candidate_count'),
                               link_frame_bytes=(feat.get('source_shape') or {}).get('link_frame_bytes'),
                               callees=len((feat.get('call_graph') or {}).get('callees') or [])),
                win_shape=dict(backward_branches=(win.get('control_flow') or {}).get('backward_branches'),
                               switch_case_counts=(win.get('control_flow') or {}).get('switch_case_counts')),
                use='supporting evidence only: loop/switch/variable-count shape; never Windows source text')


def ledger_shas(symbol):
    entry = drafts.entry(symbol) or drafts.entry(symbol.lstrip('_'))
    return {rec['sha256'] for rec in (entry.get('best'), entry.get('frontier')) if rec and rec.get('sha256')}


def diagnostics_current(symbol, fp):
    """True when the sweep diagnostics cover every stored best/frontier draft under the current recompile state."""
    path = SWEEP_DIAG / (symbol.lstrip('_').replace(':', '_') + '.json')
    if not path.exists():
        return False
    diag = read_json(path)
    if shared_state.changed(diag.get('fingerprint'), fp, shared_state.RECOMPILE):
        return False
    return ledger_shas(symbol) <= {d.get('sha256') for d in diag.get('drafts', [])}


def refresh_stale(symbols, fp):
    """Re-sweep functions whose stored drafts changed since their diagnostics (cheap: cached compiles)."""
    stale = {s for s in symbols if ledger_shas(s) and not diagnostics_current(s, fp)}
    if stale:
        import sweep
        from contextlib import redirect_stdout
        with redirect_stdout(sys.stderr):
            sweep.sweep(symbols=stale)
    return stale


def sweep_evaluation(symbol, fp):
    """Current best and frontier evaluations from sweep diagnostics, if still valid for this state."""
    path = SWEEP_DIAG / (symbol.lstrip('_').replace(':', '_') + '.json')
    if not path.exists():
        return None, None, 'NOT_SWEPT'
    diag = read_json(path)
    stale = shared_state.changed(diag.get('fingerprint'), fp, shared_state.RECOMPILE)
    rows = [d for d in diag.get('drafts', []) if d.get('rank') is not None]
    if not rows:
        return None, None, 'COMPILE_FAILED'
    best = max(rows, key=lambda d: d['rank'])
    plausible = [d for d in rows if d.get('frontier_rank') and d['opcode_matches'] >= drafts.FRONTIER_MIN_FRACTION * best['opcode_matches']]
    front = max(plausible, key=lambda d: d['frontier_rank']) if plausible else best
    typedb_variant = next((d for d in rows if d.get('kind') == 'derived'), None)
    best = dict(best, typedb_variant=dict(rank=typedb_variant['rank'], opcodes='%s/%s' % (typedb_variant['opcode_matches'], typedb_variant['opcode_total']),
                                          source=typedb_variant['source']) if typedb_variant else None)
    return best, front, ('STALE: %s changed since %s' % (','.join(stale), diag.get('evaluated')) if stale else 'CURRENT')


LINK_NOISE = ('nop', 'push cs')


def gap_regions(rows, limit=5, minimum=4):
    """Largest runs of target-only rows (code the draft lacks) and candidate-only rows (code it adds).

    LINK's near-call translation (`nop; push cs` before a same-segment far call) is not missing code."""
    def runs(side):
        other = 'candidate' if side == 'target' else 'target'
        out, cur = [], []
        for r in rows:
            one_sided = bool(r.get(side)) and not r.get(other)
            if one_sided and (r.get(side) or '').strip() in LINK_NOISE:
                continue  # LINK noise neither counts nor breaks a run
            if one_sided:
                cur.append(r)
                continue
            if len(cur) >= minimum:
                out.append(cur)
            cur = []
        if len(cur) >= minimum:
            out.append(cur)
        out.sort(key=len, reverse=True)
        key = side + '_offset'
        return [dict(start=hex(run[0].get(key) or 0), end=hex(run[-1].get(key) or 0), instructions=len(run),
                     first=[(x.get(side) or '').strip() for x in run[:3]]) for run in out[:limit]]
    return dict(missing_in_draft=runs('target'), extra_in_draft=runs('candidate'))


def _both_unsupported(divergence):
    d = divergence or {}
    t, c = d.get('target') or {}, d.get('candidate') or {}
    return 'UNSUPPORTED' in (t.get('status'), c.get('status')) and 'execution' in (t.get('kind'), c.get('kind'))


def emu_verdict(symbol, draft, run=False):
    path = ROOT / 'build/emu_diff' / (symbol.lstrip('_') + '.json')
    if run and draft:
        try:
            import emu_diff
            from contextlib import redirect_stdout
            with redirect_stdout(sys.stderr):
                report = emu_diff.compare(symbol, str(ROOT / draft), runs=20, seed=1)
            write_json(path, report)
        except Exception as exc:  # diagnostics only
            return dict(status='ERROR', error=str(exc)[:200])
    if not path.exists():
        return dict(status='NOT_RUN')
    try:
        report = read_json(path)
    except ValueError:
        return dict(status='UNREADABLE')
    verdict = report.get('result') or report.get('overall') or report.get('status')
    if verdict == 'DIVERGED':
        # Runs where both sides stopped on an emulator exception are inconclusive, not a
        # semantic difference (the fault address differs whenever the code layout does).
        # Only the first divergence is reported in detail.
        if _both_unsupported(report.get('first_divergence')):
            verdict = 'INCONCLUSIVE'
    first = report.get('first_divergence') if isinstance(report.get('first_divergence'), dict) else None
    out = dict(status=verdict, draft=report.get('draft'), runs=report.get('executed_runs'), report=relative(path),
               first=({k: first.get(k) for k in ('run', 'index', 'target', 'candidate')} if first else None))
    if draft and report.get('draft') and Path(report['draft']).as_posix() != Path(draft).as_posix():
        # A verdict about another draft is a hint, not the semantic status of the current one.
        out['status'] = 'OTHER_DRAFT_%s' % verdict
    return out


def typedb_live(draft):
    try:
        import typedb
        from contextlib import redirect_stdout
        with redirect_stdout(sys.stderr):
            report = typedb.check_source(ROOT / draft)
        items = report.get('conflicts') or report.get('disagreements') or report.get('issues') or []
        return dict(disagreements=len(items) if isinstance(items, list) else items, sample=items[:5] if isinstance(items, list) else None)
    except Exception as exc:
        return dict(error=str(exc)[:200])


def unit_info(symbol):
    import compiler_profiles
    import unit_owner
    comp = compiler_profiles.component_of(symbol) or {}
    cid = comp.get('id')
    admitted = recipes()
    members = comp.get('publics') or []
    done = [m for m in members if m in admitted]
    unit_ids = sorted({admitted[m].get('unit') for m in done if admitted[m].get('unit')})
    return dict(component=cid, members=len(members), admitted_members=len(done), admitted_units=unit_ids or None,
                owner=(unit_owner.owner_of(cid) or {}).get('owner') if cid else None)


def classify_blocker(ev, fd, emu_status=None, typedb_better=False, size=0):
    """Blocker class from a current evaluation (sweep compact form) and its first meaningful divergence."""
    fd = fd or {}
    m, t = ev.get('opcode_matches') or 0, ev.get('opcode_total') or 1
    ratio = m / t
    cb, tb = ev.get('candidate_bytes') or 0, ev.get('target_bytes') or size or 1
    gap = abs(cb - tb)
    if ev.get('strict'):
        return 'EXACT_PENDING'
    if ev.get('body_exact'):
        return 'PLACEMENT'
    if emu_status == 'DIVERGED':
        return 'SEMANTICS'
    if m == t and gap == 0 and fd.get('kind') == 'RELOCATION_ONLY':
        return 'BINDING'
    if ratio < 0.75 or gap > max(24, 0.08 * tb):
        return 'AUTHORING'
    allocation_only = (m == t and gap == 0 and not ev.get('branch_target_differences') and
                       (ev.get('register_only_differences') or ev.get('stack_local_differences')))
    if allocation_only:
        # The first meaningful divergence names the first allocation decision to explain.
        cls = {'WRONG_REGISTER': 'REGISTER_ALLOCATION', 'WRONG_STACK_SLOT': 'HOME_ORDER', 'RELOAD_OR_SPILL': 'HOME_ORDER',
               'FRAME_SIZE': 'FRAME_SIZE'}.get(fd.get('kind'))
        return cls or ('REGISTER_ALLOCATION' if (ev.get('register_only_differences') or 0) >= (ev.get('stack_local_differences') or 0) else 'HOME_ORDER')
    cls = KIND_CLASS.get(fd.get('kind'), 'EXPRESSION_SHAPE')
    if cls == 'PLACEMENT':
        cls = 'EXPRESSION_SHAPE'
    if cls in ('EXPRESSION_SHAPE', 'FAR_POINTER_LIFETIME') and typedb_better:
        cls = 'DECLARATION_TYPE'
    return cls


def choose_lane(cls, fam, park_status, ev):
    """(lane, ordered next families, exhausted families, stale conclusions) for a blocker class.

    Families come from the class playbook, untried first, then those whose negative conclusion
    went stale after a shared change. A near-exact allocation/home residue whose relevant
    families are all exhausted goes to the background permuter instead of another agent."""
    families = PLAYBOOK[cls][0]
    exhausted = {f for f, s in fam.items() if s['verdict'] in ('EXHAUSTED', 'NO_EFFECT') and not s['stale_since']}
    stale = {f: s['stale_since'] for f, s in fam.items() if s['stale_since'] and s['verdict'] in ('EXHAUSTED', 'NO_EFFECT')}
    untried = [f for f in families if f not in fam]
    retry = [f for f in families if f in stale]
    ordered = untried + retry + [f for f in families if f in fam and f not in exhausted and f not in stale]
    relevant_tried = [f for f in families if f in exhausted]
    lane = {'EXACT_PENDING': 'PROMOTE', 'PLACEMENT': 'COMPOSE', 'SEMANTICS': 'AUTHORING', 'AUTHORING': 'AUTHORING',
            'NO_DRAFT': 'AUTHORING'}.get(cls, 'TAIL_INTERACTIVE')
    complete = ev.get('opcode_matches') is not None and ev.get('opcode_matches') == ev.get('opcode_total')
    if cls in ('REGISTER_ALLOCATION', 'HOME_ORDER'):
        if not untried and not retry:
            lane = 'BACKGROUND_PERMUTER'
    elif lane == 'TAIL_INTERACTIVE' and not untried and not retry and len(relevant_tried) >= 3 and complete:
        lane = 'BACKGROUND_PERMUTER'
    if park_status == 'PARKED' and lane not in ('PROMOTE', 'COMPOSE'):
        lane = 'PARKED'
    return lane, ordered, exhausted, stale


def triage(symbol, fp=None, live_typedb=False, run_emu=False, parked=None, refresh=True):
    fp = fp or shared_state.fingerprint()
    if refresh and symbol not in recipes():
        # A worker's newer best/frontier draft must be judged, not the sweep's older view of it.
        refresh_stale([symbol], fp)
    card = _cards().get(symbol)
    if card is None:
        raise FormatError('unknown function symbol ' + symbol)
    if symbol in recipes():
        return dict(symbol=symbol, state='MATCHED', lane='DONE')
    import compiler_profiles
    size = card['extent'].get('size') or 0
    entry = drafts.entry(symbol) or drafts.entry(symbol.lstrip('_'))
    best, front, sweep_status = sweep_evaluation(symbol, fp)
    stored = entry.get('best') or {}
    draft = (best or {}).get('source') or stored.get('source')
    parked = parking.load_parking() if parked is None else parked
    park = parked.get(symbol)
    park_status = 'PARKED' if parking.is_active(park) else 'REOPENED' if park else 'NOT_PARKED'
    fam = attempts.summary(symbol, current_fp=fp)
    emu = emu_verdict(symbol, draft, run_emu)
    out = dict(symbol=symbol, state='OPEN', size=size, segment=card.get('segment_name'), profile=compiler_profiles.resolve(symbol)['name'],
               sweep=sweep_status, parking=park_status, unit=unit_info(symbol))
    if best is None and not stored:
        cls = 'NO_DRAFT'
        ev = {}
    else:
        ev = best or dict(opcode_matches=stored.get('opcode_matches'), opcode_total=stored.get('opcode_total'),
                          candidate_bytes=stored.get('candidate_bytes'), target_bytes=stored.get('target_bytes'),
                          strict=stored.get('result') in drafts.GOOD, body_exact=bool((stored.get('key') or [0, 0])[1]), first_divergence=None)
        m, t = ev.get('opcode_matches') or 0, ev.get('opcode_total') or 1
        ratio = m / t
        cb, tb = ev.get('candidate_bytes') or 0, ev.get('target_bytes') or size or 1
        gap = abs(cb - tb)
        fd = ((front or ev).get('first_divergence') or {}) if (front or ev) else {}
        out['current'] = dict(opcodes='%d/%d' % (m, t), bytes='%s/%s' % (cb, tb), strict=bool(ev.get('strict')), body_exact=bool(ev.get('body_exact')),
                              register_differences=ev.get('register_only_differences'), stack_differences=ev.get('stack_local_differences'),
                              branch_differences=ev.get('branch_target_differences'), fixups=ev.get('fixups'), draft=draft,
                              frontier_draft=(front or {}).get('source') if front and front.get('source') != draft else None)
        out['first_divergence'] = dict(kind=fd.get('kind'), row=fd.get('row'), target=fd.get('target'), candidate=fd.get('candidate')) if fd else None
        if (best or {}).get('typedb_variant'):
            out['typedb_variant'] = best['typedb_variant']
        typedb_better = bool((best or {}).get('typedb_variant')) and best['typedb_variant']['rank'] >= best['rank']
        cls = classify_blocker(ev, fd, emu.get('status'), typedb_better, size)
    families, avoid, prefixes, tool = PLAYBOOK[cls]
    lane, ordered, exhausted, stale = choose_lane(cls, fam, park_status, ev)
    if cls == 'PLACEMENT':
        last = [r for r in attempts.load(symbol) if 'TU_COMPOSITION' in (r.get('families') or []) and r.get('worker') == 'sweep']
        if last:
            out['last_compose'] = last[-1].get('hypothesis')
    reopen = None
    if park_status == 'PARKED':
        stale_park = shared_state.changed((park or {}).get('state') or {}, fp, shared_state.CONCLUSION) if (park or {}).get('state') else []
        # A fact-register edit reopens only through facts relevant to the parked blocker class.
        fact_hits = new_relevant_facts((park or {}).get('facts_snapshot'), park.get('blocker_class') or cls) if (park or {}).get('facts_snapshot') is not None else []
        relevant = ('toolchain', 'compiler', 'profiles', 'matcher', 'permuter', 'typedb') + (('composer', 'units') if cls in ('PLACEMENT', 'BINDING') else ())
        tool_hits = [c for c in stale_park if c in relevant]
        if fact_hits or tool_hits:
            reopen = dict(new_facts=fact_hits or None, changed_components=tool_hits or None,
                          command='python tools/parking.py reopen %s --because "..."' % symbol)
    draft_arg = draft or 'DRAFT.c'
    comp = out['unit']['component'] or 'OBJECT'
    out.update(blocker_class=cls, lane=lane,
               next_tool=tool.format(sym=symbol, draft=draft_arg, plain=symbol.lstrip('_'), component=comp),
               next_families=ordered[:3] or families[:1],
               do_not_lead_with=[f for f in avoid] or None,
               exhausted_families=sorted(exhausted) or None,
               stale_conclusions=stale or None,
               tried=attempts.summary_lines(fam, families) if fam or families else None,
               relevant_facts=[f for f in relevant_facts(prefixes)][:12],
               semantics=emu, mac=mac_evidence(symbol), reopen_hint=reopen)
    if cls in ('REGISTER_ALLOCATION', 'HOME_ORDER'):
        out['allocation_guidance'] = ALLOCATION_ADVICE
    if cls in ('AUTHORING', 'SEMANTICS', 'CFG_STRUCTURE') and (best or {}).get('aligned_asm'):
        out['gap_regions'] = gap_regions(best['aligned_asm'])
    if live_typedb and draft:
        out['typedb_check'] = typedb_live(draft)
    out['value'] = value_per_hour(out, ev, size, fam)
    return out


def value_per_hour(t, ev, size, fam):
    """Heuristic expected progress per agent-hour, in bytes of debt (documented in docs/orchestration.md).

    Admission removes the whole function from debt; partial authoring progress counts at 25%."""
    lane = t['lane']
    m, total = (ev or {}).get('opcode_matches') or 0, (ev or {}).get('opcode_total') or max(1, size // 3)
    remaining = max(0, total - m)
    bytes_per_opcode = size / max(total, 1) if size else 3.0
    tried = sum(s['attempts'] for s in fam.values())
    if lane == 'PROMOTE':
        p, partial = 0.95, 0
    elif lane == 'COMPOSE':
        p, partial = (0.25 if t.get('last_compose') else 0.6), 0
    elif lane == 'PARKED':
        p, partial = 0.01, 0
    elif lane == 'BACKGROUND_PERMUTER':
        p, partial = 0.03, 0  # background compute, not agent hours
    elif lane == 'AUTHORING':
        per_hour = min(remaining, 60 + 0.15 * remaining)  # opcodes an agent can author per hour
        p, partial = (0.05 if remaining > 40 else 0.2), per_hour * bytes_per_opcode * 0.25
    elif t.get('blocker_class') == 'BINDING':
        p, partial = 0.45, 0  # every opcode already matches; only data/selector bindings differ
    else:
        untried = len(t.get('next_families') or [])
        p = max(0.02, 0.35 / (1 + tried / 15.0)) * (1.0 if untried else 0.3)
        partial = min(remaining, 10) * bytes_per_opcode * 0.25
    return round(p * size + partial, 1)


def backlog(lane=None, limit=None):
    fp = shared_state.fingerprint()
    admitted = recipes()
    parked = parking.load_parking()
    rows = []
    open_symbols = [s for s, c in _cards().items() if c.get('ownership') == 'GAME' and s not in admitted]
    refresh_stale(open_symbols, fp)
    for symbol, card in sorted(_cards().items()):
        if card.get('ownership') != 'GAME' or symbol in admitted:
            continue
        try:
            t = triage(symbol, fp, parked=parked, refresh=False)
        except FormatError as exc:
            t = dict(symbol=symbol, error=str(exc), lane='ERROR')
        rows.append(t)
    rows.sort(key=lambda t: -(t.get('value') or 0))
    counts = {}
    for t in rows:
        counts[t['lane']] = counts.get(t['lane'], 0) + 1
    classes = {}
    for t in rows:
        classes[t.get('blocker_class')] = classes.get(t.get('blocker_class'), 0) + 1
    if lane:
        rows = [t for t in rows if t['lane'] == lane]
    if limit:
        rows = rows[:limit]
    return dict(fingerprint=fp, lanes=counts, blocker_classes=classes, functions=rows)


def compact_line(t):
    cur = t.get('current') or {}
    fd = t.get('first_divergence') or {}
    return '%-26s %-19s %-20s %-9s %5s  %-14s next=%s' % (t['symbol'][:26], t['lane'], t.get('blocker_class'), cur.get('opcodes', '-'), t.get('size'),
                                                          (fd.get('kind') or '-')[:14], ','.join(t.get('next_families') or []))


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('symbol', nargs='?')
    ap.add_argument('--open', action='store_true', help='triage every open GAME function (backlog mode)')
    ap.add_argument('--lane', help='backlog: only this lane')
    ap.add_argument('--limit', type=int)
    ap.add_argument('--json', nargs='?', const='-', help='JSON output (backlog: file path; default build/triage/backlog.json)')
    ap.add_argument('--typedb', action='store_true', help='single symbol: live typedb check of the best draft')
    ap.add_argument('--emu', action='store_true', help='single symbol: run 20 emu_diff samples of the best draft')
    args = ap.parse_args()
    if args.open:
        result = backlog(args.lane, args.limit)
        path = ROOT / 'build/triage/backlog.json' if args.json in (None, '-') else Path(args.json)
        write_json(path, result)
        print('lanes: ' + ', '.join('%s=%d' % kv for kv in sorted(result['lanes'].items(), key=lambda kv: -kv[1])))
        print('classes: ' + ', '.join('%s=%d' % kv for kv in sorted(result['blocker_classes'].items(), key=lambda kv: -kv[1])))
        print('%-26s %-19s %-20s %-9s %5s  %-14s' % ('symbol', 'lane', 'class', 'opcodes', 'size', 'first div'))
        for t in result['functions'][:args.limit or 60]:
            print(compact_line(t))
        print('full backlog: ' + relative(path))
    elif args.symbol:
        result = triage(args.symbol, live_typedb=args.typedb, run_emu=args.emu)
        if args.json:
            print(json.dumps(result, indent=2, default=str))
        else:
            print(render(result))
    else:
        ap.error('give SYMBOL or --open')


def render(t):
    if t.get('state') == 'MATCHED':
        return '%s: already admitted' % t['symbol']
    cur = t.get('current') or {}
    fd = t.get('first_divergence') or {}
    lines = ['%s  (%s bytes, %s, profile %s)' % (t['symbol'], t['size'], t['segment'], t['profile']),
             'current best    : %s opcodes, %s bytes, strict=%s body_exact=%s  [sweep: %s]' % (cur.get('opcodes', '-'), cur.get('bytes', '-'), cur.get('strict'), cur.get('body_exact'), t['sweep']),
             'draft           : %s%s' % (cur.get('draft'), ('  (frontier: %s)' % cur['frontier_draft']) if cur.get('frontier_draft') else ''),
             'first divergence: %s at row %s   T: %s | C: %s' % (fd.get('kind'), fd.get('row'), fd.get('target'), fd.get('candidate')),
             'semantics       : %s' % (t['semantics'].get('status')),
             'blocker class   : %s' % t['blocker_class'],
             'lane            : %s   (value ~%s debt bytes per agent-hour)' % (t['lane'], t['value']),
             'next tool       : %s' % t['next_tool'],
             'next families   : %s' % ', '.join(t['next_families'] or []),
             'do not lead with: %s' % ', '.join(t.get('do_not_lead_with') or []) if t.get('do_not_lead_with') else None,
             'parking         : %s' % t['parking'] + (('  reopen candidate: %s' % json.dumps({k: v for k, v in t['reopen_hint'].items() if k != 'command' and v})) if t.get('reopen_hint') else ''),
             'unit            : %s (%s/%s members admitted, owner %s)' % (t['unit']['component'], t['unit']['admitted_members'], t['unit']['members'], t['unit']['owner'] or 'none'),
             'last compose    : %s' % t['last_compose'] if t.get('last_compose') else None,
             'typedb variant  : %s' % t['typedb_variant'] if t.get('typedb_variant') else None,
             'missing regions : %s' % '; '.join('%s..%s (%d instr: %s)' % (g['start'], g['end'], g['instructions'], ' | '.join(g['first'])) for g in t['gap_regions']['missing_in_draft'][:3]) if (t.get('gap_regions') or {}).get('missing_in_draft') else None,
             'extra regions   : %s' % '; '.join('%s..%s (%d instr)' % (g['start'], g['end'], g['instructions']) for g in t['gap_regions']['extra_in_draft'][:3]) if (t.get('gap_regions') or {}).get('extra_in_draft') else None,
             'mac             : %s' % json.dumps(t['mac'])[:200],
             'already tried   :']
    lines += ['  - ' + x for x in (t.get('tried') or ['nothing recorded'])]
    if t.get('allocation_guidance'):
        lines.append('allocation      : ' + t['allocation_guidance'])
    if t.get('relevant_facts'):
        lines.append('facts           : ' + '; '.join('%s %s' % (f['id'], f['status']) for f in t['relevant_facts']))
    return '\n'.join(x for x in lines if x)


if __name__ == '__main__':
    try:
        main()
    except FormatError as exc:
        raise SystemExit('ERROR: ' + str(exc))
