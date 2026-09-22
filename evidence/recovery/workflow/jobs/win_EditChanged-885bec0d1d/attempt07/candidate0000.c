/* win_EditChanged: recompute the edit window's tile geometry and
 * reallocate its per-tile draw buffers after the edit window object (4)
 * is resized or reopened. win_GetObjRect fills editTileRect from object 4;
 * editHeight/editWidth are the tile counts needed to cover it (rounded up
 * to a whole tile), and editTileRect.right/bottom are grown back out to
 * the resulting whole-tile pixel size. Two private based buffer handles
 * (tileDspHandle/tileMaskHandle, evidenced only by selector 0xbf8a into
 * SIMANT_DATA_GROUP at the unnamed words just before the public
 * editBufInvalidFlag[] -- assets/SIMANTW.SYM segment 8: ..._colorValue
 * (0x8ca6) ... _editBufInvalidFlag (0x8df6), a private gap) are freed if
 * already allocated, then both are reallocated to the new tile count
 * (tileMaskHandle at twice the byte count) and locked into the near far
 * pointers tileDsp (0x143e/0x1440, MAPSYM-confirmed) and tileMask
 * (0x1442/0x1444, same unnamed-gap pattern as the handles). tileMask is
 * filled with 0xFF (rep stosb over the doubled byte count) and
 * editBufInvalidFlag[0] is cleared. Finally MapPnt is clamped inside the
 * new tile rectangle (X against 0x80 for MapMode 0/1, 0x40 for MapMode
 * >=2, matching ResetEditScrollRange's own 0x80/0x40 split; Y always
 * against 0x40) and ResetEditScrollRange is called. */
struct ScentRect { int left, top, right, bottom; };
extern void far win_GetObjRect(int object, struct ScentRect far *rect);

extern struct ScentRect far editTileRect;
extern int near tileWidth;
extern int near tileHeight;
extern int near editHeight;
extern int near editWidth;

static unsigned int __based(__segname("SIMANT_DATA_GROUP")) tileDspHandle;
static unsigned int __based(__segname("SIMANT_DATA_GROUP")) tileMaskHandle;
extern int far editBufInvalidFlag[];

extern unsigned int far mem_Alloc(unsigned long bytes, int kind, char far *name);
extern void far *mem_Lock(unsigned int handle);
extern int far mem_Unlock(unsigned int handle);
extern void far mem_Free(int handle);

extern char far *tileDsp;
extern char far *tileMask;

extern int near MapPlane;
struct MapPoint { int x, y; };
extern struct MapPoint far MapPnt;
extern void far ResetEditScrollRange(void);

void far win_EditChanged(void)
{
    long bytes;
    int limit;
    int h, w;

    win_GetObjRect(4, &editTileRect);

    h = (editTileRect.bottom - editTileRect.top + tileHeight - 1) / tileHeight;
    editHeight = h;
    w = (editTileRect.right - editTileRect.left + tileWidth - 1) / tileWidth;
    editWidth = w;
    editTileRect.right = editTileRect.left + w * tileWidth;
    editTileRect.bottom = editTileRect.top + h * tileHeight;

    if (tileDspHandle) {
        mem_Unlock(tileDspHandle);
        mem_Free(tileDspHandle);
    }
    tileDspHandle = 0;

    if (tileMaskHandle) {
        mem_Unlock(tileMaskHandle);
        mem_Free(tileMaskHandle);
    }
    tileMaskHandle = 0;

    bytes = (long)editHeight * editWidth;
    tileDspHandle = mem_Alloc(bytes, 1, "tiledsp");
    tileDsp = mem_Lock(tileDspHandle);

    bytes = (long)editHeight * editWidth * 2;
    tileMaskHandle = mem_Alloc(bytes, 1, "tilemask");
    tileMask = mem_Lock(tileMaskHandle);

    {
        unsigned int count;
        char far *m;

        m = tileMask;
        for (count = editHeight * editWidth * 2; count != 0; count--)
            *m++ = 0xff;
    }

    editBufInvalidFlag[0] = 0;

    limit = (MapPlane < 0 || MapPlane > 1) ? 0x40 : 0x80;

    if (MapPnt.x < 0)
        MapPnt.x = 0;
    else if (MapPnt.x + editWidth > limit)
        MapPnt.x = limit - editWidth;

    if (MapPnt.y < 0)
        MapPnt.y = 0;
    else if (MapPnt.y + editHeight > 0x40)
        MapPnt.y = 0x40 - editHeight;

    ResetEditScrollRange();
}
