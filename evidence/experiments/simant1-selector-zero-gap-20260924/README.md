# simant1:75F4 zero CONST interleaving microfixture

## Scope and predicted layout

This is an isolated two-source MSC7 batch, not a reconstructed member. The source uses only `Fixture*` external names and small probe functions to force selector references. It tests whether a six-byte, all-zero file-scope `const` object placed between two groups can occupy the selector pool's CONST segment without changing later selector-fixup ordering. No historical public is assigned to the zeros.

Expected target-relative shape:

- 54-byte baseline preceding block (27 selector words)
- three `_ExitNest` words, C3E2/C3E4/C3E6, segment 8
- six unrelocated zero bytes, C3E8–C3ED
- four `_GetMyDis` words, C3EE/C3F0/C3F2/C3F4, segment 8
- `_GetMyNextRandDirs` at C3F6, segment 9
- `_GetMyInitialRandDir` at C3F8/C3FA, segment 9

That requires 80 total CONST bytes in the fixture-relative analogue, with 37 selector fixups and a six-byte unrelocated interval after the first 30 fixups. The batch uses baseline `/AL /G2 /Gs /Oelw /NTSIMANT1_MODULE`; compiler lock SHA-256 is `745e0932b4d672174dc74423c627846a88708946093756f9ee520cee7a2f33f6`.

## Observed result

Both sources compiled. The control and treatment each have a 440-byte `SIMANT1_MODULE` and a 74-byte CONST segment with 37 width-2 selector fixups at offsets 0 through 72. Group fixups remain contiguous: prefix offsets 0–52, first group 54–58, second group 60–66, final group 68–72. There is no 6-byte CONST interval; the later fixups did not shift.

The treatment's six zero bytes went to `_DATA` (length 6), not CONST. Its code segment and CONST bytes/fixups are identical to the control. Thus this ordinary `const` declaration does not model the historical zero gap. The result is a source-form feasibility blocker for this fixture; it does not establish whether a forced `#pragma data_seg("CONST")` object would work, and that different form was not tested in this bounded run.

No strict target-member oracle applies: the fixture contains only synthetic probe publics, not the `_GetMyInitialRandDir` body. Full segment bytes, all OMF fixups, publics, externals, source/compiler receipts, and hashes are in `results.json`; concise segment and selector-fixup identities are in `layout-summary.json`.

## Identities and deduplication

- Control raw OMF SHA-256: `49ffa65ce396ee10e7269540b35300161d4166a71acb87e8dd609d020134587c`
- Treatment raw OMF SHA-256: `64212ae151599acb9373f989891df037cc37f8d2559a0e168b64e5624a3b99b7`
- Control material OMF SHA-256: `4f5ab077ce7a4264820b74b86b822e03590085e0d11a1e81a8de8d1535d80d6a`
- Treatment material OMF SHA-256: `ded4a959d56a093f89d07ab51eec56b02efa9f4c369b3dfa15c87fed12ab0348`

There are two distinct raw/material objects because the treatment adds `_DATA`; the code and CONST material is byte/fixup-identical. That initial control/treatment batch stopped here: it did not demonstrate a selector-order change or CONST filler capability. The later scalar follow-up below demonstrated the filler behavior in a synthetic fixture. No production source, job, unit, proof, manifest, or tool was changed.

## Admitted `__segment` declaration follow-ups

The first `__segment` array compile initially failed because its synthetic function appeared after `#pragma alloc_text`; the failed receipt is preserved in `followup-results.json`. After adding the required forward declaration, the same array form compiled under the same MSC 7.00 profile. Its six zeros still went to `_DATA` (length 6); CONST remained 74 bytes with 37 selector fixups at offsets 0–72. The source SHA-256 is `ddfb23852f69c6c2a257a43785a8116265033ad6c1fde89e7b7e1ce16de0799a`, and the raw OMF SHA-256 is `b999fb380f7cabc618ea7c0341585da33be34d22db18cc6497a989f453ea64db`. Full receipt/layout is in `followup2-results.json`.

A final bounded discriminator used three separately declared scalars in the admitted form `static const __segment near mmSelector = __segname("SIMANT_DATA_GROUP")`, each read only by the synthetic helper. This compile succeeded with source SHA-256 `e25673908a77acf28305d30e839bc1438bd5b3e259a23e5f99d127c6dc272848` and raw OMF SHA-256 `d22705964ddadd8c7f29f1ea0c73bab3b8bf1a3cd3ebf85d9cd49ba03632f2c8`. The fixture's CONST is 80 bytes: selector fixups remain at 0–58, then six zero bytes occupy offsets 60–65 without relocations, and later selector fixups occur at 66, 68, 70, 72, 74, 76, and 78. `_DATA` is empty. This reproduces the hypothesized pool layout in this synthetic setup; it does not prove historical ownership or establish an exact member.

The scalar object is materially distinct from both prior candidates: it changes CONST length/fixup placement and adds helper references. The main `SIMANT1_MODULE` remains 440 bytes, with seven byte differences from the no-gap control; `POOLSTUB_TEXT` is 24 bytes. OMF bytes, segment data, complete fixups, publics, externals, and compiler receipt are preserved in `followup3-results.json`; source and runner are `followup3_zero_scalars.c` and `followup3.py`. The compiler lock and flags match the first batch. No strict target-member oracle applies to these synthetic publics. The experiment shows this scalar declaration form can create the six-byte CONST gap. The later root-authorized reviewed-unit diagnostic is summarized below; it achieved `STRONGLY_SUPPORTED_MEMBER` with exact real-member and CONST contributions, without establishing historical filler ownership or exact admission.
## Unit-source feasibility checkpoint

The existing native entry point is `tu_assembly.py build COMPONENT --unit-source PATH --members ... --scaffold`, followed by `tu_assembly.py test UNIT`. `build_unit` checks that the hand-written source defines every claimed member; `reviewed_scaffold` checks that named `POOLSTUB_TEXT` stand-ins have definitions and are not real component publics. The native test then runs the strict matcher for all listed members. The interface has no structured field for a scalar CONST filler: its scaffold record captures stand-in functions only.

No unit prototype was run. The existing exact-source scaffold at `evidence/recovery/units/simant1_75F4_DoAntSimY_3_scaffold/unit.c` contains `_DoAntSimY`, `_EnterNest`, `_CheckMyBestDirs`, and the `_DoAntMoveY` stand-in. It does not contain the intervening `_ExitNest`, `_GetMyDis`, or `_GetMyNextRandDirs` stand-ins needed around the measured scalar gap. The current `simant1:75F4` proposal also reports `_GetMyInitialRandDir`'s first-use order as `C3F8 C3F6 C3FA`, with missing `_GetMyBestDir`, `_GetMyDir`, and `_GetMyNextRandDirs`; its blocker row is preserved at `proposal-simant1-75F4.json`. The only preserved Initial source inspected is `evidence/recovery/workflow/jobs/GetMyInitialRandDir-72875fbed4/attempt07/candidate0000.c`. No exact sources or existing stubs for the missing introducers were available in the current unit source. Writing new stand-ins and assigning them pool words would exceed this bounded prototype's source-evidence constraint.

A future guarded interface would need an explicit reviewed filler record (source identity, declared scalar names, expected zero bytes, expected CONST interval, and expected absence of fixups) and a validator that checks the compiled filler contribution at the declared location while preserving full strict member-body, selector-fixup, private-data, and complete CONST-layout comparisons. Attempt 01 placed the scalar gap but returned `NO_COMPLETE_MATCH`; the corrected follow-up below achieved `STRONGLY_SUPPORTED_MEMBER` with exact real-member and CONST contributions. Neither result establishes historical filler ownership or exact admission.

The reviewed-unit diagnostic reports are [attempt 01](unit-diagnostic.md) and [the `MeCrazyCnt` follow-up](unit-diagnostic-followup.md). Attempt 01 emitted 82B CONST and returned `NO_COMPLETE_MATCH`. The follow-up source SHA-256 is `0ad9aba7d3f321d9ca9f3b67c24e7814d5302ac476af033a20c04dbcfc937620`; raw OMF SHA-256 is `582584699c47d56d8bfc35a9cd02a170cb252409f7f77458ab7cd2543ad86cb8`. It emitted 80B CONST with fixups at 0–58, 66/68/70/72, and 74/76/78; the six unrelocated zeros occupy 60–65, and `MeCrazyCnt` reuses C3F6 at 74. All five real contributions matched with no divergences or failed fixups. Native status was `STRONGLY_SUPPORTED_MEMBER`, no issues, 548/548 literal bytes equal and 130/197 total fixups equal. This remains diagnostic evidence only: no historical owner claim, promotion, or production admission was made. Full segment and member details are in [the native test report](../../recovery/units/simant1_75F4_DoAntSimY_4_reviewed/test/results.json).

## Native admission after reviewed filler recording

`tu_assembly.py build` now records the three separately declared zero scalars as `private_zero_gaps` with claim `UNCLAIMED_LAYOUT_SCAFFOLD` (CONST offsets 60�65, no fixups, owner `pool_stub_ZeroGap`). The unit test checks that initialized OMF interval; the unchanged complete-member matcher checks the full 80-byte CONST contribution. This metadata does not identify historical private-state ownership or credit the stand-in code.

The normal TU workflow job `tu_simant1_75F4_DoAntSimY_4_reviewed-721da53bc2` passed one exact candidate, an independent `--audit-only` rebuild, and a serialized native promotion. Its [promotion proof](../../recovery/promotions/tu_simant1_75F4_DoAntSimY_4_reviewed-721da53bc2.json) admits `_GetMyInitialRandDir` and supersedes three prior unit recipes. Strict progress rose from 523 functions / 57,510 game bytes to 524 functions / 57,601 game bytes (+1 function, +91 bytes). The five real contributions remain exact; the reserved-code stubs and measured zero scalars remain unclaimed scaffolds.
