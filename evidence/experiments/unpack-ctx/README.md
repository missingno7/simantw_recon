# SIMTWO unpacker and BlockMove compiler context

## Result

`_BlockMove` is explained by catalog profile `ogi` (`/Oegilw`) in its own singleton topology component `simtwo:783E`. The readable `_fmemcpy` wrapper compiled under `ogi` is a strict member and was promoted as `BlockMove-26138b977c`.

The LZSS unpacker family has no single catalogued profile established by these probes. `ogi` produces the `/Oi` intrinsic sequence for `_UnpackInit`'s far fill and can be made strict for `_BlockMove`, but the `_UnpackInit` body remains nonmatching, `_InitTree`'s `rep stosw` loop is profile invariant, and the `_UnpackFileClose` stack cleanup remains `add sp,2` under every tested profile and raw switch set. `_InsertNode` and `_DeleteNode` gain diagnostics under `/Og` but remain far from complete matches. No profile was assigned across the LZSS range.

## Topology scope

The unpack functions fall inside candidate range `simtwo:858A-B02A` (`SIMTWO_MODULE`, 50 publics). The named unpack functions have singleton components in the topology output; the range is not proof that every public is one object. `_Encode` immediately precedes this LZSS cluster and `_font_ReadFont` follows `_DeleteNode`. Their saved profile probes are included as boundary context. The `_BlockMove` component is also separate from adjacent `_FinishVertStep` (`simtwo:6EFE`, assigned `og`) and `_FlipHandleWords` (`simtwo:7860`); adjacency in candidate range `simtwo:6EFE-8175` does not join their compiler contexts.

## Evidence

- [`profile-probes.json`](profile-probes.json) summarizes the catalogued probes of the nine unpack functions, their immediate public neighbors, and the two immediate BlockMove neighbors. Full records remain under `evidence/experiments/optimizer-profile/probes/`.
- [`raw-probes.json`](raw-probes.json) records bounded `/Oelw`, `/Oi`, `/Os`, `/Ot`, `/Ox`, and `/Oi` + `/Os` tests for the `_fmemcpy`, `_fmemset`, close-wrapper, and LZSS tree-fill sources. Its `raw/` evidence files contain compiler receipts and strict/diagnostic outcomes.
- Sources and full search output are under `build/workers/unpack-ctx/` and `build/search/`.
- `_BlockMove` promotion proof: `evidence/recovery/promotions/BlockMove-26138b977c.json`.

These are code-generation and routing findings. The nonmatching LZSS drafts do not recover function bodies, private state placement, or object boundaries.
