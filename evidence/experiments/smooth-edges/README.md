# SmoothEdgesB / SmoothEdgesR recovery probes

These two SIMONE_MODULE members are a strict mirror pair: both are 362 bytes with the same control-flow and thresholds. The R body changes the map-plane base and colony identifiers; it does not expose a semantic asymmetry. Each packet is a single-public unit context.

## Semantic reconstruction hypothesis

- Reject x outside 0..63 and y above 63. When y is zero, change the map byte to `0x18` only when it is at least `0x30`.
- For nonzero y, reject center bytes below `0x20` and in `0x30..0x4e`. Bytes `0x20..0x2f` are normalized to zero; bytes `0x4f` and above are normalized to `0x2f`.
- Inspect the four cardinal neighbors at the guarded coordinates. A neighbor classifies as active for values `0x20..0x2f` or `0x4f` and above. The result combines the center value, `0x1f`, and directional bits; with no active neighbor, it writes `SRand8()` when the normalized center is zero, otherwise `0x4e`.

This is a readable semantic hypothesis from the branches, not source-recovery proof.

## Production evidence

- B used all eight production attempts. R received the mechanically mirrored best B source in one production attempt.
- B's best result is `attempt04/results.json`, 345 bytes versus the 362-byte target, diagnostic score 0.516, 113 aligned opcodes, and `NO_COMPLETE_MATCH`. It preserves useful readable source in `candidate04.c`.
- The mirrored R candidate has the same size and diagnostic class in `SmoothEdgesR-a8261b4ef6/attempt01/results.json`; its map offsets are correspondingly swapped.
- Both exact acceptance results are absent. Strict comparisons report body literal differences and unresolved internal fixups, including the MapB/MapR operands and translated `SRand8` call. No candidate was promoted.

## Isolated probes

`declaration-order-evidence.json` contains 24 equivalent permutations of the four local declarations from the best readable source. They produced no exact body and only two distinct comparison classes. `register-hints-evidence.json` checks all 16 register-hint subsets for the same declarations; all produced the same comparison class and no exact body. This rules out local declaration order and simple `register` hints as sufficient explanations under the assigned MSC 7 baseline.

A new attempt should wait for evidence about the target's C expression/source idiom that preserves x in SI and y in DI while placing index/current/scratch at BP-6/BP-2/BP-4. The evidence so far does not justify a compiler-profile search or proof-tool change.
