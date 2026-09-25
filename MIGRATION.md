# Workflow simplification — 2026-09-25

The bounded "factory" workflow (queue, jobs, attempt/candidate budgets, automatic parking, expert reissue, stale-job invalidation, readiness reports and model-specific briefs) was replaced by the four-command workflow used in `../stunts_recon` and `../icytower_rerecon`: `context.py` → `search.py` → `promote.py`, with `validate.py` at acceptance or tooling boundaries. The strict proof core is unchanged. Git checkpoint: tag `checkpoint/pre-simplification-20260925`.

## Why

The budget of 8 attempts / 96 variants / 192 candidates per target, combined with "block and never reopen", had parked 526 jobs; 495 functions were `MATCH_BLOCKED` against 44 `MATCH_READY`. Of those parked jobs, 356 stopped after four or fewer attempts and 110 after zero or one. Every proof-tool change also invalidated open jobs until an expert refreshed their recorded hashes. The limits measured the process, not the evidence.

## What changed

| Before | After |
| --- | --- |
| `grind.py next/inspect/test/accept/block`, `recovery_workflow.py queue/next/attempt/promote/defer/refresh/doctor` | `context.py SYMBOL` / `--list`, `search.py SYMBOL files...`, `promote.py SYMBOL file` / `--unit UNIT`, `validate.py` |
| Per-target budgets, duplicate-experiment refusal, ESCALATED/parked states, `topology_retest.py` reissue with budget extensions | None. Any unrecovered function can be searched at any time; old blocker labels appear as hints in `context.py` |
| Job directories in `evidence/recovery/workflow/jobs` (19,866 tracked files, ~500 MB) | Durable best draft per function in `evidence/recovery/drafts/` (index plus 797 sources, 4.6 MB); scratch runs in ignored `build/search/` |
| `accept` required the exact identity of a previously tested file (the CRLF trap) | `promote.py` freezes and freshly compiles the given file itself |
| `tu_assembly.py job` + `recovery_workflow.py attempt/promote` | `promote.py --unit UNIT --reason ...` |
| Core journal in `evidence/recovery/workflow/transaction.json`; 44 MB `verified-objects.json` tracked and rewritten per promotion | `tools/publication.py` lock + journal in `build/publication.json`; detailed report in `build/recovery/`, totals in `docs/progress.json` |
| `handoff_validate.py` + `doctor` readiness gate | `validate.py` (tests, full re-verification, profile catalog, cache replay of an exact control, service evidence) |

Removed tools: `grind`, `recovery_workflow`, `factory_queue`, `topology_retest`, `parked_review`, `blocked_reclassification`, `near_exact_lane`, `blocker_ledger`, `blocker_families`, `structural_families`, `handoff_validate`, `codegen_report`, `progress`. New: `context`, `search`, `promote`, `validate`, `publication`, `drafts`. Adapted: `tu_assembly` (preserved sources from the draft ledger, no job issuing), `compiler_profiles probe SYMBOL`, `declaration_order SYMBOL [--write]`, `mirror_pairs` (records through `search`), `call_abi_audit` (audits drafts), `build_topology`, `cards`, `verify_recovery`, `codegen_grinder` (multi-file rounds).

Removed docs: the cheap-model handoff/prompt, Sonnet grinder, near-exact lane, Fable continuation briefs, expert blocker pass, generated reclassification/family reports, queue and readiness JSON. `docs/factory.md` now describes the new workflow and keeps the build-model, proof, runner and diagnostic sections. `docs/grinder-lessons.md` keeps the technical lessons plus the idiom checklist from the retired briefs.

## Data migration

- **Drafts.** The one-off `build/migration/migrate_drafts.py` (local, ignored) replayed the retired `tu_assembly.preserved_sources()` selection over every job attempt, fresh reclassification and body-matched family source. It copied each chosen source into `evidence/recovery/drafts/SYMBOL/<sha12>.c` and kept a compact summary of all 809 legacy jobs (status, attempts, blockers, reason, next experiment) plus the 41 frozen pre-workflow drafts. 504 of the previously selected drafts existed only in the ignored compiler cache. They are now versioned.
- **Equivalence.** `preserved_sources()` before and after the migration returns the same 1,002 symbols with identical source content and basis (523 admitted, 475 best-not-exact, 4 body-matched). It stayed identical after a real superseding unit publication. Five `unit.json` files that named job files now name the identical draft copies.
- **Promotion proofs.** The 292 `promotion.json` files moved to `evidence/recovery/promotions/<job>.json`. Recipe `promotion_evidence` paths and every textual reference were rewritten mechanically; no proof content changed.
- **Archive.** The rest of `evidence/recovery/workflow`, the drafts/blocker/family/reclassification ledgers, `layout/private-data-topology.json`, `evidence/orchestration`, the near-exact lane and profile-reissue records, and 238 tracked scratch logs from the repository root were moved (not deleted) to ignored `build/archive/` (621 MB). Git history keeps them at the checkpoint tag. Links in dated notes that point into `evidence/recovery/workflow/jobs/` resolve there.
- Tests that read archived attempt reports now use five extracted comparisons in `tests/fixtures/`. The reconstruction-rule test uses live `context.py` packets.

## Verification

| Measure | Before | After |
| --- | ---: | ---: |
| Verified game functions | 524 | 524 |
| Game code bytes | 57,601 | 57,601 |
| Runtime members / bytes | 77 / 12,960 | 77 / 12,960 |
| Tests | 224 (pass) | 207 (pass) |
| Tracked files | 26,288 | 7,232 |
| Tracked size | 734 MB | 153 MB |
| Python tool modules | 65 | 58 |
| docs/ files | 23 | 10 |

The verified symbol set and every admitted source path are identical to the baseline. The test count fell because budget, queue, escalation and reissue tests were deleted with their machinery. The admission, receipt, cache and scope tests were kept. New tests cover source rules, journal rollback/conflict refusal, the publication lock, fail-closed promotion (nothing published, no stray source), refusal to replace an admitted recipe outside a unit, `--verify-only`, and repeated identical search rounds.

Controls, all against real tools and fixtures:

- `validate.py` passed: 207 tests, fresh 524/77 verification, `_TooFar` cache replay `CONFIRMED_MEMBER` without a compiler launch.
- `promote.py _TooFar ... --verify-only` passed the complete fresh gate (`CONFIRMED_MEMBER`). Units `simone_4668_KillSpider_1_scaffold` and `gr_6322_DebugWinPrintf_1_reviewed` passed `--unit --verify-only` (`STRONGLY_SUPPORTED_MEMBER`).
- A real superseding publication of the KillSpider unit committed through the journal and re-verified 524/77. The canonical files were then restored from the pre-publication snapshot (`build/migration/publication-control/`).
- A non-exact `_PlacePillTile` candidate was refused (`literal bytes differ`) with no file left in `src/recovered/`.
- Search smoke on `_PlacePillTile` (`build/workers/migration-smoke/`): four rounds and nine hypotheses, cached reruns in about 0.5 s. Declaring the column `register` local first moved `x`/`y` into the target's DI/SI registers (0 register differences). C7 then interleaves the first argument push between the two loads, the same residue recorded in `docs/recovery-handoff.md`. No recovery is claimed.

## Limits

Nothing about proof strength changed: complete extents, ordinary bytes, semantic fixups, private contributions, profile catalog, ownership and independent re-verification are all still required. Scaffold stand-ins still earn no credit. The retired workflow's historical counts in dated notes describe their checkpoints. No throughput improvement is claimed yet.
