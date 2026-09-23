# Luna foreman checkpoint

Updated: 2026-09-23 22:13 UTC (session checkpoint)

## Baseline

- Branch: `codex/simantw-recovery`
- HEAD: `aab33e7e` (`Preserve bounded Luna recovery and blocked-family research`)
- `recovery_workflow.py doctor`: READY_FOR_BOUNDED_HANDOFF; 518 verified game functions, 77 runtime members; 86 MATCH_READY, 459 MATCH_BLOCKED, 2 STRUCTURE_BLOCKED, 518 MATCHED; 487 durable escalations; no problems.
- Doctor generated readiness at 2026-09-23 22:07:29 UTC; the queue remained at 25 GUIDED, 61 LARGE, 461 EXPERT.
- Root owns systemic review of `_win_SetObjBitmap`, `_ClearHistory`, `_PauseGame`, `_SetPause`, and `_MapToYard`; no fleet assignment overlaps these.
- Prior approaches excluded: InitApplication frame negative, GetEnterDir lexical-scope collapse, ReadConfig far-pointer ABI, DrawH/VBar tail-lifetime collapse, palette data blockers.

## Worker ownership

| Worker | Symbol | Job | State / notes |
| --- | --- | --- | --- |
| `guided_recovery_2` | `_font_MakeImage` | `font_MakeImage-407a1fb679` | Allocated first through `grind.py next` at session start; baseline SIMTWO_MODULE. Attempt 01 was submitted by `guided_recovery_1` just before ownership correction: 624 candidate bytes vs 586 target, 17/624 ordinary bytes, 0/29 fixups, score 0.4095, no complete match. Worker 2 owns all follow-up work. |
| `guided_recovery_1` | `_SaveGame` | `SaveGame-4535266fed` | Explicit `grind.py inspect _SaveGame` allocation at 2026-09-23 22:13 UTC, after the `next` collision; MATCH_READY, ANTEDIT_MODULE. |

The factory queue's `next` resumes the first open MATCH_READY job, so concurrent workers must not both call it for independent allocations. Use explicit-symbol `grind.py inspect SYMBOL` to provision the second disjoint job, then give that symbol/job to its owner. All strict tests and promotions still go through `grind.py`; no production manifests or proof files were changed.

## Working tree note

`doctor` refreshed only the generated `checked` and `generated` timestamps in tracked `docs/handoff-readiness.json` and `docs/recovery-queue.json`. Their state content is unchanged. Git restore failed because `.git/index.lock` could not be created; root has been notified and will handle the final checkpoint.

## Previous-goal-turn capacity observation

At 2026-09-23 22:13 UTC, after the global `agents.max_concurrent_threads_per_session` setting was raised, one additional `guided_recovery_3` spawn was attempted and returned `agent thread limit reached`. No retry was made. This running session remains at its four-thread cap: root, foreman, and the two production workers. `_OPENDLG` was proposed for the extra worker but was not allocated.

## Current goal turn (2026-09-23 22:16–22:33 UTC)

The live session now exposes 17 thread slots. `doctor` again reports READY_FOR_BOUNDED_HANDOFF with 518 verified game functions / 77 runtime members, 86 MATCH_READY / 459 MATCH_BLOCKED / 2 STRUCTURE_BLOCKED / 518 MATCHED, and 487 durable escalations. HEAD remains `aab33e7e`; branch remains `codex/simantw-recovery`.

The fleet was scaled to ten workers: eight production assignments plus two isolated research assignments. The first research batch has now closed, and the 4C24 owner is running one bounded follow-up. The live fleet currently has eight production jobs and one research task. See machine-readable ownership, assignment generations, starting source identities, statuses, and compiler-service snapshot in [luna-ownership.json](luna-ownership.json).

The first production set was `_font_MakeImage`, `_SaveGame`, `_MapToolsMenu`, `_DoRedInitiator`, `_TryMyDropOrLift`, `_ProcMapRibbonEvent`, `_SimBird`, and `_GPutPacked`; two targets have since parked and their workers were refilled. Current production ownership is `_MapToolsMenu`, `_DoRedInitiator`, `_TryMyDropOrLift`, `_ProcMapRibbonEvent`, `_SimBird`, `_GPutPacked`, `_RibbonToolsMenu`, and `_ch_LookUpId`. `_font_MakeImage` parked after eight attempts: attempt08 matches frame size 0x14 but retains proportional-pass/local-register/far-selector differences. `_SaveGame` parked as DATA_LAYOUT without spending attempts; the packet does not establish names or bounds for DGROUP references 0x9520 and 0x9570. Their evidence and next steps remain in the workflow ledger.

Two isolated research batches completed. `_ColonySmellBN/RN/BT/RT` now have a positive named-selector binding observation through `_PherMapBN/RN/BT/RT`, but all four full-member comparisons remain nonexact and their effective OMF hashes differ; no reissue is warranted. The 4C24 branch-pointer probe matched all 32 DATA bytes but emitted 930 code bytes versus 926, placing `_PauseGame` and `_SetPause` two bytes later each while `_SetMenuEntries` remains at offset 158. A four-variant maximum pointer-local type/register/lifetime follow-up is now assigned; previous flat/struct/static and ternary forms will not be repeated. Root owns the other five body-exact cases; only the menu-string family has this explicit research authorization.

Six fresh symbol allocations were serialized through explicit `grind.py inspect SYMBOL` and took about 18 seconds; refills took roughly 5–8 seconds per target. No collision occurred in this goal turn. The previous-goal collision—two workers receiving `_font_MakeImage` from concurrent `grind.py next`—is preserved above as historical context. Current ownership and outcomes live in [luna-ownership.json](luna-ownership.json).

Compiler service was RUNNING with four workers and zero active jobs at 22:27 UTC; its instance recycled after the idle timeout and restarted automatically with valid implementation identities. No compiler cap or runner changes were made. The queue routing rule remains: allocate each routine symbol using explicit `grind.py inspect SYMBOL`, never concurrent `grind.py next`.


## Current continuation (2026-09-23 23:25 UTC)

The expanded-capacity checkpoint had 11 workers, 19 production targets, and 66 production candidates at its recorded baseline. Subsequent refills used explicit target inspections only. Current HEAD is `57c751ee` on `codex/simantw-recovery`; the working tree contains active worker evidence and generated queue/readiness updates, so preserve it. `recovery_workflow.py doctor` is `READY_FOR_BOUNDED_HANDOFF`: 518 game functions, 77 runtime members, 68 MATCH_READY, 477 MATCH_BLOCKED, 2 STRUCTURE_BLOCKED, 518 MATCHED, and 505 durable escalations. The 216-test handoff validation remains passed.

Current fleet: **9 active workers / 29 distinct production jobs assigned**. There are 22 targets with at least one attempt, 111 production compiler candidates across 111 recorded attempts, 95 unique effective production OMFs, zero strict promotions, and zero recovered bytes added. Assignment events: 33; collisions in this goal turn: 0 (one historical `grind next` collision); model-weighted token cost unavailable. These totals are regenerated from the unique assigned job records; see [luna-ownership.json](luna-ownership.json).

| Worker | Current explicit target | Job |
|---|---|---|
| `recover_convertbitmap` | `_ConvertMaskBitmap` | `ConvertMaskBitmap-0b5587ae1e` |
| `recover_droppebble` | `_PickupMyRock` | `PickupMyRock-3b3c94d053` |
| `recover_font_makeimage` | `_ConvertBitmap2` | `ConvertBitmap2-ad5bc868e2` |
| `recover_gputpacked` | `_DoWater` | `DoWater-3796e1e6c9` |
| `recover_maptoolsmenu` | `_OpenMiniMapWin` | `OpenMiniMapWin-7aac93a2e0` |
| `recover_procmapribbon` | `_DropMyEgg` | `DropMyEgg-5dfe003e00` |
| `recover_savegame` | `_DrawCastePopUp` | `DrawCastePopUp-6de54bcbe1` |
| `recover_simbird` | `_NewGame` | `NewGame-648c3dd8ca` |
| `recover_trydrop_lift` | `_PlaceQueenInYard` | `PlaceQueenInYard-28a1feb636` |

### Save/Load research complete, no production credit

The extended NE-semantic scan finds 307 consecutive records at 8-byte stride from `0x9570` through `0x9F07`, with selector relocations at `0x9576..0x9F06` and none at the expected next site `0x9F0E`. The next record begins at `0x9F08` and has four zero words. Counts by target segment: seg8 73, seg9 188, seg10 46; 96 contiguous segment runs. Consumer code advances by eight bytes, computes transfer size from words 0×1, passes I/O arguments from +4/+6, and stops when the next record's word +2 is zero.

An isolated 2544-byte OMF candidate at provisional base `0x9520` matches all 1,316 bytes outside 307 semantic far-pointer fixups; every fixup names the corresponding MAPSYM owner and matches the target offset/segment. This supports a possible declaration shape only. It does not prove the original source object or TU extent, field spellings, or initializer, and the mechanically emitted table is not recovered source. No strict function test, reissue, promotion, or recovery credit. Evidence: `evidence/experiments/save-table-structure/README.md`, `consumer-addendum.md`, and `results.json`.


## Root histogram review (2026-09-23 23:28 UTC)

HEAD advanced to `2fc8444d` after root pushed completed Save-table, body-exact, Colony, and 4C24 research. The current histogram covers **24 investigated production jobs**: source/shape blockers are 6 `SEMANTICS_UNKNOWN` and 3 `EXPRESSION_SHAPE`; private-placement/context blockers are 3 `PRIVATE_CONST_LAYOUT`, 1 `DATA_LAYOUT`, and 3 translation-unit-context variants. Seven jobs with attempts remain `NEEDS_REVISION` and are not yet classifiable. No BSS cause appeared. The sample does not support a shared compiler/layout cause; root directed no queue or classification changes.

Current measured fleet has **9 active workers**, **29 unique production jobs assigned**, 119 production candidates across 119 attempts, 103 unique effective production OMFs, zero promotions, and zero recovered bytes. Doctor remains READY with 518 verified functions / 77 runtime members / 68 ready / 477 blocked / 2 structural / 518 matched / 505 durable escalations; all 216 validation tests passed. See JSON ledger for live owners and counters.

Representative scoped records: `evidence/recovery/workflow/jobs/ConvertBitmap-628c7ae412/job.json` (semantic shape), `evidence/recovery/workflow/jobs/DrawSwarm-7ae6fef6d6/job.json` (private CONST), and `evidence/recovery/workflow/jobs/ScrollEditArrays-3e1e532292/job.json` (TU context).


## Quiescent commit checkpoint (2026-09-23 23:35 UTC)

All eight in-flight worker owners have confirmed no strict operation remains. No refills are active. Job directories, candidate sources/reports, and generated queue/blocker/readiness files are stable for root's full commit. Root's current HEAD is `2fc8444d`. The final readiness refresh at 23:34Z is `READY_FOR_BOUNDED_HANDOFF`: 518 verified game functions, 77 runtime members, 66 MATCH_READY, 479 MATCH_BLOCKED, 2 STRUCTURE_BLOCKED, 518 MATCHED, 505 durable escalations; all 216 tests passed.

At this stable point the ledger covers 29 production jobs, 24 with attempts, 120 compiler candidates across 120 attempts, and 103 unique effective production OMFs. Strict promotions and recovered bytes remain zero. Latest explicit blocker histogram: `SEMANTICS_UNKNOWN` 6, `EXPRESSION_SHAPE` 4, `PRIVATE_CONST_LAYOUT` 3, `DATA_LAYOUT` 1, translation-unit-context causes 4, and 6 unclassified `NEEDS_REVISION`. No BSS cause. Root's review found no basis to change queue routing/classification.

Workers remain stopped until root finishes the commit; then resume disjoint explicit-symbol assignments. No commits or pushes were made by the foreman.
