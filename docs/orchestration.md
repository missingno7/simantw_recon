# Orchestration layer: sweep, triage, attempt history, lanes

This is a thin supervisor layer over the existing factory (context/search/promote, drafts ledger,
parking, residue classifier, compiler service and cache, unit composer, permuter, emu_diff, typedb,
Mac reference). It adds no new proof path. Every admission still goes through `promote.py`, which
compiles freshly and runs the unchanged gates.

## Why

Measured before this layer existed (2026-09-29):
- 25,854 search sessions over 935 functions, and only 1,707 carried a `--meta` round description.
  Those descriptions were free text, with about 1,200 distinct "family" strings.
- 5,587 free-text notes across 589 functions. A worker had to read up to 50 notes to learn what was
  tried.
- Stored best/frontier drafts were scored once, under the state at the time. A profile
  reassignment, a declaration fix in typedb, a newly admitted neighbour or a matcher improvement
  never re-scored them.
- Near-exact register/home tails absorbed most interactive hours, while large, under-authored
  functions moved more bytes per hour.

## Components

| Piece | File | Reuses |
|---|---|---|
| Shared-state fingerprint | `tools/shared_state.py` | toolchain lock, profiles catalogue, recovery.json, unit records, fact register, matcher code hashes |
| Structured attempt ledger | `tools/attempts.py`, `evidence/recovery/attempts/SYMBOL.jsonl` | written by `search.py` (every session), `sweep.py`, `permuter_queue.py`; backfilled from `build/search/*/history.jsonl` and ledger notes |
| Global draft sweep | `tools/sweep.py` | `drafts.py` (new `refresh()`), `codegen_cache.compile_cached` (compiler service), `codegen_grinder.score_object`, `codegen_diff.diagnose`, `typedb resync`, `tu_assembly compose`, `promote.py --verify-only` |
| Next-action triage | `tools/triage.py` | `residue_clusters.classify`, sweep diagnostics, parking, attempts summary, fact register, compiler profiles, unit context, emu_diff verdicts, typedb check, Mac correspondence |
| Lanes / fleet plan | `tools/fleet_plan.py` | triage backlog |
| Object ownership | `tools/unit_owner.py`, `layout/unit-owners.json` | checked by `tu_assembly compose --persist` and `promote.py --unit` |
| Permuter queue | `tools/permuter_queue.py` | `permuter.py` unchanged; candidates from triage |

## Data flow

1. A shared change lands. That is a profile assignment, an admission (new dependency or typedb
   evidence), a unit record, a matcher or compiler tool change, or a toolchain lock change.
2. `python tools/sweep.py --since-last` sees which fingerprint components changed.
   - It recompiles every preserved best/frontier draft of an OPEN function whose evaluation key
     changed. The key is draft sha + current flags + matcher hash + toolchain; identical keys are
     skipped, and the compile cache avoids duplicate compiles.
   - It adds a typedb-resynced variant when the declaration database changed.
   - It refreshes ledger keys through `drafts.refresh()` and stores compact diagnostics for triage.
   - It reports NEWLY_EXACT, NEWLY_BODY_EXACT (composition-blocked), IMPROVED, UNCHANGED,
     REGRESSED and COMPILE_FAILED.
   - NEWLY_EXACT drafts run `promote.py --verify-only` (fresh compile, full gate).
   - Body-exact drafts run a bounded `tu_assembly compose` in scratch.
   - With `--admit`, it calls the normal promotion commands for candidates that passed
     verification.
3. `python tools/triage.py --open` classifies every open function from its current diagnostic.
   - It names the blocker class, the relevant facts, the exhausted families and the recommended
     tool and family.
   - It assigns a lane: AUTHORING, TAIL_INTERACTIVE, COMPOSE, BACKGROUND_PERMUTER, PARK or
     SEMANTICS.
   - It estimates the value per agent-hour.
4. `python tools/fleet_plan.py` turns the backlog into small worker assignments:
   - 3–5 targets per worker, lane-specific;
   - one owner per object for composition;
   - the tail lane only with a new mechanism.
   `python tools/permuter_queue.py` runs the BACKGROUND_PERMUTER lane unattended.
5. Workers run `context.py` and `triage.py SYMBOL`. They begin with the recommended action and pick
   an untried family.
   - Every `search.py` session records a structured attempt: families, hypothesis, prediction,
     falsifier, before/after frontier and outcome.
   - Repeating a tried family needs `--why-repeat` naming the new fact, tool or evidence. This is
     decision support, not a gate.

## Invariants

- Nothing here edits `src/recovery.json`, proofs, fixtures, locks or hashes. The drafts ledger is
  changed only through `drafts.py` functions under its lock. The attempt ledger is append-only.
- The sweep never admits on its own comparison: admission is `promote.py`, fresh compile and gates.
- Triage output, attempt families and lanes are routing metadata. They never block `search.py` or
  `promote.py`.
- A Mac correspondence is supporting shape evidence only. It never names source text for the Win16
  function.

## Commands

```powershell
# Supervisor, after any shared change (profile, admission, unit, typedb, tool, toolchain)
python tools/sweep.py --triggers                         # which shared components changed since the last full sweep
python tools/sweep.py --since-last --derive typedb       # re-evaluate every preserved draft (cache-backed, ~3 min cold)
python tools/sweep.py --symbols _A,_B --verify --compose # fresh promote --verify-only / scratch composition for routed candidates
python tools/sweep.py --since-last --verify --compose --admit   # supervisor only: admit what passed the normal gates

# Triage
python tools/triage.py SYMBOL [--typedb] [--emu]         # one function: class, lane, next tool, untried families, facts
python tools/triage.py --open [--lane AUTHORING]         # whole backlog -> build/triage/backlog.json

# Structured history
python tools/search.py SYMBOL a.c --family CSE_SUBEXPRESSION --hypothesis "..." [--prediction ...] [--falsifier ...] [--why-repeat ...]
python tools/attempts.py summary SYMBOL                  # per-family verdicts; context.py shows the same as already_tried
python tools/attempts.py families                        # controlled vocabulary

# Scheduling
python tools/fleet_plan.py --authoring 4 --tail 2 --compose 1 [--write] [--claim]
python tools/permuter_queue.py plan | enqueue | run --budget-minutes 120 | report
python tools/unit_owner.py list | claim OBJECT --owner NAME --reason TEXT | release OBJECT --owner NAME
```

## What counts as a shared change (sweep triggers)

`tools/shared_state.py` fingerprints eleven components. Line endings are normalised.

| Component | Files | Effect |
|---|---|---|
| toolchain | layout/toolchain.json | recompile every draft |
| compiler | compiler wrapper/service/worker, layout/compiler-service.json | recompile (object cache key) |
| matcher | library_match, recovery_gate, codegen_diff, codegen_grinder, topology_diagnostics, residue_clusters, omf, analysis | re-score every draft |
| profiles | layout/compiler-profiles.json | recompile the drafts of reassigned objects under the new flags |
| admissions | src/recovery.json | new dependencies and typedb evidence; re-derive typedb variants |
| units | layout/translation-units.json | unit context / composition routes |
| typedb | tools/typedb.py, tools/c_source.py | re-derive typedb variants |
| composer | unit_composer, tu_assembly, pool_search | re-run composition routes |
| pragmas | pragma / inline-asm review lists | a steered source may become admissible |
| facts | docs/msc7-codegen.md | not a recompile trigger; marks earlier negative conclusions stale |
| permuter | permuter.py, permuter_mutations.py | not a recompile trigger; earlier permuter runs become stale |

The per-draft evaluation key is draft sha + current flags + recompile fingerprint
(toolchain, compiler, matcher, profiles). A derived typedb variant also keys on admissions and
typedb. An unchanged key reuses the stored evaluation. A cold full sweep of 332 functions (671
drafts) took 195 s, and 662 of the 671 compiles came from the object cache.

## Structured attempt records

`evidence/recovery/attempts/SYMBOL.jsonl` is append-only and holds one JSON object per line.

- **Identity:** `schema`, `id`, `symbol`, `time`, `worker`, `session`.
- **Hypothesis:** `families` (controlled vocabulary), `family_source` (declared / inferred / none),
  `family_text` (the raw free-text family when it was not in the vocabulary), `hypothesis`,
  `prediction`, `falsifier`, `why_repeat`, `declared_verdict`.
- **Inputs:** `profile`, `flags`, `inputs` (path + sha256 prefix), `candidates`, `distinct_outputs`.
- **Frontier:** `before` / `after`, each with strict, body_exact, first-divergence row, opcodes,
  opcode_total and divergence_class.
- **Result:** `outcome` is EXACT, BODY_EXACT, IMPROVED, NEUTRAL, NO_OP (identical object to an
  earlier input), REGRESSED (re-evaluation only) or COMPILE_FAILED. `report` is the path to the
  report.
- **State:** `state` is the shared-state fingerprint. When a conclusion-relevant component changes
  later, `attempts.summary` reports the family as `stale_since`, so an old negative result is not
  held against a new mechanism.

Writers:
- `search.py` writes a record every session automatically.
- `sweep.py` writes SHARED_STATE_RESWEEP records and compose outcomes (TU_COMPOSITION).
- `permuter_queue.py` writes PERMUTER_SEARCH records.
- A backfill imported the pre-existing history, 8,067 records from search sessions and notes plus
  539 permuter runs, as `family_source: inferred` (keyword inference) with `backfilled: true`.
  Inferred rows count half when deciding that a family is EXHAUSTED.
- The free-text notes in the drafts ledger are unchanged.

Family verdicts per function:
- **EXACT.**
- **PRODUCTIVE:** some session improved the frontier.
- **NO_EFFECT:** every session produced an object identical to an earlier one.
- **EXHAUSTED:** at least three weighted sessions without gain.
- **TRIED.**

## Triage classes and lanes

`triage.py` takes the current evaluation of the best/frontier draft from sweep diagnostics. It then
applies these rules in order:

1. strict: EXACT_PENDING (lane PROMOTE).
2. exact body: PLACEMENT (lane COMPOSE; the last compose blocker is shown).
3. emu_diff DIVERGED: SEMANTICS.
4. every opcode and byte equal, residue only in fixup operands: BINDING (wrongly resolved
   data/selector bindings, so the composer's body-exact preflight would refuse it).
5. opcode ratio below 0.75, or a byte gap above max(24, 8%): AUTHORING.
6. opcode-complete allocation-only residue: REGISTER_ALLOCATION or HOME_ORDER. The first divergence
   decides, and the MSC7-R0 subexpression guidance is shown.
7. otherwise the first-divergence kind maps to FRAME_SIZE, CFG_STRUCTURE, FAR_POINTER_LIFETIME,
   EXPRESSION_SHAPE or DECLARATION_TYPE. DECLARATION_TYPE also applies when the typedb-resynced
   variant is at least as good.

Each class has a playbook: families in priority order, families not to lead with (declaration
order, `register` and local order for allocation, all FALSIFIED as causes), fact prefixes and a
tool. Untried families come first, then families whose negative conclusion went stale.

A near-exact allocation/home residue with no untried or stale family goes to BACKGROUND_PERMUTER,
not to an agent. Parking still wins, except for PROMOTE/COMPOSE. A parked function whose
fingerprint changed since parking carries a reopen hint.

The value heuristic estimates debt bytes per agent-hour as p(exact within the hour) × function size
+ 25% × authored opcodes × bytes per opcode.

| Lane | p(exact within the hour) |
|---|---|
| promote | 0.95 |
| compose | 0.6, or 0.25 after a failed compose |
| binding | 0.45 |
| tail | 0.35 / (1 + sessions/15), × 0.3 without an untried family |
| authoring | 0.05, with 60 + 15% of the remaining opcodes authored per hour |
| parked | 0.01 |

It is a ranking device, not a measurement.

## Fleet plan and ownership

`fleet_plan.py` fills the COMPOSE lane first:
- one worker owns whole objects;
- `--claim` records the owner in layout/unit-owners.json with a 24 h lease;
- `tu_assembly compose --persist` and `promote.py --unit` refuse another owner's live claim;
- unclaimed objects stay free for the supervisor.

Then AUTHORING and TAIL workers get 3–5 targets each, grouped by object. Authoring/tail workers may
investigate functions of an owned object but never compose it. A TAIL target needs at least one
untried or stale family. BACKGROUND_PERMUTER targets go to `permuter_queue.py`.

The queue:
- takes near-exact (at least 90% opcodes), non-placement targets;
- drops mutations of FALSIFIED families (register hint, declaration order) and of families with no
  effect on that target;
- skips a target after two gainless runs with no shared change since (a backfilled run older than
  the current mutation catalogue does not count);
- reports only improvements and exact winners.

## Mac correspondence (assessed 2026-09-29)

`build/mac/correspondence.json` pairs only 2 of 332 open functions, `_YellowCommand` and
`_YellowDeath`, both medium confidence. The Mac binary has no symbol names, and the MPW export plan
delimits only 359 exported routines, not static helpers.
- None of the 15 parked allocation/home functions has a pair, so the Mac port cannot constrain the
  allocation wall today.
- Triage shows a pair's shape (backward branches, switch case counts, 68k register-local count,
  LINK frame size, callee count) as supporting evidence only.
- A stopped worker's feature change (NE data-string features) produced no additional pairs and was
  not merged.
- More value needs better Mac function boundaries (static routines inside the MPW exports) before
  structural matching can reach the long tail.
