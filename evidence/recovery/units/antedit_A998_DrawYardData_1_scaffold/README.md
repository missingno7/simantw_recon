# `_DrawYardData` format-string correction

The first trial used the parked source with three `"%3d"` literals. Its code
shape agreed, but five DATA offsets were unresolved and the composer inferred
overlapping private pieces. The old individual job
`DrawYardData-e344084aca` preserves both attempts and is linked to the
admission. `initial-trial/` also retains the original failed scaffold result;
the current `slots_DrawYardData/` now records the corrected source.

The executable's five call operands point to DGROUP 18C2, 18C6, 18CA, 18CD,
and 18D0. The initialized bytes at these offsets are two `"%-d"` literals and
three `"%d"` literals, occupying 17 bytes. The reviewed source
`evidence/topology/supervisor-unit-sources/DrawYardData-formats.c` changes
only those three incorrect format strings. Authentic C7 output then matched
460 code bytes, all 51 isolated fixups, 17 DATA bytes, and four CONST bytes.

The scaffolded unit passed `STRONGLY_SUPPORTED_MEMBER` and was independently
promoted in `tu_antedit_A998_DrawYardData_1_scaffold-fe4c466935`. The later
two-member `antedit_A998_DrawYardData_2_scaffold` reverified this source with
the admitted `_YardArea` source; its promotion is now the current recipe.
Unclaimed scaffold code receives no recovery credit.
