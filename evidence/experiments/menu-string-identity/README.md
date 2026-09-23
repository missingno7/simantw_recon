# Shared menu strings: bounded negative tests

The target `_SetMenuEntries`, `_PauseGame`, and `_SetPause` all load near
DGROUP addresses `0x0900` and `0x0911` for the two pause menu texts. The
bytes at those addresses are `"Un&pause\tShift+0\0"` (17 bytes) and
`"&Pause\tShift+0\0"` (15 bytes). `_SetMenuEntries` is already admitted;
the two pause routines retain preserved diagnostic body matches.

The scaffolded four-member unit
`evidence/recovery/units/simant_4C24_SetMenuEntries_4_scaffold/` uses the
preserved literal-bearing bodies. Authentic MSC 7.00 emits three pairs of
strings (`_DATA` length 96), so its six code references cannot all place the
same private segment contribution at the target addresses.

A reviewed unit trial at
`evidence/recovery/units/simant_4C24_SetMenuEntries_4_reviewed/` tested a
single shared named object. Two separate static arrays inserted a padding
byte before the second text (`_DATA` length 33). A single contiguous array,
then a struct with 17-byte and 15-byte character fields, produced the right
32 data bytes but changed each routine's conditional pointer expression:
the resulting code segment was 942 bytes instead of 926 and public placements
failed. All three readable source variants and their authentic compile
identities and public offsets are retained here in `probe-results.json`.

A targeted baseline unit compile with `/Gf` still emitted 96 data bytes;
`/GF` produced C7 warning D4002 (unknown option). These observations do not
justify changing the assigned compiler profile. The next experiment must
explain a source-level shared identity that retains the target's direct
`mov ax,offset` choice in all three bodies. Do not use numeric-address casts
or allow overlapping private contributions to bypass the binding obligation.
