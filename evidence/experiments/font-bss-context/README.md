# GR font pair: BSS identity and TEXTMETRIC fields

The prior reviewed unit `gr_1560_GSetSmallFont_2_reviewed` used explicitly
initialized zero statics in `_DATA` and one shared `avgWidthByte`. Its failed
source, compiler output and comparison remain in the unit's `initial-trial/`.

DGROUP CC54 is above `_edata` CA60 and lies in BSS. Target code reads CC54 as
a shared two-byte `savedFont`; `_GSetSmallFont` uses CC56 for its byte scratch,
while `_GSetBigFont` uses CC57. Removing the explicit zero initializers and
giving each function its own byte creates an authentic four-byte `_BSS`
contribution at CC54. The intermediate `split-trial/` then matches all 77
fixups and every private contribution, leaving eight ordinary byte differences.

Those differences are the TEXTMETRIC stack offsets. The target reads
`tmExternalLeading + tmHeight` for the average byte and
`(tmAveCharWidth + tmMaxCharWidth) / 2` for the based PACK byte. The old
reviewed unit had swapped these calculations; the preserved individual bodies
already had the target expressions. `exact-trial/` verifies the corrected
source as a complete 520-byte pair. The durable reviewed source is
`evidence/topology/supervisor-unit-sources/gr_1560-bss-fields.c`.

Fresh independent unit proof:
`evidence/recovery/workflow/jobs/tu_gr_1560_GSetSmallFont_2_reviewed-d4616416c8/promotion.json`.
It matches 520 code bytes, 41 DATA bytes, two CONST bytes, four BSS bytes, two
PACK bytes, and all 77 fixups. The prior individual jobs are linked as
superseded; their attempts are retained.
