/*
 * Hypothesis from the closed 712-byte target: only draw on the redraw flag
 * (bit 1); if far word at Dx8 offset 0x8610 is zero, restore the yard and
 * return. Otherwise erase a shown map cursor, redraw the map bitmap when its
 * buffer and update region permit it, then draw a hidden cursor. In modes 2
 * and 3, clear the left and right border strips and use a half-width bitmap.
 * Named fields and selectors follow the factory packet's MAPSYM/NE bindings;
 * no absolute address is embedded in this source.
 */
struct MapRect {
    int left;
    int top;
    int right;
    int bottom;
};

struct MapPoint {
    int x;
    int y;
};

extern char far Dx8[];
extern struct MapRect far mapTileRect;
extern struct MapRect far mapCursorRect;
extern struct MapPoint far MapPnt;
extern int far mapXsize;
extern int far mapYsize;
extern int far just;
extern int near mapCursorState;
extern unsigned int near mapBuf;
extern int near updateRgn;
extern unsigned char near displayType;
extern int near editWidth;
extern int near editHeight;

extern void far MapToYard(void);
extern void far clip_SetWin(int window);
extern void far clip_Push(void);
extern void far clip_Pop(void);
extern int far win_IsWinOpen(int window);
extern void far GRectInvOutline(struct MapRect far *rect, int color);
extern int far pascal RectInRegion(int region, struct MapRect far *rect);
extern void far *mem_Lock(unsigned int handle);
extern int far mem_Unlock(unsigned int handle);
extern int far ConvColor(int color);
extern void far GBoxFill(int left, int top, int right, int bottom, int color);
extern void far DoFastBitmap(int x, int y, int width, int height,
                             void far *bits, int mode);
extern void far DoFastMonoBitmap(int x, int y, int width, int height,
                                 void far *bits);

void far win_DrawMapWindow(int flags)
{
    int mapWidth;
    void far *bits;

    if (!(flags & 2))
        return;

    if (*(int far *)(Dx8 + 0x8610) == 0) {
        MapToYard();
        return;
    }

    clip_SetWin(0x100);
    if (win_IsWinOpen(0x100) && mapCursorState == 1) {
        clip_Push();
        clip_SetWin(0x100);
        GRectInvOutline(&mapCursorRect, 2);
        mapCursorState = 0;
        clip_Pop();
    }

    if (mapBuf != 0 &&
        (updateRgn == 0 || RectInRegion(updateRgn, &mapTileRect))) {
        bits = mem_Lock(mapBuf);

        if (*(int far *)(Dx8 + 0x8610) == 2 || *(int far *)(Dx8 + 0x8610) == 3) {
            GBoxFill(mapTileRect.left, mapTileRect.top,
                     mapTileRect.left + (mapXsize << 5) - 1,
                     mapTileRect.bottom, ConvColor(15));
            GBoxFill(mapTileRect.right - (mapXsize << 5),
                     mapTileRect.top, mapTileRect.right,
                     mapTileRect.bottom, ConvColor(15));
            mapWidth = mapXsize << 6;
        } else {
            mapWidth = mapXsize << 7;
        }

        if (displayType & 1)
            DoFastMonoBitmap(mapTileRect.left, mapTileRect.top, mapWidth, mapYsize << 6, bits);
        else
            DoFastBitmap(mapTileRect.left, mapTileRect.top, mapWidth, mapYsize << 6, bits, 0);

        mem_Unlock(mapBuf);
    }

    if (!win_IsWinOpen(0x100) || mapCursorState != 0)
        return;

    clip_Push();
    clip_SetWin(0x100);
    mapCursorRect.top = mapYsize * MapPnt.y + mapTileRect.top;
    mapCursorRect.bottom = mapCursorRect.top + mapYsize * editHeight;
    mapCursorRect.left = mapXsize * MapPnt.x + mapTileRect.left + just;
    mapCursorRect.right = mapCursorRect.left + mapXsize * editWidth;
    GRectInvOutline(&mapCursorRect, 2);
    mapCursorState = 1;
    clip_Pop();
}
