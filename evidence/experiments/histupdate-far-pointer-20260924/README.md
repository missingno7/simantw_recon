# HistUpdate typed far-pointer probe

Isolated experiment from the best saved named-H-buffer source (`setup.json` records the base identity). The factory packet binds the target's indexed word read at offset 37520 to `_Dx8`, with selector slot 49284 targeting segment 8 and displacement zero. The loop initializes SI to `0x8e54`, reads four words at `0x8e54`, `0x8e56`, `0x8e58`, and `0x8e5a`, increments SI by two, and exits at `0x8e5c`. The tested source preserves that range using an `int far *` initialized from `Dx8 + 0x8e54`, an endpoint at `Dx8 + 0x8e5c`, and one-int pointer increments.

Only pointer storage varies: ordinary `int far *p` versus `register int far *p`. Exact forms, base/template hashes, and semantics are in `setup.json`; the full compiler receipts and comparisons are in `run/results.json`.

## Result

Both candidates compiled under baseline MSC 7.00 `/AL /G2 /Gs /Oelw /NTSIMANT_MODULE`. They collapse to one effective OMF, size 1238 bytes, SHA-256 `a8699a0ec202d5acb12b914df3829db93def8edd70618529cf9ae6a65ae6d0a9`, distinct from the prior 1239-byte integer-offset OMF. Register qualification did not affect code generation.

Both strict results are `NO_COMPLETE_MATCH`, with 321 candidate bytes versus 317 target bytes, 83/93 opcodes, layout false, CFG true, 6/322 literal bytes, and 0/74 fixups. `tu_assembly.body_exact` is false for both. In the loop the candidate loads a far pointer via private fixups and `LES BX,[bp-4]`, rather than the target's selector load plus `ES:[SI]`; SI remains the candidate index register, with pointer advancement through `[bp-4]`. This is a regression from the prior named-buffer integer-offset candidate (84/93 opcodes and 9/322 literal bytes), and does not approach target DI-index/SI-pointer allocation. Stop this pointer-storage axis.

No production job, proof, manifest, ledger, or tool was changed; no promotion or recovery credit is claimed.
