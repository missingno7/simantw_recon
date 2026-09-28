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
void far DrawMapWorker(void);
extern void far pascal InvalidateRect(int window, struct WinRect far *rect, int erase);
extern void far pascal UpdateWindow(int window);
extern void far DrawMapData(void);

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
extern unsigned int near mapBuf;
extern unsigned char near displayType;
extern int far MapMode;
extern int near newMapForce;
extern int near lastMapGenMode;
extern int near showTrails;
extern int far just;
extern int far multiplier;
extern unsigned int far mapOutBuf;
extern unsigned int far mapMapBuf;
extern unsigned int far lastMapMapBuf;
extern int near MapPlane;
extern int far mapXsize;
extern int far mapYsize;
extern struct Rect far mapTileRect;

extern int far _mapForce;
extern int far multiplier;
extern int near SpidX;

extern int near SpidY;

extern int far SpidDir;
extern char far Dx8[];
extern void far clip_Push(void);

extern int far clip_SubInclude(void far *, void far *);
extern void far MapToYard(void);

extern void win_MapChanged(void);

extern long far BitmapImageSize(int width, int height, int planes);
extern unsigned int far mem_Alloc(unsigned long bytes, int kind, char far *name);
extern void far *mem_Lock(unsigned int handle);
extern int far mem_Unlock(unsigned int handle);
extern void far mem_Free(int handle);

extern void myServiceSong(void);

extern void far DrawMapSpider(int x, int y, int direction);
extern void far DrawMapFoot(void);
extern void far Punt(char far *message);
extern void near MiniMapHelperA(void);
extern void near MiniMapHelperB(void);
extern void near MapCommonHelper(unsigned char far *source);
extern int far _fmemcmp(const void far *, const void far *, unsigned int);
extern void far *_fmemcpy(void far *, const void far *, unsigned int);
void far DrawMapWorker(void)
{
    unsigned char far *oldBits;
    unsigned char far *newBits;
    unsigned char far *tileBits;
    int width, height, row, column;
    int spiderX, spiderY;
    unsigned int generation;
    long bytes;

    if (MapMode == 0) {
        MapToYard();
        return;
    }
    if (!mapBuf) {
        int planes;
        planes = (displayType & 1) ? 1 : 4;
        bytes = BitmapImageSize(mapXsize << 7, mapYsize << 6, planes);
        mapBuf = mem_Alloc(bytes + 0x20L, 1, "mapbuf");
    }
    oldBits = (unsigned char far *)mem_Lock(mapBuf);
    multiplier = 0x80;
    newMapForce = 0;
    just = 0;
    mapOutBuf = mem_Alloc(0x400L, 1, "mapOutBuf");
    mapMapBuf = mem_Alloc(0x2000L, 1, "mapMapBuf");
    generation = (unsigned int)MapMode;
    if (generation != (unsigned int)lastMapGenMode) win_MapChanged();

    switch (generation) {
    case 0: Punt("Invalid map mode"); break;
    case 1: MiniMapHelperA(); break;
    case 2:
    case 3:
        MiniMapHelperB();
        multiplier = 0x40;
        height = mapYsize << 5;
        break;
    case 4: MapCommonHelper((unsigned char far *)Dx8 + 0x62d2); break;
    case 5: MapCommonHelper((unsigned char far *)Dx8 + 0x6ad2); break;
    case 6: MapCommonHelper((unsigned char far *)Dx8 + 0x72d2); break;
    case 7: MapCommonHelper((unsigned char far *)Dx8 + 0x7ad2); break;
    case 8: MapCommonHelper((unsigned char far *)Dx8 + 0x52d2); break;
    }

    width = mapXsize << 7;
    height = mapYsize << 6;
    if (showTrails && MapPlane == 1) {
        spiderX = SpidX >> 4;
        spiderY = SpidY >> 4;
    } else {
        spiderX = spiderY = 0x7fff;
    }
    clip_Push();
    clip_SubInclude(&mapCursorRect, &mapTileRect);
    newBits = (unsigned char far *)mem_Lock(mapMapBuf);
    tileBits = (unsigned char far *)mem_Lock(mapOutBuf);
    if (newMapForce || _mapForce || generation != lastMapGenMode) {
        for (row = 0; row < height; ++row) {
            /* Bounded completion: the target compares and copies each row here.
               The remaining renderer logic is still unresolved. */
            if (_fmemcmp(oldBits, newBits, (unsigned int)mapXsize) != 0 || _mapForce)
                _fmemcpy(oldBits, newBits, (unsigned int)mapXsize);
            oldBits += mapXsize;
            newBits += mapXsize;
            myServiceSong();
        }
        DrawMapSpider(spiderX, spiderY, SpidDir);
        DrawMapFoot();
    }
    mem_Unlock(mapBuf);
    mem_Unlock(mapOutBuf);
    mem_Unlock(mapMapBuf);
    mem_Free(mapOutBuf);
    mem_Free(mapMapBuf);
}

