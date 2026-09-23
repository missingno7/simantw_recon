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
