/*
 * OverlayTileSet: switch the edit view's terrain overlay tile set.
 * Ignored unless the caller passes type 0.  id 0x3e9 (1001) selects the
 * "set" terrain tiles, id 0x3e8 (1000) the clear ones; each guards on
 * editBufInvalidFlag[1] so it only frees and reloads the terrainTiles
 * handle the first time that state is requested (db_LoadObject(9|10,9,1)
 * followed by db_UnhookObject(9|10,9)); Barrier is refreshed every call.
 *
 * Written for the /Og (global CSE) profile: the far address of
 * terrainTiles is computed once (BX:ES), homed on the frame and reloaded
 * with LES after the calls; no explicit pointer local is used.
 */
extern int far editBufInvalidFlag[];
extern int far TERRAINset;
extern unsigned int far terrainTiles;
extern int far Barrier;

extern void far mem_Free(unsigned int handle);
extern unsigned int far db_LoadObject(int object, int kind, int lock);
extern void far db_UnhookObject(int object, int kind);

void far OverlayTileSet(int type, int id)
{
    if (type != 0)
        return;

    if (id == 0x3e9) {
        if (editBufInvalidFlag[1] != 1) {
            editBufInvalidFlag[1] = 1;
            TERRAINset = 1;
            if (terrainTiles != 0)
                mem_Free(terrainTiles);
            terrainTiles = db_LoadObject(9, 9, 1);
            db_UnhookObject(9, 9);
        }
        Barrier = 0x90;
    } else if (id == 0x3e8) {
        if (editBufInvalidFlag[1] != 0) {
            editBufInvalidFlag[1] = 0;
            TERRAINset = 0;
            if (terrainTiles != 0)
                mem_Free(terrainTiles);
            terrainTiles = db_LoadObject(10, 9, 1);
            db_UnhookObject(10, 9);
        }
        Barrier = 0x50;
    }
}
