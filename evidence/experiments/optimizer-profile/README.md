# Optimizer-profile evidence (diagnostic, no proof, no queue changes)

Scripts here recompile existing sources under alternative MSC C/C++ 7.00 profiles and score them with the search diagnostic (`codegen_diff.compare_code`) or the strict member matcher (`library_match.compare_member`). Nothing here alters recipes, hashes, jobs or counts.

## invariance2.py — admitted sources are profile-invariant

Every admitted msc700 source (363 at the time) was compiled under the locked `/AL /G2 /Gs /Oelw /NT<group>` and under `/Oeglw`, `/Oegilw` and `/Oelw /GA`. CODE-segment bytes were compared object against object (`invariance2.json`).

| Code group | admitted | identical under /Oeglw and /Oegilw | identical under /GA |
| --- | ---: | ---: | ---: |
| ANTEDIT_MODULE | 54 | 54 | 54 |
| GR_MODULE | 98 | 98 | 98 |
| SIMANT1_MODULE | 16 | 16 | 16 |
| SIMANT_MODULE | 60 | 60 | 60 |
| SIMONE_MODULE | 52 | 52 | 52 |
| SIMTWO_MODULE | 83 | 82 (`_win_SetColorFromObj` differs) | 83 |

The admitted corpus therefore cannot distinguish the locked profile from `/Oeglw`, `/Oegilw` or `/GA`, except for one function of the `win_*` translation unit.

## sweep.py — parked code-shape jobs under /Og

All escalated jobs with a REGISTER_ALLOCATION, EXPRESSION_SHAPE, OPTIMIZER_VARIANT_REQUIRED or LOCAL_FRAME_LAYOUT cause (102) had their best candidate recompiled under `/Oeglw` and `/Oegilw` (`sweep.json`): 28 improve, 2 reach full opcode and size alignment. Strict matcher results for those (see the session log):

| Job | Unit | locked /Oelw | /Oeglw | /Oegilw |
| --- | --- | --- | --- | --- |
| SeparateFile | ANTEDIT_MODULE | NO_COMPLETE_MATCH | CONFIRMED_MEMBER | CONFIRMED_MEMBER |
| IsPillDead | SIMTWO_MODULE | NO_COMPLETE_MATCH | STRONGLY_SUPPORTED_MEMBER | STRONGLY_SUPPORTED_MEMBER |

`/Ox` and MSC 6.00A were also probed (`probe.py`, `results.json`); both are worse than `/Oeglw` on the parked set, and MSC 6 is worse everywhere.

## Reading

- The bulk of the game is consistent with a single makefile whose optimizer switches include `/Og` (global CSE, register write-through before calls, loop-carried register homes) and, for some units, `/Oi` (inline memset/strlen/strcat: CarpetFloorL/R, MakeKitchenWall, DecodeString, SetHelpCursor); `/GA` explains the exported-prologue blocker (INDIRECTDLGPROC) without changing any admitted function.
- The `win_*` translation unit inside SIMTWO_MODULE is the one place where `/Og` is refuted by an admitted function, i.e. profiles may differ per translation unit (a library module compiled separately), not per code group.
- The remaining large families are not profile questions: 100 escalations are exact bodies blocked only by translation-unit selector pools or private data placement (DATA_LAYOUT / PRIVATE_CONST_LAYOUT), and the strict matcher does not yet validate offset fixups to far code symbols (InitApplicationWindows).
