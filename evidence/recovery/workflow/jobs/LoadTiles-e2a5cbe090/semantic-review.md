# Semantic review: `_LoadTiles`

Fresh `factory-packet.json` SHA-256 matches the assigned `775c3f0b5d2d0d857d1dd25dcd742ccd57af372162fa974f451538a25d223124`. The job remains OPEN with zero attempts. I made no candidate or strict test; the original TODO remains intact.

## Direct evidence

- `packet.json` records one incoming reference: `_IBMInitStuff` at `GR_MODULE:0x0220`. In that caller's packet, `_LoadTiles` is called without arguments during startup, after `_SetMenuEntries` and before application/window initialization.
- The target packet shows `_LoadTiles` obtains and releases database objects through `db_LoadObject`, `db_UnhookObject`, and `db_PurgeObject`, with the object/type/lock values pushed at each site. It calls `mem_Size` on loaded handles, allocates temporary blocks, and copies each measured extent using `rep movsw` followed by `rep movsb` for a possible odd byte. The exact copy extent is therefore handle-specific, not a constant inferred from the target.
- The conversion loops pass `0x10, 0x10` and far pointers into `_ConvertMaskBitmap`; observed destination offsets include `0x80`, `0x5080`, and `0xa080`, with repeated `0xa0` increments. These are call arguments and pointer arithmetic, not proof of source-file dimensions, object bounds, or the packed tile format.
- The packet binds the repeated stores at `ES:[BX]` to `_match_position` under its stated DS assumption. Other selector loads at `0xbf80` through `0xbf8c` lack exact MAPSYM names in this packet; the nearby based-segment access at `ES:[0x8df8]` does not prove which higher-level state should be assigned in C. I did not infer additional globals from those offsets.
- The admitted `src/recovered/wf_OverlayTileSet-83853d3d3a.c` establishes its own terrain overlay behavior: it changes `_TERRAINset`, frees/reloads `_terrainTiles` using object IDs 9/10 and database type 9, and calls `db_UnhookObject`. It does not call `_LoadTiles` or describe the image data consumed by `_ConvertMaskBitmap`.
- `assets/` contains the external `.DAT`/`.NDX` companions, but the checked-in evidence does not map `_LoadTiles`' database object IDs to decoded payloads or a tile/mask layout. The only adjacent `_ConvertMaskBitmap` references are disassembly; there is no admitted `src/recovered` implementation establishing its source/destination format contract.

## Concrete blocker and next experiment

The broad purpose is loading database-backed tile data and converting 16-by-16 regions, but the source contract needed for a faithful draft is missing: the loaded object IDs are not tied to decoded payload bytes, and `_ConvertMaskBitmap`'s format and bounds are not established by admitted source. Writing C now would invent the object-to-file mapping, bitmap/mask layout, and storage bounds. The target also contains computed-size `REP MOVSB` sequences; the packet's `intrinsic-fingerprints` rule classifies that shape as `/Oi` evidence, while this unit is assigned `/Oeglw`. That is unit-level code-generation evidence, not authorization to change this job's profile or hand-code assembly.

Next, obtain a decoded/indexed view of the relevant database records for the exact IDs in this target and a proof-backed `_ConvertMaskBitmap` contract. Then map its observed pointer arguments to those record fields and bounds before drafting or testing `_LoadTiles`.
