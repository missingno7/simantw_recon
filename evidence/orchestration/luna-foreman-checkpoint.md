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


## Resumed fleet after checkpoint 2346d3ae (2026-09-24 00:52 UTC)

Root pushed the stable checkpoint as `2346d3ae`. `_DropMyFood` received one documented ABI reissue based on the exact `90 0E E8` call evidence and admitted far prototype. Attempt03 remains `NO_COMPLETE_MATCH` (520 candidate bytes, 128/445 opcodes, 56/514 literal bytes, 2/31 fixups; first divergence at 55). Candidate `far` emits an `lcall`, while the strict target member contains the LINK-lowered five-byte sequence; no promotion or TU claim. The target source-level far signature is supported, but this isolated attempt does not reproduce the linker transformation. Attempt report and ABI reissue spec are under the job directory.

`_GiveLesson` unit feasibility closed without a build/test: `simtwo:78CA` proposal has no usable exact-body sources. Attempt02's 948-byte/383-opcode layout still fails `body_exact()` with two resolved `_modeLevels` frame/offset mismatches plus 11 unresolved selector fixups. `_Feedback` and `_RunTutor` are nonexact; `_LessonDone` has no source. Contiguous predicted selector order alone is insufficient.

Eight active Luna workers now hold disjoint explicit symbols (each starts with source-backed packet review and may compile at most one supported candidate): `_DoLaserFire` (`DoLaserFire-9589b88895`), `_SmoothACell` (`SmoothACell-f43227e84e`), `_ProcYardRibbonEvent` (`ProcYardRibbonEvent-68cf4fce3a`), `_DrawBalloons` (`DrawBalloons-ddca13e229`), `_win_DrawMapWindow` (`win_DrawMapWindow-eebfb870f2`), `_ch_AddEntry` (`ch_AddEntry-677911eac6`), `_YellowBirth` (`YellowBirth-4908a07a2f`), and `_DoKeyDown` (`DoKeyDown-785609ef21`). All allocations used explicit `grind.py inspect SYMBOL`; none used concurrent `grind next`. Ownership/source packet hashes and task statuses are in [luna-ownership.json](luna-ownership.json). Root is separately validating a read-only audit of near declarations inconsistent with LINK-lowered far calls; no tool edits or strict result reinterpretation are underway.


## ABI-audit triage and fleet checkpoint (2026-09-24 01:04 UTC)

Root committed the read-only ABI audit at HEAD `49821b00`: 39 current near-prototype conflicts across 23 jobs, two focused tests and 219-test handoff validation pass; doctor remains ready. The audit reports mismatches only and does not prove a recovered C type or unit boundary.

The first controlled replay, `_DropMyFood` near-to-far `IsClearTile`, was nonexact after one ABI reissue: 520B, 128/445 opcodes, 56/514 literal bytes, 2/31 fixups. It supports the source-level far call but the strict object-to-image comparison still differs at the linked lowering. `_GiveLesson` remains ineligible for TU composition because its exact-byte/opcode layout has two `_modeLevels` fixup mismatches and 11 unresolved selector fixups, while the other family sources are not body exact.

High-value audit triage selected one more bounded reissue, `_GetMyInitialRandDir`: the current audited source identity is stable, the single near `GetMyRandDirs` call targets `90 0E E8`, and the candidate is 89B against 91B with 34/36 opcodes. `_GetStrategy`, `_EditMessage`, and `_CustomerIDDialog` are read-only triage only. A separate `_CopyMonoBitmap` task traces DS state only if prior evidence lacks the answer.

Routine work since the prior checkpoint: `_DoLaserFire` and `_SmoothACell` each had one strict candidate and were escalated for distinct frame and selector-view gaps. `_DrawBalloons`, `_win_DrawMapWindow`, and `_ch_AddEntry` stopped without compiling because target storage/API contracts remain unsupported. Eight disjoint Luna workers are active on `_GetMyInitialRandDir`, `_GetStrategy`, `_EditMessage`, `_CustomerIDDialog`, `_CopyMonoBitmap` DS state, `_ProcYardRibbonEvent`, `_YellowBirth`, and `_DoKeyDown`. Root requested a short quiescent boundary before updating `recovery_context.py` to surface target-specific far-call evidence; no foreman changes to tools or proof logic were made. See machine ownership for source packet identities and statuses.


## Quiescent boundary for packet ABI note (2026-09-24 01:16 UTC)

All assigned child work settled and is stable; root can proceed with the requested `recovery_context.py` packet-note update. HEAD remains `49821b00`. I refreshed doctor at 01:15Z: `READY_FOR_BOUNDED_HANDOFF`, 518 game / 77 runtime, 53 ready / 492 blocked / 2 structure blocked / 518 matched, 519 durable escalations, 219 tests pass.

Since root commit `2346d3ae`, five strict candidates were tested: `_DropMyFood`, `_GetMyInitialRandDir`, `_DoLaserFire`, `_SmoothACell`, and `_DoKeyDown`; zero promotions or recovered bytes. The one clear ABI-layout discriminator is `_GetMyInitialRandDir` attempt05: one `GetMyRandDirs near→far` edit changed candidate size 89→91 bytes and opcode alignment 34/36→36/36, with exact layout and no register/branch/stack differences. Remaining fixups are three unresolved CONST selector refs and `_match_position` frame/offset. No promotion.

Read-only triage: `_GetStrategy` has a source-backed single `GstrR near→far` probe candidate, but CFG extent is unknown and fixup/data residue remains; held pending root's packet update. `_EditMessage` and `_CustomerIDDialog` have valid far-call evidence but their main body/frame mismatches dominate, so no reissue. `_CopyMonoBitmap` preserves inherited DS but does not prove it is DGROUP. `_DoKeyDown` attempt01 was 989/1385B, 89/514 opcodes, 1/58 fixups; the candidate is missing event/object-selection semantics. `_YellowBirth` remains 0-attempt DATA_LAYOUT on six unnamed DGROUP words. `_ProcYardRibbonEvent` was incorrectly considered in C19C; packet confirms `antedit:A51E`, with only the 0x2302 path grounded and unknown prompt state. All worker-specific evidence is in the workflow job directories and machine ledger.


## Resumed fleet after packet-note push 9d91461f (2026-09-24 01:36 UTC)

Verified HEAD `9d91461f`. Doctor is `READY_FOR_BOUNDED_HANDOFF`: 518 game / 77 runtime, 53 MATCH_READY / 492 MATCH_BLOCKED / 2 STRUCTURE_BLOCKED / 518 MATCHED, 519 durable escalations, 220 handoff tests pass. Strict counts are unchanged.

Eight active disjoint assignments were dispatched from fresh explicit `grind.py inspect SYMBOL` packets, with source packet identities recorded in [luna-ownership.json](luna-ownership.json): `_GetStrategy` (one GstrR ABI probe conditional on supported expert reissue), `_DoLaserFire` (one source-backed local/frame probe conditional on support), `_hanim_SetObjectPos`, `_win_DoProxMenu`, `_SetYardMode`, `_MakeBalloon`, `_CalcScore`, and `_DrawBitMapToBuffer`. The six open jobs began at zero attempts; the two escalated jobs are restricted to one genuinely new source-backed hypothesis or a no-reissue report. No concurrent `grind next` was used.

Fleet state at dispatch: 8 active worker threads; 4 persistent compiler workers. Zero new candidates, strict promotions, or recovered bytes are counted at assignment time. Next checkpoint will reconcile worker reports, job attempts/effective OMF identities, current doctor state, and updated HEAD before root stages anything.


## Quiescent checkpoint after packet-note push 9d91461f (2026-09-24 01:51 UTC)

All ten assigned investigations settled; no workers remain active. Doctor is `READY_FOR_BOUNDED_HANDOFF`: 518 game / 77 runtime, 52 MATCH_READY / 493 MATCH_BLOCKED / 2 STRUCTURE_BLOCKED / 518 MATCHED, 520 durable escalations, 220 handoff tests pass. No strict promotion or recovered bytes.

Since `9d91461f`: 10 targets investigated, two strict candidates compiled, two unique effective OMF outputs, and eight early no-candidate stops. `_GetStrategy` attempt09 changed only `_GstrR` near→far: exact 460B extent but 139/151 opcodes, 6 register +16 branch differences, 27/59 fixups; C7 still emits explicit `lcall` versus target LINK lowering. `_DoLaserFire` attempt02 is 996B vs 719B with 212/343 opcodes and a frame/live-range mismatch. Other results are bounded semantic/data blockers recorded per job. Zero ownership collisions.

Fresh `python tools/parked_review.py` returned 351 semantic, 38 profile-candidate, 39 ABI/type, 64 TU-layout, 27 unknown, and 2 profile-resolvable rows. Intersecting with live `docs/production-queue.json` leaves seven blocked exact-body TU-layout rows: `_ClearHistory`, `_GiveLesson`, `_MapToYard`, `_PauseGame`, `_SetPause`, `_ToggleMapCursor`, `_win_SetObjBitmap`; the first, third, fourth, fifth and seventh remain root-reserved. `_SetAntLion`, `_SendBoyMsg`, `_StartAttack`, `_FollowCatDir`, and `_FindInAList` from the old shortlist are already MATCHED. The remaining `_GiveLesson` and `_ToggleMapCursor` warrant fresh packet/unit feasibility review before any reissue.

Changed evidence includes the fresh parked review and doctor-generated queue/readiness/blocker/topology/cards snapshots; worker attempt/reissue data for `_GetStrategy` and `_DoLaserFire`; job/packet/blocker records for assigned symbols; and this ownership checkpoint. Seven additional explicit inspect packets (`_hanim_RenderAnimSet`, `_UpdateEdit`, `_AboutDialog`, `_ProcMenu`, `_YellowDeath`, `_myBeginSong`, `_CopyMonoMaskBitmap`) were created while preparing replacements but remain unassigned/zero-attempt. Their job IDs are recorded in the machine ledger. Root should validate changed scope before commit; the foreman did not touch tools, protected proof, or manifests by hand.


## Fleet restart after checkpoint 058e3158 (2026-09-24 02:02 UTC)

Root validated and pushed the previous quiet state as `058e3158`. Doctor remains `READY_FOR_BOUNDED_HANDOFF`: 518 game / 77 runtime, 52 MATCH_READY / 493 MATCH_BLOCKED / 2 STRUCTURE_BLOCKED / 518 MATCHED, 521 durable escalations, 220 tests.

Nine disjoint assignments are active. The research-heavy five are `_ToggleMapCursor` and `_GiveLesson` (fresh B_TU feasibility, with explicit warning that opcode identity is not body-exact), `_GetMyInitialRandDir` (simant1 component/selector feasibility), and `_win_DrawModeWindow` plus `_ConvertMonoMaskToTandy` (unit-level profile evidence only). Four guided fresh targets are `SAVEASDLG`, `_IBMInitStuff`, `_Draw_SimYard`, and `_LoadTiles`, each capped at one source-grounded candidate/test, or an early blocker report. Packet identities, starting attempts, owner and exact hypothesis are in [luna-ownership.json](luna-ownership.json). No root-reserved B_TU member is assigned.


### Early TU feasibility result (2026-09-24 02:06 UTC)

`_GiveLesson` attempt02 was reviewed against fresh `simtwo:78CA` unit evidence. The current source is not `body_exact` despite 948B and 383/383 opcodes: two resolved `_modeLevels` frame/offset mismatches and 11 selector fixups remain. `tu_assembly propose` has no usable members/groups (`_Feedback` and `_RunTutor` nonexact, `_LessonDone` absent); selector pool continuity alone cannot admit it. No build or reissue. Eight other owners remain active.


### Post-restart blocked-lane progress (2026-09-24 02:12 UTC)

Six of nine assignments have settled, all without compilation; three remain active (`_ConvertMonoMaskToTandy`, `SAVEASDLG`, `_IBMInitStuff`). `_ToggleMapCursor` exposed a source-backed candidate-only hypothesis: reverse the crossed `just`/`_mapTileRect` additions to clear two resolved offset fixups, but the unit still has no eligible group and nine CONST selectors remain. Root requested one isolated expression-reversal test only after the pending classifier checkpoint, then TU consideration only if native `body_exact` and introducer gates pass. `_GiveLesson` and `_GetMyInitialRandDir` remain excluded by resolved offset/frame mismatches. `_win_DrawModeWindow` cannot assign `og` to `simant:B324` due sibling/profile-invariance conflict. `_Draw_SimYard` and `_LoadTiles` stopped on unresolved private state/data contracts. No tests, candidates or promotions in this sub-batch.


## Quiescence before parked-classifier correction (2026-09-24 02:25 UTC)

All nine assignments after `058e3158` settled with zero strict candidates or promotions. Fresh blocked-lane review: `_GiveLesson` remains body_exact-ineligible; `_GetMyInitialRandDir` remains excluded by `_match_position` frame/offset mismatch and uneligible selector introducers; `_win_DrawModeWindow` cannot assign og to 20-public `simant:B324`; `_ToggleMapCursor` has a source-backed reversal of crossed `_just`/`_mapTileRect` additions but still lacks an eligible antedit:C19C TU group. Root will correct parked B_TU classification based on native body_exact gates, then permit one isolated expression-reversal test; no TU is planned until exact-body and introducer gates pass.

`_ConvertMonoMaskToTandy` probe supports og for a single-public component `gr:5E30`; the preserved profile probe source is older than attempt04’s current best, so this merits a reviewed component-level profile assignment and source-specific profile reissue after the checkpoint. Four guided starts (SAVEASDLG, IBMInitStuff, Draw_SimYard, LoadTiles) stopped before compile on unsupported state/API/data bindings. No strict credit. One accidental `partial_resources.py --help` run changed only random output paths in `resource-probe.json` and created `build/REShg9sh212`; root checked semantic identity unchanged and will restore at quiescence.

All workers have settled. No one is invoking `parked_review.py`, `doctor`, or `tu_assembly`; root has a safe classifier edit/validation window. Packet identities, assignments, and per-job outcomes remain in [luna-ownership.json](luna-ownership.json).


### Parked classifier correction validated (2026-09-24 02:22 UTC)

Root’s classifier/tooling correction is validated. Fresh `parked_review.py` now reports 58 `B_TU_LAYOUT_RESOLVABLE` and 6 `B_TU_SOURCE_INELIGIBLE`, using native `tu_assembly.body_exact` as the source gate. `_GiveLesson` is excluded for two resolved `_modeLevels` bindings; `_ToggleMapCursor` is excluded for two resolved crossed `_mapTileRect`/`_just` bindings. The other four ineligible records are in `evidence/recovery/parked-reclassification.json`. Handoff validation passed all 220 tests and cache replay; doctor is READY at 518/77, 52 ready / 493 blocked, no problems. The accidental resource-probe JSON is restored and `--help` is side-effect-free. Root will commit/push before fleet resume.


## Resumed after classifier push d7bdbfb0 (2026-09-24 02:30 UTC)

Root validated and pushed the B_TU eligibility correction as `d7bdbfb0`. Two priority one-candidate tasks are active: `_ConvertMonoMaskToTandy` receives a reviewed `gr:5E30 -> og` component assignment and profile reissue of the current attempt04 source if context checks pass; `_ToggleMapCursor` receives a source-layout reissue reversing only the crossed side-effect-free integer additions. Both retain strict factory-only promotion and TU gating on native `body_exact` plus eligible introducers.


## 2026-09-24T02:50Z-quiescent-after-d7bdbfb0

- Root checkpoint HEAD: `d7bdbfb0`; all ten assignments since the classifier push are settled, with no active child operations. Root may commit the stable generated/job/orchestration state.
- Doctor: `READY_FOR_BOUNDED_HANDOFF`; 519 game functions, 77 runtime members, 53 ready, 491 blocked, 2 structure-blocked, 519 matched, zero problems. Handoff validation passed 220 tests and cache replay.
- Promotion: `_ConvertMonoMaskToTandy` now contributes 221 verified bytes under reviewed singleton `gr:5E30→og`. The preserved old probe source SHA `4914bd3c…354d9537` was decisive; attempt05 on the newer attempt04 source remained 16 `GR_MODULE` bytes off despite 11/11 fixups and 22/22 `_DATA`. Attempt06 exactly matched 208/208 bytes and 11/11 fixups and passed native `grind.py accept`. Source: `src/recovered/wf_ConvertMonoMaskToTandy-4e3e71229c.c`; recipe `src/recovery.json`; proof `evidence/recovery/workflow/jobs/ConvertMonoMaskToTandy-4e3e71229c/promotion.json`.
- Since `d7bdbfb0`: 10 targets investigated; 5 workflow candidates, 2 declaration-order research fixture candidates, 4 new unique effective workflow OMFs, 1 strict promotion / 221 bytes. Six reviews stopped before compile/reissue because their proposed axis did not explain the principal mismatch or was already exhausted. No ownership collisions.
- `ToggleMapCursor`: expression reversal canonicalized to the old OMF. A separate two-order fixture proves `_just` before `_mapTileRect` flips both bindings at +0xC4/+0xCD; fixups improve 28/45→30/45. Nine `CONST` selector obligations/private placement remain, so no production promotion/TU. Artifact: `evidence/experiments/toggle-map-cursor-declaration-order/`.
- ABI selective replays: `_QueenMoveR` and `_MakeLint2` each confirmed a LINK-lowered far-call transformation, but whole members still fail on independent layout, fixup, frame, and private `CONST` obligations. `_CustomerIDDialog`, `_EditMessage`, and `_DropMyFood` were not reissued because the call form occurs downstream of the dominant gap or unresolved TU/data context.
- `_GetMyInitialRandDir` has a distinct selector-versus-offset source question: target +0x46 is an NE selector relocation to PACK seg9:0, while attempt05 emits LOC1 offset for `_match_position`. Native `body_exact` remains false and `tu_assembly.propose(15)` has no eligible group/introducers; preserve as an isolated probe axis only.
- Changed files include generated production/recovery queue and blocker snapshots, `_ConvertMonoMaskToTandy` profile assignment/recipe/source/promotion proof, four job attempt histories (ConvertMonoMaskToTandy, ToggleMapCursor, QueenMoveR, MakeLint2), the ToggleMapCursor research fixture, and the ownership/checkpoint metadata. No proof tools were edited.


### 2026-09-24T02:56Z-togglemap-close follow-up

After the prior quiescent snapshot, `_ToggleMapCursor` was formally closed through the supported `python tools/grind.py block` workflow as `ESCALATED` / `PRIVATE_CONST_LAYOUT`. The record includes attempt04’s unchanged effective OMF after expression reversal, the new microfixture result that `_just` before `_mapTileRect` fixes both crossed named operands, and the remaining nine `CONST` selector/private placement blockers. No queue or blocker ledger was hand-edited. Doctor passed at 02:55Z: 519 game / 77 runtime, 54 ready / 490 blocked / 2 structural blocked / 519 matched, zero problems; validation remains 220 tests plus cache replay. Generated queue, blocker, card, frontier, and progress files were refreshed by the supported workflow and are stable for root commit.


### 2026-09-24T03:00Z-abi-reissue-close post-reissue closeout

Root audit found `_MakeLint2` and `_QueenMoveR` had been reclassified MATCH_READY after failed expert reissues. Both were closed through supported `python tools/grind.py block`, retaining their scoped negatives and source-backed next requirements. `_MakeLint2` is `REGISTER_ALLOCATION` (attempt05 corrects neither frame/local allocation nor `MapA` and SRand1 fixups); `_QueenMoveR` is `PRIVATE_CONST_LAYOUT` (attempt05 confirms the far GetBestDir LINK transformation but retains CONST/LifeR/unit residues). `_ToggleMapCursor` was already re-escalated through the same workflow. No hand edits to manifests/queue/blockers. Doctor now READY at 02:59Z: 519 game / 77 runtime, 52 ready / 492 blocked / 2 structural blocked / 519 matched / 520 durable escalations, zero problems; 220 tests/cache replay pass. All child workers are idle and the regenerated state is stable for root commit.


### 2026-09-24T03:24Z bounded ABI/profile generation closeout

The post-9dd43d55 batch is quiescent and ready for root checkpoint. Doctor at 03:24Z reports READY_FOR_BOUNDED_HANDOFF: 519 game functions / 77 runtime members; 51 MATCH_READY, 493 MATCH_BLOCKED, 2 STRUCTURE_BLOCKED, 519 MATCHED, 521 durable escalations; 220 handoff tests and cache replay passed; no problems. No strict promotion or recovered bytes in this batch.

- Eight production targets investigated across bounded ABI screens and source-grounded selector work; one read-only profile census found no eligible blocked reissue. Six ABI screens stopped without compile/reissue because the ABI form was already exhausted or downstream of a leading mismatch.
- `_GetMyInitialRandDir`: attempt06 pointer-cast form failed compilation. Attempt07 uses the scalar selector formal supported by caller evidence and raw `__segname("PACK")`; it fixes the target +0x46 PACK LOC2 relocation and yields 36/36 opcodes, but strict proof remains NO_COMPLETE_MATCH with 8/14 fixups, three unresolved CONST selector references at +0x1e/+0x26/+0x31, and an unplaced/conflicting CONST contribution. Job is already ESCALATED / DATA_LAYOUT; do not retry or attempt TU until private selector sources/placement are established. Detailed fixtures: `evidence/experiments/getmyinitialranddir-segment-expression/` and `evidence/experiments/getmyinitialranddir-formal-shape/`; strict report: `evidence/recovery/workflow/jobs/GetMyInitialRandDir-72875fbed4/attempt07/results.json`.
- `_win_SetObjSelectedStateI` attempt09 confirms far `win_IsWinOpen` call lowering and advances first divergence to +0x31; whole member remains 330/331 bytes, 50/318 literal bytes and 3/18 fixups; it was closed through supported `grind.py block` as REGISTER_ALLOCATION. Other ABI screens (`_DoAttackAnt`, `_DoRandAntA`, `_TryMoveDirB`, `_EditToolsMenu`, `_ms_LoadPopUpResource`, `_SpiderDialog`) did not justify new reissues.
- Batch counts: 2 strict workflow candidates / 2 distinct OMF outputs, 1 compile failure, 4 isolated fixture compilations / 3 unique fixture outputs, 0 promotions, 0 collisions. Profile census was read-only.
- Changed-file scope for root commit: generated queue/blocker/frontier/card/private-topology/readiness snapshots from supported workflow/doctor; `_GetMyInitialRandDir` attempts 06/07 and preserved source/job state; `_win_SetObjSelectedStateI` attempt09 and supported escalation; two isolated selector-expression fixture folders; orchestration ownership/checkpoint metadata. No proof tool or protected gate was changed.


Follow-up at 2026-09-24T03:34Z: `_GetMyInitialRandDir` had no remaining production hypothesis after attempt07, so I closed the refreshed body-exact/private-binding result with supported `python tools/grind.py block` as DATA_LAYOUT (three CONST selector obligations and an unplaced/conflicting CONST contribution). Doctor rerun passed READY_FOR_BOUNDED_HANDOFF at 519/77, 51 ready / 493 blocked / 2 structural blocked / 519 matched / 521 durable escalations, with 220 tests/cache replay and zero problems.
