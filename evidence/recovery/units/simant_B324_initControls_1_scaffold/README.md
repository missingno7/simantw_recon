# `_initControls` selector ownership

The first scaffold trial stopped at selector word C144. Its result is retained
under `initial-trial/`; the three older individual attempts remain in job
`initControls-1381cecee4`.

The target `_ProcModeEvent`, an earlier public in `simant:B324`, reads C142 and
C144 through direct `MOV ES,word ptr` instructions (C0D2/C115 and C231/C313).
Both words have NE selector relocations, to segments 9 and 8 respectively.
`_initControls` reuses C142 but has no C144 read. The topology record left
`_ProcModeEvent`'s size unknown and therefore attributed neither word to it.
The old explanation that `_initControls` lacked an object access was wrong.

The composer now recognizes direct relocated selector loads in earlier publics
with unknown topology size. Its reserved stand-in allocates C142/C144 before
the claimed body. The C144 stand-in name is only a segment representative; it
does not identify the historical object. Authentic C7 compilation and the
strict member matcher then agreed on the 291-byte target extent and 50-byte
CONST block, with no member or CONST divergences or failed fixups. Fresh proof:
`evidence/recovery/promotions/tu_simant_B324_initControls_1_scaffold-03091459d8.json`.
The stand-in is uncredited construction context.
