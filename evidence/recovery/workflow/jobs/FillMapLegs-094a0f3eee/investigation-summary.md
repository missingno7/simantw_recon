# `_FillMapLegs` bounded recovery outcome

Status: no exact source found; no acceptance or promotion. The best readable draft is restored at `candidate.c` from attempt 01. Strict receipts and effective output diffs for all compiled attempts are retained in `attempt01` through `attempt04`.

## Target semantics established from the 503-byte member

The function operates on the near `MapA` grid (64-byte row stride), with row bounds at `BP+6/+8`, column bounds at `BP+0xA/+0xC`, and fill byte at `BP+0xE`. It fills the inclusive rectangle with the supplied byte. It then visits each rectangle cell and, when `SRand1(20)` returns zero, stores `SRand1(5)+0x38`. Finally, four 4-by-4 corner areas are filled with `0xC0`: upper-left, lower-left, upper-right, and lower-right. Target evidence: direct writes use displacement `0x28E8`, and the two random-number call sites target `_SRand1` at SIMONE_MODULE offset `0x158A`.

The first fill and all four corner fills use contiguous `rep stosb` runs. `FillMap` in the same unit provides a nearby example of this run layout. The task packet maps displacement `0x28E8` to possible public `_MapA`; its binding is not an exact MAPSYM identity in this function packet.

## Strict attempts and effective outputs

- Attempt 01: 526 candidate bytes; 141/206 aligned opcodes; 0/8 fixups. This is the best body/output so far. It retains a readable rectangle/random/corner hypothesis, but its entry/control-flow shape, local layout, and fixups remain wrong.
- Attempt 02: canonical pointer/for-loop byte runs, 466 bytes; 56/206 opcodes; 0/8 fixups.
- Attempt 03: do/while pointer stores for those runs, 466 bytes; 64/206 opcodes; 0/8 fixups. Its OMF hash differs from attempt 02, so these are separate outputs rather than a deduplicated duplicate.
- Attempt 04: ordinary external `memset` declaration with no compiler pragmas, 476 bytes; 29/206 opcodes; 0/13 fixups. It emitted call fixups rather than the target's inline `rep stosb`.

The workflow rejected a pragma-based `memset` intrinsic experiment before compiling because the handoff lane permits self-contained ordinary C without compiler pragmas. A literal pointer cast to `0x28E8` was also rejected for expert review; neither rejection consumed a strict compile. No generated object bytes or proof tools were altered.

## Remaining discriminator

Find a supported ordinary-C source idiom under the assigned C7 baseline that emits the target's inline `rep stosb` runs while preserving the target's frame and operand schedule. Then test the best body with the `simone:3120` unit context so the `_MapA` and `_SRand1` bindings can be validated together. Do not accept on semantic similarity or isolated numeric-offset coincidence.