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
extern void far win_GetObjRect(int object, struct MiniMapRect far *rect);
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
extern void far DoFastBitmap(int x, int y, int width, int height, void far *source, int mode);
extern void far DoFastMonoBitmap(int x, int y, int width, int height, void far *source);
extern int near win_hwnd[];

void far Mini_DrawMapI(void)
{
    struct MiniMapRect far *rect;
    int far *scale;
    int far *just;
    int far *ySize;
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
    mapImage = (unsigned char far *)mem_Lock(mapMapBuf);
    (void)mem_Lock(mapOutBuf);
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
    mem_Unlock(mapOutBuf);
    mem_Unlock(mapMapBuf);
    if (mapMem == 0) {
        mem_Free(mapOutBuf);
        mem_Free(mapMapBuf);
    }
}