# MapToYard selector-pool / private DATA investigation

Status: diagnostic only. `_MapToYard` remains `BODY_MATCHED_BINDING_BLOCKED`; this investigation does not change or reopen its recovery job.

## Observed strict signature

`evidence/recovery/workflow/jobs/MapToYard-b239e336a1/attempt05/results.json` reports a 529-byte target and candidate, 156/156 aligned opcodes, identical instruction layout and CFG, 49/60 fixups, and eight memory-operand differences. All eight are selector loads emitted with unresolved `CONST` fixups at target pool words `C0D6`, `C0D8`, and `C0D2`. The initialized private DATA table itself matches: candidate contribution placement is segment 10 offset `0x1502`, and its eight bytes are the two target pairs `{0x2309,0x230a}` and `{0x190d,0x190e}`.

## Discriminating unit tests

- Topology predicts `_MapToYard` pool first-use order `C0D6, C0D8, C0D2`; the original contiguous block is `C0D2, C0D4, C0D6, C0D8`. The missing preceding `_UpdateLayQueenModeDisplay` uses `C0D2`; exact `_YardToMap` uses `C0D4, C0D6, C0D8`. This supports an ordering hypothesis, not proof that the target pair shares an object.
- `python tools/tu_assembly.py build simant:94A4 --members _YardToMap,_MapToYard --scaffold ...` generated `evidence/recovery/units/simant_94A4_YardToMap_2_scaffold/unit.json`. The scaffold preserved `_YardToMap` as the only claimed member and listed `_MapToYard` as unclaimed after it. Its pool report assigns `_YardToMap`'s observed words `C0D4/C0D6/C0D8`; it did not reproduce MapToYard's `C0D2` first use. This does not establish a strict unit match.
- `python tools/tu_assembly.py build simant:94A4 --members _MapToYard --scaffold ...` compiled the isolated best body (358/374 ordinary bytes, 49/60 fixups) but refused to compose it because the private DATA placement was outside the component block. This distinguishes selector-pool order from the independent table-placement constraint.
- Adding the missing updater, YTM, and MapToYard to one diagnostic build exposed declaration conflicts (`clip_*` far/near declarations and the updater's `extern` versus MapToYard's `static` table names). That build ended `DECLARATION_CONFLICT`; it did not test the proposed ordering.

## Next question

Can `_UpdateLayQueenModeDisplay` be recovered as an exact body under its assigned profile, with its shared table declarations resolved from evidence? If yes, build the ordered three-member unit and check whether the pool lands at `C0D2 -> C0D4 -> C0D6 -> C0D8`; then separately verify the MapToYard private DATA contribution at `0x1502`. Until an exact introducer and a complete strict unit result exist, keep production blocked.

## Ordered three-member follow-up (diagnostic, 2026-09-23)

The body-shape probe in `evidence/experiments/update-lay-queen-shape/candidate-exact-body.c` now supplies an exact body for `_UpdateLayQueenModeDisplay`. `tu_assembly.py build simant:94A4 --members _UpdateLayQueenModeDisplay,_YardToMap,_MapToYard --source ... --harmonize` recorded five evidence-backed declaration trials. Harmonization found exact-body-preserving spellings for the three clip declarations and both array declarations; no conflict remained.

The first non-scaffolded unit test was `RULED_OUT_MEMBER` with “inconsistent public placements for SIMANT_MODULE”: these three members are separated by unclaimed code in the original component, so an ordered source alone cannot preserve all three public anchors. The scaffolded rebuild therefore kept the two testable members and reported `_MapToYard` as unclaimed after `_YardToMap`.

The strict scaffold test for `_UpdateLayQueenModeDisplay` plus `_YardToMap` reports:

- `_UpdateLayQueenModeDisplay`: original code placement `SIMANT_MODULE:0x94A4`, length 108; same layout/CFG, 33/33 opcodes, zero branch-target differences. Remaining differences are only its external candidates for direct target DATA operands at `0xBCEC`, `0x1502`, and `0x1506` (three fixups; 6 differing literal bytes).
- `_YardToMap`: original code placement `SIMANT_MODULE:0x972A`, 494 compared bytes including alignment; zero byte divergences and zero failed fixups.
- CONST: candidate contribution placed at `0xC0D2`, length 8, zero divergences and zero failed fixups. This strictly reproduces the target's `C0D2/C0D4/C0D6/C0D8` selector block with the missing introducer followed by YTM.
- Overall unit result remains `NO_COMPLETE_MATCH`: 394/400 ordinary bytes and 66/75 fixups equal. Full report: `evidence/recovery/units/simant_94A4_UpdateLayQueenModeDisplay_3_scaffold/test/results.json`.

The independent MapToYard attempt05 strict comparison also verifies its candidate `_DATA` contribution at `0x1502`, length 8, with zero divergences. However, topology currently records only DATA word `0x150A` for component `simant:94A4`; the scaffold planner excludes the `0x1502` table as outside that component's proven data block. This is an ownership boundary, not a failed byte-value hypothesis. Do not force the arrays into the unit by changing topology or bypassing the scaffold's strict exclusion.

Next question: what independent evidence establishes that DGROUP `0x1502..0x1509` belongs to the same source unit as this selector block, rather than an earlier data contribution? A reviewed object/source boundary or additional relocation/data ownership evidence is needed before a complete three-member TU test can include MapToYard.
