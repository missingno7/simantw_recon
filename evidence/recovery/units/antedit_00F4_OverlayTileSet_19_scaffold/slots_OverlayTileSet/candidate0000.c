/*
 * OverlayTileSet: switch the edit view's terrain overlay tile set.
 * Ignored unless the caller passes type 0.  id 0x3e9 (1001) selects the
 * "set" terrain tiles, id 0x3e8 (1000) the clear ones; each guards on
 * the private terrain-set state word so it only frees and reloads the
 * terrainTiles handle the first time that state is requested
 * (db_LoadObject(9|10,9,1) followed by db_UnhookObject(9|10,9)); Barrier is
 * refreshed every call.
 *
 * Unit review (antedit:00F4): the state word lives at SIMANT_DATA_GROUP
 * 0x8DF8, the unnamed word after editBufInvalidFlag, and is addressed
 * through its own selector word (BF7E) while editBufInvalidFlag itself is
 * addressed through a different word (BF8A) elsewhere in the object: it is
 * this object's private based static, not terrainSetState.
 *
 * Written for the /Og (global CSE) profile: the far address of
 * terrainTiles is computed once (BX:ES), homed on the frame and reloaded
 * with LES after the calls; no explicit pointer local is used.
 */
static int __based(__segname("SIMANT_DATA_GROUP")) terrainSetState;
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
        if (terrainSetState != 1) {
            terrainSetState = 1;
            TERRAINset = 1;
            if (terrainTiles != 0)
                mem_Free(terrainTiles);
            terrainTiles = db_LoadObject(9, 9, 1);
            db_UnhookObject(9, 9);
        }
        Barrier = 0x90;
    } else if (id == 0x3e8) {
        if (terrainSetState != 0) {
            terrainSetState = 0;
            TERRAINset = 0;
            if (terrainTiles != 0)
                mem_Free(terrainTiles);
            terrainTiles = db_LoadObject(10, 9, 1);
            db_UnhookObject(10, 9);
        }
        Barrier = 0x50;
    }
}
