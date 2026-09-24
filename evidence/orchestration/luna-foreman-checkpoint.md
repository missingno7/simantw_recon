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


## Post-commit resumption (2026-09-23 23:39 UTC)

Root pushed the quiescent checkpoint as `bd54c9a5`. Eight workers resumed with explicit disjoint ownership: `_ConvertMaskBitmap`, `_ConvertBitmap2`, `_DrawCastePopUp`, `_NewGame`, `_OpenMiniMapWin`, `_DoWater`, `_PlaceQueenInYard`, and `_DoBitmap`. The Save/Load, Colony, menu-string, and body-exact research artifacts are durable. Escalated targets remain parked; `_DoBitmap` is assigned only to identify the exact `SS:BA2E` owner before any strict test. The checkout is active again, so generated queue/job files may change.


## Near-exact results and quiescent stop (2026-09-24 00:25 UTC)

Root requested a tool/card-generation change after finding out-of-range direct near-call targets that require 16-bit IP normalization. Fleet stopped refilling and all in-flight owners reported settled; no compiler operation remains active. Root has the quiescent signal and can safely update call normalization and regenerate cards. No proof tools, manifests, recipes, or protected counts were edited by the foreman.

The three isolated tiny near-exact checks closed: `_NotMowed`'s wrong segment-9:0 binding resolves to `_GrassMap` at `seg9:0xA0B6`; three candidates fixed the binding, 52-byte extent, and all three fixups, but six register-allocation differences remain. `_db_GetObjectSize`'s two guarded far-cursor forms share a worse 92-byte/frame-8 OMF class against the target's 84-byte/frame-4 shape. `_PlacePillTile` had no evidence-supported new source axis beyond 24 prior variants, so no new candidate was compiled. None earns recovery credit or reopens production.

Additional strict outcomes: `_MakeNewTailR`'s supported `og` profile reissue reproduced its prior nonexact result (29/40 opcodes; 91/101 bytes; CONST/fixup mismatch). `_DoWater` escalated after four candidates with a recurring unplaced CONST/TU-context blocker. `_DoBitmap` attempt03 used a distinct OMF but scored lower than attempt02 (630/678 bytes, 161/257 opcodes). `_PlaceQueenInYard` escalated after six attempts; best is attempt06 (855/937 bytes, 208/326 opcodes). `OPENDLG` escalated after one attempt (466/667 bytes, 99/259 opcodes) with callback/resource semantics still unresolved.

The `_OpenMiniMapWin`/`_MapAreaEvent` read-only audit resolves apparent near helpers using 16-bit wrap: `0x11620 -> _CenterEdit` at ANTEDIT `0x1620`; `0x111e0 -> _UpdateEdit` at ANTEDIT `0x11e0`. The callers group at `antedit:E100` and helper publics at `antedit:00F4`, which does not prove source TU boundaries. Evidence: `build/grinder/open-minimap-helper-audit/audit.md`.

Four jobs allocated just before root's stop request remain OPEN with zero attempts and unchanged TODO sources: `_DropMyFood` (`DropMyFood-3ae9844a8e`), `_CopyMonoBitmap` (`CopyMonoBitmap-13ceb70b88`), `_MciOutWave` (`MciOutWave-3a675ce3d7`), and `_MakeHousePatch` (`MakeHousePatch-1e27dee6d0`). `_snd_Install` (`snd_Install-3c0f20a8c8`) is also OPEN with zero attempts and no owner. These are recorded as stopped/unassigned in [luna-ownership.json](luna-ownership.json); do not resume until root finishes normalization/card regeneration and revalidates active packets.


## Fleet refill after NewGame blocker (2026-09-23 23:43 UTC)

`_NewGame` closed at `PRIVATE_CONST_LAYOUT` after attempt04; the same worker was explicitly assigned `OPENDLG-1f34a15e1f`. Current active ownership remains eight disjoint workers; HEAD is `bd54c9a5`, the last root commit.


## Near-exact and profile-context research (2026-09-23 23:50 UTC)

Root requested three isolated near-exact investigations: `_NotMowed` (simtwo:1378/og), `_db_GetObjectSize` (simtwo:81AC/baseline), and `_PlacePillTile` (simtwo:4CDC/og). Their preserved best sources are used, output stays under `build/grinder/near-exact/`, and no production jobs are created. Each owner must inspect existing negative coverage first and avoid register hints/profile fishing.

A separate profile-context retest is assigned for `_MakeNewTailR` using only `tools/topology_retest.py --profile-reissue` under the existing simant1:5344 `og` assignment. A read-only helper ownership/TU audit checks `_OpenMiniMapWin`/`_MapAreaEvent` ANTEDIT near helpers at 0x11620/0x111e0; no stub, TU claim, or recovery credit is allowed. Fleet count is nine active owners across routine and research tasks.


## Quiescent handoff checkpoint (2026-09-24 00:47 UTC)

All current child investigations have settled; no strict operation or refill remains active. HEAD is `073742b9` on `codex/simantw-recovery`. After `python tools/recovery_workflow.py doctor`, readiness is `READY_FOR_BOUNDED_HANDOFF`: 518 game / 77 runtime, 56 MATCH_READY / 489 MATCH_BLOCKED / 2 STRUCTURE_BLOCKED / 518 matched, 516 durable escalations; all 217 handoff tests pass. Root owns commit/push.

The ledger now contains 40 distinct production job IDs and 34 jobs with strict attempt records; recomputed totals across tracked job IDs are 157 candidate slots, 134 unique effective OMF identities (compile-failed empty-object hashes excluded), zero strict promotions, and zero recovered bytes. This is the all-ledger total, not a delta since the prior checkpoint. Model-weighted token cost remains unavailable. No ownership collisions occurred this batch.

| Target | Settled result |
|---|---|
| `_snd_Install` | One compiler failure then one strict candidate; 225/291 opcodes, 755/804 bytes; private DATA/CONST placement and body gaps remain. |
| `_DoMonoBitmap` | Attempt 02 improves alignment to 210/314 opcodes and 824/870 bytes; still 0/35 fixups and semantic shift/mask/clipping gaps; escalated. |
| `_GiveLesson` | Attempt 02 is body-layout exact (948 bytes, 383/383 opcodes); 13 selector-memory differences and CONST placement/fixups remain. Candidate for `simtwo:78CA` selector composition if exact-body members/evidence satisfy the supported lane. |
| `_FileSelect` | One strict candidate, 71/367 opcodes and 0/26 fixups; custom dialog fallback/path semantics unresolved. |
| `_DropMyFood` | TU feasibility run did not include the current candidate. The near prototype is unsupported: target calls at `0x7769` and `0x78AD` are `90 0E E8`, LINK's same-segment lowering of a source far call, corroborated by the packet and admitted `IsClearTile` declarations. The scaffold conflict is not TU-boundary evidence. Far-prototype retest is next. |
| `_DoWater` / `_MakeNewTailR` | Current bodies are not exact, so the scaffold lane excluded them; no TU test or claim. |

Root's read-only ABI survey found 40 of 131 resolved near-function declarations across 23 jobs conflict with target `90 0E E8` call signatures (39 ESCALATED jobs, one stale PROMOTED candidate). Root will assess a deterministic diagnostic after this stable checkpoint; this is not a proof result. The current diff consists of worker evidence, generated queue/readiness data, refreshed job contexts, and this ownership checkpoint; no proof infrastructure or manifest changes were made by the foreman.

After root checkpoints this stable state, resume with a supported far-prototype retest for `_DropMyFood`, then review `_GiveLesson` unit composition.
