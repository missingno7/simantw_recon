# `_PlacePillTile` coordinate lifetime probe

The target at `SIMTWO_MODULE:4CDC` is 40 bytes. Its first live sequence is
`MOV DI,[BP+6]`, `MOV SI,[BP+8]`, `PUSH SI`, `PUSH DI`, then the far
`IsValidA` call. After the call it uses DI as the high coordinate in the
`MapA` index. The preserved direct source (`src/recovered/PlacePillTile.c`)
matches all 20 opcodes, size, call and map bindings, but C7 loads the
coordinates in the opposite DI/SI order.

Two explicit coordinate-snapshot sources were tested under the component's
recorded `og` profile with authentic MSC 7.00. Both make the post-call DI
index use agree, but C7 emits `MOV SI,[BP+8]; PUSH SI; MOV DI,[BP+6]; PUSH DI`
instead of loading both before the pushes. They retain the 40-byte extent
and both semantic bindings; ordinary bytes are 28/34. Applying `register`
to one or both formal parameters compiled to the same result. The sources,
specifications, and complete comparisons remain here; no admission or
production-budget attempt occurred.

The next experiment needs a causal explanation for the argument-load/push
schedule, rather than another local or parameter spelling that C7
canonicalizes. The target's call and indexed memory effects are not in
question on this evidence.

## Bounded follow-up, 2026-09-23

Four isolated batches under the assigned `/Oeglw` profile tested 24 source
variants without touching the production job. Declaration and assignment
order, `register` locals, linear versus two-dimensional byte-array views,
equivalent 64-byte row index spellings, and prototyped versus K&R callee
declarations reduced to three effective object
hashes across all batches. Every result retained the 40-byte extent and both
semantic bindings, but none matched the target's register/load schedule.
The specs and strict results are in `declaration-order-*`,
`index-representation-*`, `array-shape-*`, and `call-declaration-*` here. These are negative
results for this profile and these representations, not a general C7 rule.

The independently recovered `_db_ReplaceObject` begins with the same
`MOV DI,[BP+6]; MOV SI,[BP+8]; PUSH SI; PUSH DI` sequence as the target.
Its source reuses both parameters in later calls, which may explain their
early register loads. `_PlacePillTile` also reuses both coordinates after
the call, but the tested source forms do not produce that schedule. A new
experiment should change the causal register-lifetime hypothesis, not
repeat declaration or array spelling permutations.
