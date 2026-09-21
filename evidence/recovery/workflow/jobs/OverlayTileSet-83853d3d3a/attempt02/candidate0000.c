/*
 * OverlayTileSet: switch the edit view's terrain overlay tile set.
 * Ignored unless the caller passes type 0.  id 0x3e9 (1001) selects the
 * night/set terrain tiles, id 0x3e8 (1000) the day/clear ones; each
 * guards on editBufInvalidFlag[1] so it only reloads terrainTiles (and
 * frees the previous handle) the first time that state is requested,
 * but TERRAINset and Barrier are refreshed every call.
 */
extern int far editBufInvalidFlag[];
extern int far TERRAINset;
extern unsigned int far terrainTiles;
extern int far Barrier;

extern void far mem_Free(int handle);
extern unsigned int far db_LoadObject(int object, int kind, int lock);
extern void far db_UnhookObject(int object, int type);

void far OverlayTileSet(int type, int id)
{
    unsigned int far *tiles;

    if (type != 0)
        return;

    if (id == 0x3e9) {
        if (editBufInvalidFlag[1] != 1) {
            editBufInvalidFlag[1] = 1;
            TERRAINset = 1;
            tiles = &terrainTiles;
            if (*tiles != 0)
                mem_Free(*tiles);
            *tiles = db_LoadObject(9, 9, 1);
            db_UnhookObject(9, 9);
        }
        Barrier = 0x90;
    } else if (id == 0x3e8) {
        if (editBufInvalidFlag[1] != 0) {
            editBufInvalidFlag[1] = 0;
            TERRAINset = 0;
            tiles = &terrainTiles;
            if (*tiles != 0)
                mem_Free(*tiles);
            *tiles = db_LoadObject(10, 9, 1);
            db_UnhookObject(9, 10);
        }
        Barrier = 0x50;
    }
}
