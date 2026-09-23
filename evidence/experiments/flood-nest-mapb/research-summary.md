# FloodNestB isolated recovery research summary

The isolated MAPSYM `_MapB` binding corrected the semantic fixup and gave a 60-byte body with all 27 aligned opcodes, but the best output retains seven register-only differences (target row/cell values DI/BX; candidate CX/DI). The preserved blocked production state has not been reopened.

Local source-form evidence:

- `operand-lifetime/`: 12 declaration/address combinations collapsed to one OMF object.
- `control-lifetimes/`: five nested loop forms collapsed to one OMF object.
- `pointer-scope/`: three pointer lifetime/initialization forms collapsed to one OMF object.
- `local-object-lifetimes/`: four pointer/value variants yielded distinct objects; original pointer plus `int value` remained best.
- `mapsym-type-context/`: tested flat and 64x64 `MapB` views did not improve the best class; one malformed view changed the body/fixup.
- `same-tu-context/`: appending admitted neighboring members left the target function object and its seven register mismatches unchanged. This tests following members only, not the historical preceding-member boundary.
- `predecessor-context/`: attempts using blocked `_FixExitMapB/R` drafts did not form valid compatible predecessor context (placement inconsistency / conflicting `Dx8` declaration), so they do not establish a TU-context negative.

The repeated collapses rule out additional exploration of the tested declaration, address, loop, and pointer-scope families for this candidate/profile. Remaining question: what evidenced source lifetime or valid historical TU context causes MSC7 to preserve the target's outer row in DI and inner cell in BX while forming the `SI = row + cell + _MapB` address, instead of allocating CX/DI? A useful next step needs a correctly reconstructed immediate predecessor or another evidence-backed lifetime dimension that changes live ranges; do not repeat equivalent local spellings. These findings are scoped to this function and assigned baseline profile. They are isolated research, not production credit or proof of a general compiler rule.
