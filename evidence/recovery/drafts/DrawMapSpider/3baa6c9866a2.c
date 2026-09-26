/* Draw a spider bitmap to mapBuf, invalidate its rectangle, then stamp the patch tail. */
struct WinRect { int left, top, right, bottom; };
struct Rect { int left, top, right, bottom; };
extern unsigned int near mapBuf;
extern struct Rect far mapTileRect;
extern int far mapXsize, mapYsize, tileStride;
extern int near win_hwnd[];
extern int far mapPatchHandle;
extern void far *mem_Lock(unsigned int);
extern int far mem_Unlock(unsigned int);
extern void far DrawBitMapToBuffer(void far *, int, int, int, int, int, int far *, int far *);
extern void far pascal InvalidateRect(int, struct WinRect far *, int);
void far DrawMapSpider(int x, int y, int frame) {
    void far *buf; struct WinRect rect; int outH, outW; int y4; int limit;
    buf = mem_Lock(mapBuf);
    y4 = y * 4; x = x * 4;
    DrawBitMapToBuffer(buf, x, y4, mapYsize * 64, mapXsize * 128, frame + 0x44c, &outH, &outW);
    mem_Unlock(mapBuf);
    rect.top = mapTileRect.top + y4; rect.left = mapTileRect.left + x;
    rect.right = rect.left + outW; rect.bottom = rect.top + outH;
    InvalidateRect(win_hwnd[1], &rect, 0);
    y -= 2;
    if (mapPatchHandle) {
        void far *p = mem_Lock(mapPatchHandle);
        char far *dst = (char far *)p + tileStride * y;
        limit = y + 5;
        while (y < limit && y < 0x40) {
            if (y >= 0) *dst = (char)0xff;
            dst += tileStride; ++y;
        }
        mem_Unlock(mapPatchHandle);
    }
}