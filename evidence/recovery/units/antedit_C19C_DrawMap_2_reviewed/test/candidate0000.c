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


extern void far *mem_Lock(unsigned int handle);


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

/* Rebuild and render the mini-map image from the plane-specific cached map buffers. */
struct MiniMapRect { int left, top, right, bottom; };
extern struct MiniMapRect far miniMapRect;
extern unsigned int far multiplier;
extern unsigned int far miniJust;
extern unsigned int far mapOutBuf;
extern unsigned int far mapMapBuf;
extern unsigned int far miniXSize;
extern unsigned int far miniYSize;
extern int near mapMem;
extern int near MapPlane;
extern unsigned char near displayType;


extern void far *mem_Lock(unsigned int handle);



extern int far ConvColor(int color);
extern void far MSClipStart(int window);
extern void far MSClipEnd(void);
extern void far GBoxFill(int a, int b, int c, int d, int color);
extern void far Mini_MakeTable(void far *destination, void far *source, int row);
extern void near MiniMapRefreshLow(void);
extern void near MiniMapRefreshHigh(void);
extern void far DoFastBitmap(int x, int y, int width, int height, void far *source, int mode);
extern void far DoFastMonoBitmap(int x, int y, int width, int height, void far *source);
extern int near win_hwnd[];


extern void far win_GetObjRect();
extern unsigned int far mem_Alloc();
extern long far BitmapImageSize();
extern int far mem_Unlock();
extern int far mem_Free();
void far DrawMap(void);
void far Mini_DrawMapI(void);
#pragma alloc_text(RUN1_TEXT, DrawMap)
#pragma alloc_text(RUN2_TEXT, Mini_DrawMapI, DrawMapWorker)

void far drawmap_pool_stub_window(void);
void far drawmap_pool_stub_spider(void);
void far drawmap_pool_stub_foot(void);
void far drawmap_pool_stub_ant(void);
void far drawmap_pool_stub_mini(void);
#pragma alloc_text(POOLSTUB_TEXT, drawmap_pool_stub_window, drawmap_pool_stub_spider, drawmap_pool_stub_foot, drawmap_pool_stub_ant, drawmap_pool_stub_mini)
void far drawmap_pool_stub_window(void) { }
void far drawmap_pool_stub_spider(void) { }
void far drawmap_pool_stub_foot(void) { }
void far drawmap_pool_stub_ant(void) { }
void far drawmap_pool_stub_mini(void) { }

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

void far Mini_DrawMapI(void)
{
    struct MiniMapRect far *rect;
    int far *scale;
    int far *just;
    int far *ySize;
    unsigned int far *mapHandle;
    unsigned int far *outHandle;
    unsigned char far *mapImage;
    unsigned char far *temp;
    unsigned int tempHandle;
    unsigned long imageBytes;
    int rowBytes;
    int row;
    int screenY;

    rect = &miniMapRect;
    win_GetObjRect(0x1401, rect);
    scale = &multiplier;
    *scale = 0x80;
    just = &miniJust;
    *just = 0;
    if (mapMem == 0) {
        mapOutBuf = mem_Alloc(0x400L, 1, "Map window image");
        mapMapBuf = mem_Alloc(0x2000L, 1, "Generated map window");
    }
    if (MapPlane < 2)
        MiniMapRefreshLow();
    if (MapPlane > 1 && MapPlane < 4) {
        MiniMapRefreshHigh();
        *scale = 0x40;
        *just = miniXSize << 5;
    }
    if (MapPlane > 1 && MapPlane < 4) {
        MSClipStart(win_hwnd[20]);
        GBoxFill(rect->left, miniMapRect.right,
                 rect->left + *just, miniMapRect.bottom,
                 ConvColor(15));
        GBoxFill(miniMapRect.top - *just - 1, miniMapRect.right,
                 miniMapRect.top, miniMapRect.bottom, ConvColor(15));
        MSClipEnd();
    }
    mapHandle = &mapMapBuf;
    mapImage = (unsigned char far *)mem_Lock(*mapHandle);
    outHandle = &mapOutBuf;
    (void)mem_Lock(*outHandle);
    screenY = miniMapRect.top;
    ySize = &miniYSize;
    imageBytes = BitmapImageSize(miniXSize * *scale,
                                 *ySize * 64,
                                 (displayType & 1) ? 4 : 1) + 0x20L;
    tempHandle = mem_Alloc(imageBytes, 1, "tmp");
    temp = (unsigned char far *)mem_Lock(tempHandle);
    rowBytes = (((((displayType & 1) ? 4 : 1) * *ySize * *scale + 31) / 32) * 4);
    for (row = 0; row < 64; row++) {
        Mini_MakeTable(mapImage + row * *scale,
                       temp + (63 - row) * *ySize * rowBytes,
                       screenY);
        screenY += *ySize;
    }
    MSClipStart(win_hwnd[20]);
    if (!(displayType & 1))
        DoFastBitmap(*just, 0, miniXSize * *scale, miniYSize * 64,
                     temp, 0);
    else
        DoFastMonoBitmap(*just, 0, miniXSize * *scale, miniYSize * 64,
                         temp);
    MSClipEnd();
    mem_Unlock(tempHandle);
    mem_Free(tempHandle);
    mem_Unlock(*outHandle);
    mem_Unlock(*mapHandle);
    if (mapMem == 0) {
        mem_Free(*outHandle);
        mem_Free(*mapHandle);
    }
}

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
