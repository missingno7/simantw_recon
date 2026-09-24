# `_GetMyInitialRandDir` selector/offset microfixture

This isolated MSC C7 experiment tests whether the call's third word can be
expressed as the PACK segment selector rather than the far symbol's offset.
It does not edit the production candidate, job state, or manifests.

The target packet records a width-2 NE relocation at member offset `+0x46`
(source type 2) to internal segment 9, offset 0, the `_match_position` /
PACK selector. The preserved attempt05 source casts `match_position` to a
near pointer; its corresponding OMF fixup is LOC1 (offset), which does not
match that NE selector relocation.

`offset-control.c` compiles the near-pointer-cast argument. It emits
`PUSH imm16` and a width-2 LOC1 fixup against external `_match_position`.
`selector-treatment.c` changes only the argument expression to
`__segname("PACK")`; C7 emits the same `PUSH imm16` bytes and a width-2
LOC2 fixup targeting segment `PACK`. The object segment name is represented
by the named `PACK` segment, with no numeric selector constant or invented
object declaration.

This is a positive compiler-expression class: the MSC `__segname` expression
is a source-grounded way to ask for the named segment selector and it
reproduces the target's relocation class. It is not a full candidate test,
unit proof, or admission. Results and hashes are in `results.json`.

Related evidence: the compiler's named-segment facility is used in admitted
sources such as `src/recovered/wf_IsMMWaveAvail-6cf4f4e231.c`; the selector
and based-view patterns are documented in `evidence/experiments/mm-state-structure/README.md`.