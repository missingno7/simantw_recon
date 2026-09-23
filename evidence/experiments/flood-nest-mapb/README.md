# FloodNestB named near-map binding probe

The preserved blocked draft used an invented external `_nestMap` and added
`0x48E8` to its index. Authentic MAPSYM instead names `_MapB` at DGROUP
`0x48E8`; the target's `add si,0x48E8` is a near data binding to that object.
This is new evidence relative to the job's original `FAR_POINTER_TYPE`
blocker, but it does not by itself recover the function.

`build_spec.py` made a three-candidate isolated batch from the preserved
attempt02 source. All three used `extern unsigned char near MapB[]` and
`MapB + row + cell`; the axis tested ordinary and the two previously observed
register declaration orders under the assigned baseline MSC7 flags. The
`trial/results.json` comparison reports a 60-byte body, 27/27 aligned opcodes
and 1/1 semantic fixups for every candidate. The ordinary and register
row/cell declarations collapsed to one raw OMF object
`770fe47da6cc...`; the reversed declaration order produced
`0916467c5aa0...`. Neither matched ordinary bytes. The better class has
seven register-only differences: target row/cell use DI/BX, while the
candidate uses CX/DI. The next experiment should change operand/lifetime
structure or inspect same-unit context, not repeat this declaration family.

These are isolated research results. The production job remains blocked, and
the normal strict promotion gate has not been invoked.
