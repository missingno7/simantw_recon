struct WinRect {
    int left;
    int top;
    int right;
    int bottom;
};
/* Rebuild and render the mini-map image from the plane-specific cached map buffers. */
struct MiniMapRect { int left, top, right, bottom; };
extern struct MiniMapRect far miniMapRect;
extern int far multiplier;

extern int far miniJust;

extern unsigned int far mapOutBuf;
extern unsigned int far mapMapBuf;
extern int far miniXSize;

extern int far miniYSize;

extern int near mapMem;
extern int near MapPlane;
extern unsigned char near displayType;
extern void far win_GetObjRect(int object, struct WinRect far *rect);

extern unsigned int far mem_Alloc(unsigned long bytes, int kind, char far *name);
extern void far *mem_Lock(unsigned int handle);
extern int far mem_Unlock(unsigned int handle);
extern void far mem_Free(unsigned int handle);
extern long far BitmapImageSize(int width, int height, int depth);
extern int far ConvColor(int color);
extern void far MSClipStart(int window);
extern void far MSClipEnd(void);
extern void far GBoxFill(int a, int b, int c, int d, int color);
extern void far Mini_MakeTable(void far *destination, void far *source, int row);
extern void near MiniMapRefreshLow(void);
extern void near MiniMapRefreshHigh(void);
extern void far DoFastBitmap(int x, int y, int width, int height, char far *bits, int flags);

extern void far DoFastMonoBitmap(int x, int y, int width, int height, void far *source);
extern int near win_hwnd[];

void far Mini_DrawMapI(void)
{
    struct { struct MiniMapRect far *rect; int far *scale; int far *just; } ptrs;
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

    ptrs.rect = &miniMapRect;
    win_GetObjRect(0x1401, ptrs.rect);
    ptrs.scale = &multiplier;
    *ptrs.scale = 0x80;
    ptrs.just = &miniJust;
    *ptrs.just = 0;
    if (mapMem == 0) {
        mapOutBuf = mem_Alloc(0x400L, 1, "Map window image");
        mapMapBuf = mem_Alloc(0x2000L, 1, "Generated map window");
    }
    if (MapPlane < 2)
        MiniMapRefreshLow();
    if (MapPlane > 1 && MapPlane < 4) {
        MiniMapRefreshHigh();
        *ptrs.scale = 0x40;
        *ptrs.just = miniXSize << 5;
    }
    if (MapPlane > 1 && MapPlane < 4) {
        MSClipStart(win_hwnd[20]);
        GBoxFill(ptrs.rect->left, miniMapRect.right,
                 ptrs.rect->left + *ptrs.just, miniMapRect.bottom,
                 ConvColor(15));
        GBoxFill(miniMapRect.top - *ptrs.just - 1, miniMapRect.right,
                 miniMapRect.top, miniMapRect.bottom, ConvColor(15));
        MSClipEnd();
    }
    mapHandle = &mapMapBuf;
    mapImage = (unsigned char far *)mem_Lock(*mapHandle);
    outHandle = &mapOutBuf;
    (void)mem_Lock(*outHandle);
    screenY = miniMapRect.top;
    ySize = &miniYSize;
    imageBytes = BitmapImageSize(miniXSize * *ptrs.scale,
                                 *ySize * 64,
                                 (displayType & 1) ? 4 : 1) + 0x20L;
    tempHandle = mem_Alloc(imageBytes, 1, "tmp");
    temp = (unsigned char far *)mem_Lock(tempHandle);
    rowBytes = (((((displayType & 1) ? 4 : 1) * *ySize * *ptrs.scale + 31) / 32) * 4);
    for (row = 0; row < 64; row++) {
        Mini_MakeTable(mapImage + row * *ptrs.scale,
                       temp + (63 - row) * *ySize * rowBytes,
                       screenY);
        screenY += *ySize;
    }
    MSClipStart(win_hwnd[20]);
    if (!(displayType & 1))
        DoFastBitmap(*ptrs.just, 0, miniXSize * *ptrs.scale, miniYSize * 64,
                     temp, 0);
    else
        DoFastMonoBitmap(*ptrs.just, 0, miniXSize * *ptrs.scale, miniYSize * 64,
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