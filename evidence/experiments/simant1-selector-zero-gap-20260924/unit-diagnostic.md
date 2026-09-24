# Reviewed diagnostic unit, attempt 01 before selector reuse: `simant1:75F4` through `_GetMyInitialRandDir`

## Attempt 01 inputs and scope

- Existing three-member unit source: `evidence/recovery/units/simant1_75F4_DoAntSimY_3_scaffold/unit.c`, SHA-256 `c378da576da6893b9e9df5b66b56a6eebb5da6f8d54ce212ab7a3a1361f0d180` (7321 bytes). It contains the earlier claimed `_DoAntSimY`, `_EnterNest`, `_CheckMyBestDirs`, plus the existing `_DoAntMoveY` pool stand-in.
- Preserved `_GetMyInitialRandDir` candidate: `evidence/recovery/workflow/jobs/GetMyInitialRandDir-72875fbed4/attempt07/candidate0000.c`, SHA-256 `4f0c201e18a7a755d4e7821b6efc3ccff58608f3bbf55907b99d5a3fcd503908` (1303 bytes). Its prior isolated strict result was `NO_COMPLETE_MATCH`; this diagnostic does not call it admitted or exact.
- Diagnostic source: `unit-diagnostic-GetMyInitial.c`, SHA-256 `fe492966ab4c1336bf05f307cc8bdcd234b07bc0df64cd3924e5028ee6ce1fbe` (11151 bytes). It adds only labeled pool stand-ins, three measured zero scalars and the required `RUN4_TEXT` placement for the preserved candidate.
- Profile: baseline MSC C/C++ 7.00, `/AL /G2 /Gs /Oelw /NTSIMANT1_MODULE`; toolchain lock SHA-256 `745e0932b4d672174dc74423c627846a88708946093756f9ee520cee7a2f33f6`.
- `tu_assembly build ... --unit-source ... --scaffold` accepted the source as `simant1_75F4_DoAntSimY_4_reviewed`; `tu_assembly test` compiled exactly one candidate. No production job, recipe, manifest or promotion was touched.

## Attempt 01 predicted and emitted pool

Predicted after the existing 54-byte prefix ending at C3E0:

1. `_ExitNest` stand-in: C3E2/E4/E6, three segment-8 selectors.
2. Unclaimed six-byte filler: C3E8–ED, all zeros and no relocations.
3. `_GetMyDis` stand-in: C3EE/F0/F2/F4, four segment-8 selectors.
4. `_GetMyNextRandDirs` stand-in: C3F6, one segment-9 selector.
5. `_GetMyInitialRandDir`: C3F8/FA, two segment-9 selectors.

Observed OMF CONST is 82 bytes, all zero data, with selectors at relative offsets 0–58, then no fixups at 60/62/64, then selectors at 66/68/70/72 and 74. The three scalars therefore landed at the predicted relative gap offsets 60–65; `_DATA` is absent. The selected representative MAPSYM publics are all segment-backed: `TurnTab`, `relSearchDirs`, `absSearchDirs`, `IsCarryCaste`, `UnCarryCaste`, `YMapPopB`, `YMapPopR` are MAPSYM segment 8; `Scycle` is segment 9. They are fixture anchors only, not claims about historical member ownership.

The candidate then adds three Initial-function selector fixups at relative offsets 76/78/80 (`_MeCrazyDir`, `_MeCrazyCnt`, `_MeCrazyRot`), while the supplied target sequence calls for two Initial words at 76/78. Thus one extra selector word remains; the emitted CONST is two bytes longer than the predicted 80 bytes. Full OMF segment/fixup evidence is in `evidence/recovery/units/simant1_75F4_DoAntSimY_4_reviewed/test/results.json`; candidate OMF SHA-256 is `e6fef7235d73c85d60f7c98bedff1439042fcd26033f85346d947d9b4523bd1a`.

## Attempt 01 strict result by real member

The native result is `NO_COMPLETE_MATCH`. All four real members were anchored at their expected original offsets, but none has an exact body contribution:

| Member | Emitted code segment / size | Literal bytes equal | Byte divergences | Failed fixups |
| --- | --- | ---: | --- | ---: |
| `_DoAntSimY` | `SIMANT1_MODULE` / 352 B | 236/248 | 7, 8, 53, 54, 148, 149, 163, 164, 190, 191, 307, 308 | 6/46 |
| `_EnterNest` | `RUN2_TEXT` / 156 B | 94/96 | 7, 8 | 1/26 |
| `_CheckMyBestDirs` | `RUN3_TEXT` / 170 B | 146/154 | 43, 44, 59, 60, 121, 122, 134, 135 | 4/10 |
| `_GetMyInitialRandDir` | `RUN4_TEXT` / 92 B | 66/72 | 30, 31, 38, 39, 49, 50 | 3/11 |

Overall the matcher reports 542/570 literal bytes and 79/198 fixups equal, no private constraint placement, and issues `conflicting private placement constraints CONST` and `unplaced contribution CONST` in addition to the listed body/fixup mismatches. The compiler exited successfully; object size is 3503 bytes. The full strict diagnostics, placements, and issue list are in the saved native test report. The scalar microfixture remains positive evidence for compiler CONST-gap behavior only; this diagnostic does not establish historical filler ownership or an exact recovered member.
## Attempt 02: exact `MeCrazyCnt` selector reuse

The controlled follow-up changed the Next stand-in to reference the existing target symbol `MeCrazyCnt`, identified at C3F6, instead of representative `Scycle`. The three zero scalars and all other source dimensions stayed fixed. Corrected source SHA-256: `0ad9aba7d3f321d9ca9f3b67c24e7814d5302ac476af033a20c04dbcfc937620`. Raw OMF SHA-256: `582584699c47d56d8bfc35a9cd02a170cb252409f7f77458ab7cd2543ad86cb8`.

CONST is exactly 80 bytes with 37 selector fixups: offsets 0–58, then 66/68/70/72, followed by 74/76/78. Offsets 60/62/64 are the six unrelocated zeros; `MeCrazyCnt` at 74 reuses C3F6, and Initial's `MeCrazyDir`/`MeCrazyRot` occupy 76/78. All five real contributions—`_DoAntSimY` 352B, `_EnterNest` 156B, `_CheckMyBestDirs` 170B, `_GetMyInitialRandDir` 92B, and CONST 80B—have zero divergences and zero failed contribution fixups. The native overall outcome is `STRONGLY_SUPPORTED_MEMBER`, with no issues, 548/548 literal bytes equal, and 130/197 overall fixups equal. The raw strict report and segment data are in `evidence/recovery/units/simant1_75F4_DoAntSimY_4_reviewed/test/results.json`; details are also in [unit-diagnostic-followup.md](unit-diagnostic-followup.md).

Attempt 01's 82-byte CONST and `NO_COMPLETE_MATCH` report are preserved as `unit-diagnostic-attempt01-results.json`; its source, unit source, and unit spec are preserved beside it. The follow-up remains diagnostic only: POOLSTUB code and the zero filler have no historical owner claim, and no production admission or promotion occurred.

## Native admission after reviewed filler recording

`tu_assembly.py build` now records the three separately declared zero scalars as `private_zero_gaps` with claim `UNCLAIMED_LAYOUT_SCAFFOLD` (CONST offsets 60�65, no fixups, owner `pool_stub_ZeroGap`). The unit test checks that initialized OMF interval; the unchanged complete-member matcher checks the full 80-byte CONST contribution. This metadata does not identify historical private-state ownership or credit the stand-in code.

The normal TU workflow job `tu_simant1_75F4_DoAntSimY_4_reviewed-721da53bc2` passed one exact candidate, an independent `--audit-only` rebuild, and a serialized native promotion. Its [promotion proof](../../recovery/workflow/jobs/tu_simant1_75F4_DoAntSimY_4_reviewed-721da53bc2/promotion.json) admits `_GetMyInitialRandDir` and supersedes three prior unit recipes. Strict progress rose from 523 functions / 57,510 game bytes to 524 functions / 57,601 game bytes (+1 function, +91 bytes). The five real contributions remain exact; the reserved-code stubs and measured zero scalars remain unclaimed scaffolds.
