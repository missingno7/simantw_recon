# `_SetCasteProd` frame and lexical-scope research

Production remains escalated. Its best source under the assigned MSC 7.00
`/Oeglw` profile already matches all 74 target opcodes and 13 fixups, but
uses `enter 0x16` rather than the target's `enter 0x1a`. The `pct[4]`
operands are two bytes too shallow and the `want[4]` operands four bytes
too shallow.

The first isolated seven-source batch tested the recorded nested-scope
hypothesis with different array placement and 16-bit type forms. It yielded
four effective OMF classes. Both arrays in one nested scope produced
`enter 0x18`, 71/74 opcodes and 7/13 fixups; `short` and unsigned 16-bit
forms collapsed into that same class. Splitting the percentage calculations
changed the control shape. Volatile arrays degraded codegen. The baseline
control retained 74/74 opcodes and 13/13 fixups with the original frame.

A second two-variant batch placed `pct` and `want` in opposite enclosing and
nested scopes while preserving interleaved computation. Both variants
deduplicated to the same `enter 0x18` object with 71/74 opcodes and 7/13
fixups. Sources, strict receipts, effective-output classes, and comparison
details are in `spec.json`, `evidence.json`, `nested-scope-spec.json`, and
`nested-scope-evidence.json`; those reports reference the build-local runs.

These forms neither explain the two separate stack-home gaps nor justify a
production reissue. The result is scoped to this source, unit profile, and
tested lexical layouts; it is not a general MSC7 stack-allocation rule.
