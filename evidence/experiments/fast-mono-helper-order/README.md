# `_DoFastMonoBitmap`: arithmetic order, pointer ABI, cleanup tail

The production job reached eight attempts with a readable 337-byte draft but
no exact result. At the pre-solution signature, its instruction layout was
close, yet the original called `__aFldiv` at +0xA6 and `__aFlmul` at +0xAD;
the draft called them in reverse. The NE records relocate only the selector
halves at +0xA9 and +0xB0. The ordinary offset bytes are `0x08D4` and
`0x096E`, matching MAPSYM's helper entries. Reading the selector relocation
as a call to segment 4 offset zero would miss that distinction.

`spec.json` changed the image-size expression from multiplying height before
division to dividing the rounded row width before multiplying height. Both
`* 4L` and `<< 2` variants compiled to one effective object and matched both
arithmetic helper bindings (`trial/results.json`); the GDI argument and
cleanup tail still differed. `far-pointer-spec.json` replaced separate
offset/segment parameters with one far pointer. Both variants again collapsed
to one object and matched the direct stack argument pushes and GDI ordinal
443 (`far-pointer-trial/results.json`). `cleanup-spec.json` tested three
equivalent common-tail spellings. They collapsed to one object with a full
337-byte target body, all 11 semantic fixups and the three-byte private
`bm\0` data contribution matching (`cleanup-trial/results.json`). The
candidate object also has one trailing alignment byte.

The prior best object had the recognizable signature: both helper calls at
the correct instruction sites but reversed, followed by extra loads of the
source pointer words into AX/DX at +0x120 and an omitted jump after
`mem_Unlock`. The corrected source was reissued through the recorded
single-candidate `SOURCE_LAYOUT` extension (`reissue-spec.json`), then
freshly admitted by the normal production gate in
`evidence/recovery/promotions/DoFastMonoBitmap-4c72c58f17.json`.

An exact text search across preserved C sources found no other draft using
this `imageSize` expression. The adjacent ready `_DoFastBitmap` is a useful
new target for the row-stride and far-pointer lessons; its own disassembly
must decide whether the same arithmetic and cleanup apply.
