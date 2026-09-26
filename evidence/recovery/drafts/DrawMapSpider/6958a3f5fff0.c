/* Preserve x and y as register copies through the map bitmap call. */
struct WinRect { int left, top, right, bottom; };
struct Rect { int left, top, right, bottom; };
extern unsigned int near mapBuf;
extern struct Rect far mapTileRect;
extern int far mapXsize, mapYsize, tileStride;
extern int near win_hwnd[]; extern int far mapPatchHandle;
extern void far *mem_Lock(unsigned int); extern int far mem_Unlock(unsigned int);
extern void far DrawBitMapToBuffer(void far *, int, int, int, int, int, int far *, int far *);
extern void far pascal InvalidateRect(int, struct WinRect far *, int);
void far DrawMapSpider(int x0, int y0, int frame) {
    register int x = x0, y = y0; void far *buf; struct WinRect rect; int outH, outW; int y4;
    buf = mem_Lock(mapBuf); y4 = y << 2; x <<= 2;
    DrawBitMapToBuffer(buf, x, y4, mapYsize << 6, mapXsize << 7, frame + 0x44c, &outH, &outW);
    mem_Unlock(mapBuf);
    rect.top = mapTileRect.top + y4; rect.left = mapTileRect.left + x;
    rect.right = rect.left + outW; rect.bottom = rect.top + outH;
    InvalidateRect(win_hwnd[1], &rect, 0);
    y -= 2;
    if (mapPatchHandle != 0) {
        void far *p = mem_Lock(mapPatchHandle); char far *dst = (char far *)p + tileStride * y; int end = y + 5;
        if (end > y) for (; y < end && y < 0x40; ++y, dst += tileStride) if (y >= 0) *dst = -1;
        mem_Unlock(mapPatchHandle);
    }
}