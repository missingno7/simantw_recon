# MSC 7.00 register allocation experiments

These artifacts preserve controlled probes compiled through `python tools/search.py` and the seven target-specific searches. Every row in `results.json` contains the catalogued symbol profile and flags, compiler receipt, OMF object hash, disassembly through the function return, strict member result, and an aligned diff copy where the source was compared with a target member.

## Profiles

- Most allocation, type, call, and frame probes were compiled through `_RallocFindMem` using the catalogued baseline `/AL /G2 /Gs /Oelw /NTGR_MODULE` profile. The probe function uses that target symbol only to select its real MSC 7.00 object profile; its body is not a recovery candidate for `_RallocFindMem`.
- `og_*.c` and the `/Oeglw` controls were compiled through `_SimQueenR` using `/AL /G2 /Gs /Oeglw /NTSIMANT1_MODULE`.
- `init_pointer_*.c` and `draw_pointer_*.c` use the actual `_InitAntLions` and `_DrawSimKid` profiles respectively.
- Target variants were compiled with the exact symbol profiles recorded in their rows. A diagnostic resemblance is not a strict match; only a complete member match could be promoted.

The named probe sources are in `sources/`. `results.json` uses paths relative to this directory. It records disassembly directly parsed from each compiler-produced OMF object; `diagnostics/` holds the corresponding aligned instruction diffs for target comparisons. The original transient search report paths are also kept in the JSON for traceability; the compiler and comparison facts needed for these lessons are copied here.

## Experiments covered

`r3_register_tie_*.c`, `r3_register_three.c`, `r2_*`, `r3_*`, `r4_*`, `frame_order*.c`, and pointer probes isolate register selection, types, liveness, address exposure, local frame homes, and far-pointer reloads. `og_*.c` cover `/Oe` behavior. The final runs cover candidate variants for `_GetMyBestDirs`, `_SimQueenR`, `_AnimYellowInsane`, `_DoExpMenu`, `_DrawSimKid`, `_InitAntLions`, and `_RallocFindMem`.

All controlled probes compiled successfully. The target-specific variants currently have no `exact_candidates`; their entries are retained as hypotheses and negative results, not as recovered source.
