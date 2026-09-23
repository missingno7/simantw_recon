# FloodNestB MAPSYM array view

Six controlled candidates tested the flat `MapB[]` declaration against the nearby verified `unsigned char near MapB[64][64]` declaration and three equivalent flattened address expressions. Four compiled candidates collapsed to the same best OMF object (`770fe47da6cc...`), retaining seven register-only differences and the exact one `_MapB` fixup. One form failed because it subscripted a flat declaration; the 2D declaration paired with uncast `MapB + row + cell` emitted a distinct 72-byte object with all body bytes and the `_MapB` fixup wrong.

The MAPSYM-backed 64x64 view is consistent with neighboring recovered users, but it does not alter the body when flattened as tested. Full results include the compile failure and negative class; no promotion was attempted.
