# `_GetEnterDirB` lexical lifetime probe

Isolated MATCH_BLOCKED research only. Neither production job was reopened or
modified. The B member was tested under its current baseline profile
(`/AL /G2 /Gs /Oelw /NTSIMONE_MODULE`). The R mirror was intentionally not
retested because none of the B variants produced a new effective object.

## Evidence and bounded batch

The fresh packet and attempt02 diff show a complete 152-byte, 60-opcode body
with all 12 fixups and selector bindings correct. The five remaining operand
differences are only stack-home assignments: target `back = dir ^ 4` uses
`[bp-4]` and `bestValue` uses `[bp-6]`; the preserved candidate reverses these
homes. Earlier attempts covered local declaration order, names, initializers,
condition operand order, loop/body structure, and `nx`/`ny` assignment order.

This probe tested three new lexical scopes on B while preserving initialization
and loop statement order:

1. Scope `back` from its assignment through the loop.
2. Scope `bestValue` from its assignment through the loop.
3. Scope both locals together around their original initializations and loop.

All three compiled and produced the same OMF SHA-256 as attempt02:
`e7009280bc61a8fdcf7ecc15b4ff918f7855800a865ddd5bdc75118b551242fa`.
Each strict result is `NO_COMPLETE_MATCH`, 127/132 ordinary bytes, 12/12
fixups, 152-byte contribution, 60/60 opcodes, and the same five stack-local
differences. Thus neither narrower lifetime nor their combined block changes
the local-home allocation under C7 baseline. Because the effective object
class did not change, mirroring the variants to R would duplicate the same
evidence and was skipped.

## Reproduction

- The three controlled source/spec pairs are `back_block.*`,
  `bestvalue_block.*`, and `both_block.*` in this folder.
- `representative-result.json` archives the strict comparison for `back_block`.
- Per-variant full results and diffs are in
  `build/experiments/getenterdir-lifetime-{back,best,both}/`.
- The stack-home distinction remains the only useful blocker; another source
  hypothesis would need new evidence about allocator/use weighting rather than
  repeating local ordering or lexical scoping.
