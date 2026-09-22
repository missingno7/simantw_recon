/*
 * DrawMapSpider(x, y, frame): lock mapBuf, draw bitmap (0x44c+frame) into
 * it via DrawBitMapToBuffer at (x*4, y*4) scaled to mapXsize<<7/mapYsize<<6,
 * getting back its actual width/height; unlock, then invalidate the
 * corresponding screen rect (mapTileRect-relative) on win_hwnd[1].  Then,
 * exactly like DrawMapFoot's tail: while the cached far handle at PACK
 * segment8+0x72ca is non-zero, lock it, and for y2=y-2 in
 * [0, min(y2+5,y2)) stamp 0xff bytes at stride tileStride starting from
 * the locked pointer offset by y2*tileStride, switching DS to SS/ES when
 * y2<0x40 (a small-count/DGROUP shortcut) before the fill loop; unlock at
 * the end regardless.
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

extern unsigned int far mapBuf;
extern struct Rect far mapTileRect;
extern int far mapXsize;
extern int far mapYsize;
extern int near win_hwnd[];
extern int far mapPatchHandle;
extern int far tileStride;

extern void far *mem_Lock(unsigned int handle);
extern int far mem_Unlock(unsigned int handle);
extern void far DrawBitMapToBuffer(void far *buf, int x4, int y4, int height, int width, int bitmapID, int far *outH, int far *outW);
extern void far pascal InvalidateRect(int window, struct WinRect far *rect, int erase);

void far DrawMapSpider(int x0, int y0, int frame)
{
    void far *buf;
    int outW, outH;
    int y4;
    int x, y;
    struct WinRect rect;
    int far *pHandle;
    void far *p;
    int limit;
    char far *dst;

    x = x0;
    y = y0;
    buf = mem_Lock(mapBuf);

    x <<= 2;
    y4 = y << 2;
    DrawBitMapToBuffer(buf, x, y4, mapYsize << 6, mapXsize << 7, frame + 0x44c, &outH, &outW);

    mem_Unlock(mapBuf);

    rect.top = mapTileRect.top + y4;
    rect.left = x + mapTileRect.left;
    rect.right = rect.left + outW;
    rect.bottom = rect.top + outH;
    InvalidateRect(win_hwnd[1], &rect, 0);

    y -= 2;
    pHandle = &mapPatchHandle;
    if (*pHandle != 0) {
        p = mem_Lock(*pHandle);
        dst = (char far *)p + tileStride * y;
        limit = y + 5;
        if (limit > y && y < 0x40 && y >= 0) {
            for (; y < limit; y++) {
                *dst = (char)0xff;
                dst += tileStride;
            }
        }
        mem_Unlock(*pHandle);
    }
}
