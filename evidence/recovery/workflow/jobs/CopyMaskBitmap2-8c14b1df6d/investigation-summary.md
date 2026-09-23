# `_CopyMaskBitmap2` bounded investigation

Status: no exact candidate; no acceptance or promotion.

## What the target establishes

The confirmed member extent is 496 bytes at `SIMTWO_MODULE:B110`. Its stack
arguments are destination far pointer at `BP+6`, source far pointer at `BP+0xA`,
destination height/width at `BP+0xE/+0x10`, source height/width at
`BP+0x12/+0x14`, and signed X/Y at `BP+0x16/+0x18`.

The entry clips negative X/Y by deriving source offsets, rejects origins at or
beyond the destination bounds, and clips the right/bottom copy extent. It then
converts source X and width from pixels to packed-byte indices and computes each
4-bpp DIB row stride as `(((width * 4 + 31) >> 5) << 2)`. Source and destination
far row pointers are formed from those strides. The pixel loop treats nibble
value `0xD` as transparent, merges each nontransparent nibble into the matching
half-byte in the destination, and handles odd X by rotating the paired nibble
positions. The row loop starts at the clipped source Y and stops at the clipped
copy height.

Four carry-normalization sites adjust ES by KERNEL ordinal 114 (`__AHINCR`):
two while forming initial row pointers and two while advancing rows. This is
distinct from the ordinal 113 calls emitted by the first `huge`-pointer draft.

Ten unnamed word operands occupy DGROUP offsets `BB08` through `BB1A` at two-byte
steps. Packet bindings provide no MAPSYM names, possible DGROUP names, or
selector identity for these operands. Their roles from use are source X byte
index (`BB08`), copy-width byte count (`BB0A`), source Y (`BB0C`), copy height
(`BB0E`), destination/source stride (`BB10`/`BB12`), destination offset/segment
(`BB14`/`BB16`), and source offset/segment (`BB18`/`BB1A`). This use evidence
does not establish their original declarations, initialization, object boundary,
or TU placement.

## Strict compile outcomes

`attempt01` compiled the readable nibble-merge hypothesis with one static state
struct and `huge` row pointers. It did not match: 554 candidate code bytes versus
the 496-byte target, 10/554 ordinary bytes equal, 0/51 fixups equal, private
`_DATA` placement unresolved, and the function extent was not structurally
closed. It emitted KERNEL ordinal 113 normalization relocations rather than the
target's ordinal 114 sites.

`attempt02` changed only the row pointer representation to ordinary `far` and
removed the long casts from row-offset products. It also did not match: 408
candidate bytes, 9/408 ordinary bytes equal, 0/35 fixups equal, unresolved
private `_DATA`, and no KERNEL normalization relocations. This rules out both
tested compiler-managed `huge` normalization and unadjusted `far` arithmetic as
the target form under the assigned MSC 7.00 profile. The receipts and complete
effective-output diffs are preserved in the two attempt directories; source
snapshots are `candidate.c` and `candidate-far-pointer.c`.

## Remaining discriminating question

Can readable C in the actual `simtwo` unit context express the target's explicit
far-row segment normalization (the four ordinal-114 `__AHINCR` sites), while
also binding the ten unnamed scratch words at their target DGROUP offsets?
Before another body search, establish a caller-supported source idiom for that
manual far-pointer carry adjustment and obtain TU/DATA identity evidence for
`BB08..BB1A`. Do not infer either from numeric offsets alone.
