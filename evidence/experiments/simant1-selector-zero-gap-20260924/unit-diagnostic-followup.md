# Follow-up reviewed unit: reuse `_GetMyNextRandDirs` selector

This retest changed only the Next stand-in's segment-9 reference from representative `Scycle` to the existing target symbol `MeCrazyCnt`, whose target owner is established at C3F6. A forward external declaration was added ahead of the stand-in; the preserved attempt07 function body and all other source dimensions stayed fixed. The prior source, unit file, unit spec, and strict report are preserved as `unit-diagnostic-attempt01.c`, `unit-diagnostic-attempt01-unit.c`, `unit-diagnostic-attempt01-unit.json`, and `unit-diagnostic-attempt01-results.json`.

## Identity and strict result

- Source: `unit-diagnostic-GetMyInitial.c`, 11161 bytes, SHA-256 `0ad9aba7d3f321d9ca9f3b67c24e7814d5302ac476af033a20c04dbcfc937620`.
- Preserved 3-member input identity: SHA-256 `c378da576da6893b9e9df5b66b56a6eebb5da6f8d54ce212ab7a3a1361f0d180`.
- Preserved attempt07 candidate identity: SHA-256 `4f0c201e18a7a755d4e7821b6efc3ccff58608f3bbf55907b99d5a3fcd503908`.
- Profile/toolchain: baseline `/AL /G2 /Gs /Oelw /NTSIMANT1_MODULE`, MSC C/C++ 7.00, toolchain lock SHA-256 `745e0932b4d672174dc74423c627846a88708946093756f9ee520cee7a2f33f6`.
- Native unit: `simant1_75F4_DoAntSimY_4_reviewed`; one candidate compiled successfully. Raw OMF SHA-256 `582584699c47d56d8bfc35a9cd02a170cb252409f7f77458ab7cd2543ad86cb8` (3488 bytes).
- Strict result: `STRONGLY_SUPPORTED_MEMBER`, no reported issues. The matcher compared 548/548 literal bytes, counted 130/197 fixups equal overall, and placed the CONST private constraint at original offset 50092. Do not interpret this as exact confirmation or admission; no production job or recipe was changed.

## Selector and member contributions

The emitted CONST is 80 bytes. It has the 27-word prefix at relative offsets 0â€“52, `_ExitNest` stand-in representatives at 54/56/58, no fixups at 60/62/64 (the six measured zero bytes), `_GetMyDis` representatives at 66/68/70/72, and the `MeCrazyCnt` selector at 74 (target C3F6) reused by the real Initial member. `_GetMyInitialRandDir` contributes `MeCrazyDir` and `MeCrazyRot` at 76/78 (target C3F8/FA). All 37 selector fixups land at the predicted offsets; the CONST contribution at original target offset 50092 has zero byte divergences and zero failed fixups. `_DATA` and `_BSS` are empty. The prior attempt01 candidate had 82 CONST bytes and an extra selector at 80; the `MeCrazyCnt` reuse corrected that two-byte excess.

Each real member contribution is byte/fixup exact in this run:

| Member | Candidate segment / bytes | Literal comparison | Divergences | Failed contribution fixups |
| --- | --- | ---: | --- | ---: |
| `_DoAntSimY` | `SIMANT1_MODULE` / 352 B | 236/236 | 0 | 0 |
| `_EnterNest` | `RUN2_TEXT` / 156 B | 96/96 | 0 | 0 |
| `_CheckMyBestDirs` | `RUN3_TEXT` / 170 B | 154/154 | 0 | 0 |
| `_GetMyInitialRandDir` | `RUN4_TEXT` / 92 B | 62/62 | 0 | 0 |
| Private CONST | `CONST` / 80 B | 80/80 | 0 | 0 |

The complete native comparison, OMF, selector names, and segment records remain in `evidence/recovery/units/simant1_75F4_DoAntSimY_4_reviewed/test/results.json`; the unit's current source/spec are in the same folder. `POOLSTUB_TEXT` remains excluded as scaffolding and its code is not claimed. The scalar filler is supported as a measured layout technique; its historical owner is still unknown.

## Native admission after reviewed filler recording

`tu_assembly.py build` now records the three separately declared zero scalars as `private_zero_gaps` with claim `UNCLAIMED_LAYOUT_SCAFFOLD` (CONST offsets 60–65, no fixups, owner `pool_stub_ZeroGap`). The unit test checks that initialized OMF interval; the unchanged complete-member matcher checks the full 80-byte CONST contribution. This metadata does not identify historical private-state ownership or credit the stand-in code.

The normal TU workflow job `tu_simant1_75F4_DoAntSimY_4_reviewed-721da53bc2` passed one exact candidate, an independent `--audit-only` rebuild, and a serialized native promotion. Its [promotion proof](../../recovery/workflow/jobs/tu_simant1_75F4_DoAntSimY_4_reviewed-721da53bc2/promotion.json) admits `_GetMyInitialRandDir` and supersedes three prior unit recipes. Strict progress rose from 523 functions / 57,510 game bytes to 524 functions / 57,601 game bytes (+1 function, +91 bytes). The five real contributions remain exact; the reserved-code stubs and measured zero scalars remain unclaimed scaffolds.
