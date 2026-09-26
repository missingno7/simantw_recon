/*
 * DrawMap: while the map window (0x100) is open, clip to it, recompute
 * mapCursorRect (an unresolved near-call target in this code group -- no
 * MAPSYM name is available; it is inferred purely from the values read
 * immediately after: the same far Rect at segment 9 that ToggleMapCursor
 * also derives from mapYsize/mapXsize/MapPnt/mapTileRect), then
 * invalidate its four 2px border strips (top, bottom, left, right) on
 * win_hwnd[1] via InvalidateRect (USER ordinal 125), UpdateWindow
 * (USER ordinal 124) it, redraw the population/health readouts
 * (DrawMapData) and release the clip.
 */
struct WinRect {
    int left;
    int top;
    int right;
    int bottom;
};

struct Rect {
    int left;
    int top;
    int right;
    int bottom;
};

extern int near win_hwnd[];
extern struct Rect far mapCursorRect;

extern int far win_IsWinOpen(int window);
extern void far clip_SetWin(int window);
extern void far clip_Off(void);
static void far DrawMapWorker(void);
extern void far pascal InvalidateRect(int window, struct WinRect far *rect, int erase);
extern void far pascal UpdateWindow(int window);
extern void far DrawMapData(void);

void far drawmap_pool_scaffold(void);
#pragma alloc_text(POOLSTUB_TEXT, drawmap_pool_scaffold)
void far drawmap_pool_scaffold(void) { }

void far DrawMap(void)
{
    struct WinRect rect;

    if (!win_IsWinOpen(0x100))
        return;
    clip_SetWin(0x100);
    DrawMapWorker();

    rect.left = mapCursorRect.left + 2;
    rect.top = mapCursorRect.top;
    rect.right = mapCursorRect.right - 2;
    rect.bottom = mapCursorRect.top + 2;
    InvalidateRect(win_hwnd[1], &rect, 0);

    rect.left = mapCursorRect.left + 2;
    rect.top = mapCursorRect.bottom - 2;
    rect.right = mapCursorRect.right - 2;
    rect.bottom = mapCursorRect.bottom;
    InvalidateRect(win_hwnd[1], &rect, 0);

    rect.top = mapCursorRect.top;
    rect.left = mapCursorRect.left;
    rect.right = mapCursorRect.left + 2;
    rect.bottom = mapCursorRect.bottom;
    InvalidateRect(win_hwnd[1], &rect, 0);

    rect.left = mapCursorRect.right - 2;
    rect.top = mapCursorRect.top;
    rect.right = mapCursorRect.right;
    rect.bottom = mapCursorRect.bottom;
    InvalidateRect(win_hwnd[1], &rect, 0);

    UpdateWindow(win_hwnd[1]);
    DrawMapData();
    clip_Off();
}


/* Static bitmap builder at ANTEDIT_MODULE:D7A0. The mode switch mirrors the
   nine words at D8B2: the named map modes select one of three same-object
   render helpers, while mode zero resets the map and modes two/three set the
   0x40 row pitch. The render loop reuses the old bitmap when it is unchanged. */
extern int near mapBuf;
extern int near newMapForce;
extern int near lastMapGenMode;
extern int near showTrails;
extern int near MapPlane;
extern int far mapXsize;
extern int far mapYsize;
extern int far mapTileRect;
extern int far _mapForce;
extern int far SpidX;
extern int far SpidY;
extern int far SpidDir;
extern char far Dx8[];
extern int far clip_Push(void);
extern int far clip_SubInclude(void far *, void far *);
extern int far MapToYard(void);
extern int far win_MapChanged(void);
extern int far BitmapImageSize(unsigned long width, unsigned long height, int planes);
extern int far mem_Alloc(int group, char far *name, int flags, unsigned long bytes);
extern void far *mem_Lock(unsigned int handle);
extern int far mem_Unlock(unsigned int handle);
extern int far mem_Free(unsigned int handle);
extern void far myServiceSong(void);
extern void far DrawMapSpider(int x, int y, int direction);
extern void far DrawMapFoot(void);
extern void far Punt(char far *message);
extern void near DrawMapModeOne(void);
extern void near DrawMapModeTwo(void);
extern void near DrawMapModeThree(void);
extern void near DrawMapTiles(char far *direction, int plane);
extern void near DrawMapRaster(unsigned long source, unsigned long destination,
                               int width, int height, int row);
static void far DrawMapWorker(void)
{
    unsigned char far *oldBits;
    unsigned char far *newBits;
    unsigned char far *tileBits;
    int width, height, row, column;
    int spiderX, spiderY;
    unsigned int generation;
    unsigned long bytes;

    if (lastMapGenMode == 0) {
        MapToYard();
        return;
    }
    width = (mapXsize << 7);
    height = (mapYsize << 6);
    bytes = (unsigned long)BitmapImageSize(width, height, 4) + 0x20UL;
    if (mapBuf == 0)
        mapBuf = mem_Alloc(0, "mapBuf", 1, bytes);
    oldBits = (unsigned char far *)mem_Lock(mapBuf);
    newMapForce = 0;
    generation = (unsigned int)lastMapGenMode;
    if (generation != (unsigned int)mapXsize) win_MapChanged();

    switch (generation) {
    case 0: Punt("Invalid map mode"); break;
    case 1: DrawMapModeOne(); break;
    case 2:
    case 3:
        DrawMapModeTwo();
        height = mapYsize << 5;
        break;
    case 4: DrawMapTiles(Dx8, 0x62d2); break;
    case 5: DrawMapTiles(Dx8, 0x6ad2); break;
    case 6: DrawMapTiles(Dx8, 0x72d2); break;
    case 7: DrawMapTiles(Dx8, 0x7ad2); break;
    case 8: DrawMapTiles(Dx8, 0x52d2); break;
    }

    if (showTrails && MapPlane == 1) {
        spiderX = SpidX >> 4;
        spiderY = SpidY >> 4;
    } else {
        spiderX = spiderY = 0x7fff;
    }
    clip_Push();
    clip_SubInclude(&mapCursorRect, &mapTileRect);
    newBits = oldBits;
    tileBits = (unsigned char far *)mem_Lock(mapBuf);
    if (newMapForce || _mapForce || generation != lastMapGenMode) {
        for (row = 0; row < height; ++row) {
            for (column = 0; column < width; ++column)
                DrawMapRaster((unsigned long)tileBits, (unsigned long)newBits,
                              width, height, row);
            myServiceSong();
        }
        DrawMapSpider(spiderX, spiderY, SpidDir);
        DrawMapFoot();
    }
    mem_Unlock(mapBuf);
    mem_Unlock(mapBuf);
    mem_Unlock(mapBuf);
    mem_Free(mapBuf);
}

