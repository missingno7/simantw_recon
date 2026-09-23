# DGROUP 0x1502–0x1509 ownership follow-up

Status: diagnostic research only. No topology edit, workflow reissue, recipe change, or recovery admission was made.

## Finding

The executable evidence supports `_UpdateLayQueenModeDisplay`, `_YardToMap`, and `_MapToYard` as one code object: their selector pools share `C0D2`–`C0D8`. This code same-object proof does **not** establish that the object's private DATA contribution owns DGROUP `0x1502`–`0x1509`.

`layout/private-data-topology.json` records `DGROUP:1502` and `DGROUP:1506` as `REFERENCE_CONSTRAINT`, with references from `_UpdateLayQueenModeDisplay` and `_MapToYard`, and no `candidate_tu` or historical owner. The topology's admitted DATA evidence begins at `0x150A` in the dialog family. Thus the bytes at `0x1502` could be that selector-sharing object's contribution or a separately linked object referenced by both functions.

## Exact evidence and results

- `evidence/topology/build-topology.json` and `docs/build-topology-units.md`: component `simant:94A4` joins updater, YTM, and MapToYard through shared selector words `C0D2`–`C0D8`; the three functions' code is treated as one same-object component. This establishes code membership only.
- `evidence/recovery/workflow/jobs/MapToYard-b239e336a1/attempt05/results.json`: candidate `_DATA` contribution at segment 10 offset `0x1502`, length 8, matches the target bytes `{0x2309,0x230a,0x190d,0x190e}`. Candidate placement is not original-object attribution.
- `evidence/recovery/workflow/jobs/UpdateLayQueenModeDisplay-0d3a99e474/attempt02/results.json` and `evidence/experiments/update-lay-queen-shape/README.md`: updater's direct target operands are `0x1502` and `0x1506`; exact body shape is available, while these bindings remain unresolved in isolation.
- `evidence/recovery/units/simant_94A4_UpdateLayQueenModeDisplay_3_scaffold/test/results.json`: updater + YTM scaffold places the selector block at `C0D2` with zero CONST divergences; overall unit is `NO_COMPLETE_MATCH` (394/400 ordinary bytes, 66/75 fixups). The claimed updater's remaining differences include external candidates for `0x1502`, `0x1506`, and `0xBCEC`.
- `evidence/recovery/units/simant_94A4_UpdateLayQueenModeDisplay_3_scaffold/unit.json`: scaffold keeps updater and YTM, marks MapToYard `unclaimed_after_last`, and records no data pieces. It does not attribute the table.
- `evidence/experiments/map-to-yard-selector-pool/README.md`: the prior non-scaffolded three-member composition was `RULED_OUT_MEMBER` because public placements are inconsistent with the selected ordered unit; it cannot establish DATA ownership.
- Diagnostic command rerun: `python tools/tu_assembly.py build simant:94A4 --members _UpdateLayQueenModeDisplay,_YardToMap,_MapToYard --source _UpdateLayQueenModeDisplay=evidence/experiments/update-lay-queen-shape/candidate-exact-body.c --scaffold --harmonize --reason "Diagnostic ownership probe only: test whether the exact selector-sharing members reproduce the MapToYard private table at DGROUP 1502-1509 without topology edits or admission."` It produced isolated strict summaries only (updater 70/76 bytes, YTM 324/324, MapToYard 358/374); no completed three-member result was emitted. This is not a discriminating ownership result.

## Conclusion

The table likely belongs to or is shared by the selector-sharing code object, because both updater and MapToYard reference the same two word offsets and the MapToYard candidate reproduces the expected eight bytes there. The original DATA owner remains **unproven**. Resolving it requires original object/source-boundary provenance or equivalent linker evidence attributing `0x1502`–`0x1509`; the current executable topology and forced TU composition do not supply that evidence.
