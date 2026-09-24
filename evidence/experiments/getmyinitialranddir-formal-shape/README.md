# `_GetMyInitialRandDir` selector argument formal-shape microfixture

This is a small isolated MSC C7 compilation experiment. It does not change the production candidate or job, build a unit, or attempt admission.

## Semantic evidence

The caller packet records an NE type-2 relocation at `_GetMyInitialRandDir+0x46` to internal segment 9, offset 0 (the PACK selector). The `_GetMyRandDirs` target packet shows its first two arguments as far pointers at `[bp+6]` and `[bp+0xa]`; the third overall argument is the scalar word at `[bp+0xe]`, and the callee passes that word as the first parameter to `TileCanBeMovedOn`. The preserved callee source and sibling caller drafts also declare the remaining ordinary arguments as `int`. That supports an `int` formal for this argument, not a near pointer.

The admitted multimedia unit uses `static const __segment near mmSelector = __segname("SIMANT_DATA_GROUP")` as a named selector source. The prior segment-expression experiment showed raw `__segname("PACK")` in an `unsigned int` call position produces a width-2 LOC2 fixup to segment PACK. Casting that special segment value to `int near *` failed in production attempt06 with C2440.

## Fixture results

`scalar-int.c` declares the third callee parameter as `int` and passes `__segname("PACK")`. It compiles cleanly. The third argument is emitted as `PUSH imm16` (`68 00 00`), with a width-2 LOC2 fixup targeting segment `PACK`; later scalar arguments are pushed before it, as expected for right-to-left argument evaluation.

`segment-formal.c` uses `__segment near` for that parameter. It emits the same bytes, fixup target, and object hash, but C7 warns that the memory attribute on the parameter is ignored. It is not a distinct ABI/codegen class and the callee evidence specifically shows an ordinary scalar argument.

The prior near-pointer control remains in `../getmyinitialranddir-segment-expression/offset-control.c`: it emits a width-2 LOC1 offset fixup against external `_match_position`. Attempt06 is the negative cast control. Full compiler receipts, fixups, and hashes are in `results.json`.

Conclusion: the only source-backed formal among these is scalar `int`; with the raw `__segname("PACK")` argument, it yields the target selector relocation. This is still only a microfixture. It is not a production function test or recovery proof.