# SmoothEdgesB round-review handoff (2026-09-24)

**Decision:** no follow-up compiler experiment on this template. The unresolved oracle operand is a cached center-cell value, but the available independent evidence does not select a C storage, lifetime, or type intervention. Keep `SmoothEdgesB-6e90825f72` blocked. Return production effort to eligible jobs. This is a scoped negative, not a conclusion about changed types, lifetimes, or translation-unit context.

## Inputs and identities

| Artifact | SHA-256 |
| --- | --- |
| `../ai_decomp/research/updates/20260924-round-review/simant.md` | `56eab699e80d9b8c5e89ac94b0cf56ac0e506827bedd89c243b0acfb22331788` |
| `../ai_decomp/research/updates/20260924-round-review/review.md` | `b8d919e5f39d488824f098f738f90e3650da93de28a20c1ac0442eb8eb1b5b78` |
| `plan.json` | `579076d629800c68feb9271c06cc80509a0b1f55e6ee1ce4318c22ef2213e139` |
| `run/results.json` | `252ea7216e7b372150493bd81dbf3959335240c49fffd415c0c58bc09f479b40` |
| `analysis.json` | `d1cf20104bc88353c1447de715b160726e147410e747bbd93fdfb06b50e9903c` |
| `evidence/recovery/workflow/jobs/SmoothEdgesB-6e90825f72/job.json` | `04d825deb1ad119b91fbb15ed86c8bd17a219df60fdfb7e4b7832b61d839ed5b` at review time |

The prior plan and results were co-committed; Git history alone does not independently establish the claimed precompile freeze. All four fresh receipts report one `RUN.CONF` SHA-256 (`8a2e7411ad81461c66b2971fc939fa3def2285a9a8fae6816f6b243a8d70b527`), but its payload is unavailable. These are receipt-observed context identities, not an independently reconstructed configuration. No new plan or receipt was generated in this review because no supported new comparison was found.

## Oracle operand dataflow

The original `_SmoothEdgesB` executable extent is `SIMONE_MODULE:255A`, 362 bytes, SHA-256 `1f4a5f9b369d4d5c27bbd7835d15b3b9e01404b1d81785f8440677dcadb937bb`. It enters with a six-byte frame. At relative `+0x4E`, it loads the center `MapB` byte into `AL`; `+0x52` zeroes `AH`; `+0x54` saves `AX` at `[BP-2]`. The normalized value is stored there again at `+0x78`. At `+0x136`, `add dl, byte ptr [bp-2]` adds that center value's low byte to the edge flags in `DL`. At `+0x148`, the code tests the same word home for zero. Thus `[BP-2]` is the normalized center-cell value's target stack home, live across neighbor checks; it is **not** the edge accumulator. The target also uses `[BP-6]` for the cell index and `[BP-4]` as a scratch slot.

The `_SmoothEdgesR` target at `SIMONE_MODULE:26E4` (362 bytes; SHA-256 `a2fe25744d84fd4fea229902fc48d6af969d57cc6b2e540364788084242de93b`) repeats the relative frame and operand pattern, with the red map displacement. It corroborates the executable dataflow, but it is another unrecovered target and does not establish the historical C declaration. `evidence/disassembly/cards.md` (SHA-256 `a353cb9de301e68fae8d653e582e06a851ed8a26fd314ffddfb851177c7e7332`) and `evidence/disassembly/cfg-extents.json` (SHA-256 `ddd060e080d18b44209565572675eacc23dffb6971dd13b57f1946df1da02b95`) preserve the original extent. The parsed MAPSYM record has no line-number paragraph/source-local information for this segment.

The exact recovered `src/recovered/wf_FillDirtB-b73109489f.c` (SHA-256 `aed4d9938f626fa88a294ab3d16f38e2cd67eb2912e4ac2441151c5a1863fd2c`) and `src/recovered/wf_FillDirtR-d16ac84868.c` (SHA-256 `30e5551ee38c9aae8b1d4463796409459e2cfe8ffa7b0b038c981aa94c448cf2`) support the map's byte role and call context, not the local form inside `SmoothEdgesB`. The current job draft, SHA-256 `244fd7af7b00a44b4d3cb24657ffae3a50cfc1b40d0a122913b00d8eb3a8eb16`, is a candidate, not independent source evidence. No source, debug, or exact recovered analogue selected a storage/lifetime/type hypothesis.

## Preserved pilot response and prediction

The old plan predicted that grouped `value`-before-`edges` declarations would reproduce material class A. It did: training A and grouped holdout have material SHA-256 `8b115c476d0273ba9cd4dba1d41a40cbfa314ebcc2a71cc15608e3198ba53fff`, while their raw OMF SHA-256 values differ (`6e33dc5efa4e44dfbe87bbbf672b00c855a3d605d16b7ee4e6a6b06c07ddd9f7` and `90d5ae1d785e71d22beb89c4dd8ec505aef4194b2649a354d3643fb01dce10fa`) solely through THEADR module name/checksum. Class B material SHA-256 is `5c3ce2dc6efc2f5d1cc97bfc658bf2dbc04dd1e431ef5c9f60972394c9f695fd`. Both A and B retain `enter 2` and a register-only tail; neither explains target `enter 6` or `DL:[BP-2]`.

The `unsigned char edges` probe predicted a changed memory/frame response. It produced a distinct material class (`03b478072f8d4d62417c18097af932e438a972dfdecc2a34eed6f105de4d4617`; raw OMF `3cd138abb46d5e6cb9769560b9af86a4c561ed66a485c23566a33878a66b6174`), but emitted `add al, byte ptr [bp-1]` and still `enter 2`. This puts the wrong value in the wrong register/home and does not explain the oracle residue. Its measured code and semantic-fixup alignment regressed. The old `analysis.json` records code hashes, all four sources, candidate-to-target comparisons, and the three material classes; `run/results.json` retains each native result and object/contribution data. All four are `NO_COMPLETE_MATCH` under the complete-member gate.

## Next recovery decision

Pure declaration ordering/grouping on this exact source template, MSC 7.00 profile, and recorded context is exhausted. A novel raw OMF hash or a new material output class alone is not progress. Do not reopen another declaration permutation sweep. The next SmoothEdgesB experiment requires independent evidence for a **specific** center-value storage/lifetime/type form. If found, hold the calibrated declaration relation and compiler/TU context fixed, write a plan predicting the frame/home/operand change before compilation, retain its identity in execution receipts, compare material OMF, semantic fixups, and private contributions separately from raw hashes, and use the unchanged native strict gate. Until then, keep the production job blocked. This review made no recovery, speedup, or cross-target-learning claim.
