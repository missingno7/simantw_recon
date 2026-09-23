# `_ClearHistory` private PACK array probe

The current blocked reclassification finds 90/90 aligned opcodes and a
299-byte body when nine history arrays are declared as distinct external far
objects. Its remaining failures are unresolved offsets at the nine `MOV DI`
sites and corresponding selector targets. The original has nine distinct
segment-9 selector words, while the arrays' segment-9 offsets have no MAPSYM
names. This is an exact-body hypothesis, not an admission.

`spec.json` tested two isolated declarations under the assigned baseline
profile: nine tentative `static __based(__segname("PACK"))` arrays and nine
explicit zero-initialized equivalents. Both compiled to 268-byte code with
only 49/266 ordinary bytes and 1/68 fixups agreeing. Both therefore change
the body as well as private contributions. `trial/results.json` retains the
complete comparisons. Neither variant was submitted to the production job.

A third isolated probe used nine `extern __based(__segname("PACK"))` arrays.
It also produced a 268-byte body with 49/266 ordinary bytes and 1/68
fixups agreeing (`extern-based-trial/results.json`). Extern placement alone
does not restore the target's separate ES reloads under this profile.

The next useful question is ownership and placement of the nine separate
history arrays across the `simant:8A76` unit and neighboring data, including
why the original reloads ES for each array. Repeating standalone based-array
spellings will not resolve the observed body difference.
