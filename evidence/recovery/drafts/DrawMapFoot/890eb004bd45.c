/*
 * DrawMapFoot: while FootHere is set, lock mapBuf and stamp the ant-foot
 * bitmap (0x4b0 + (BoyDir&3)) at (FootY*4, FootX*4) into it via
 * DrawBitMapToBuffer (same 8-arg shape DrawMapSpider uses), invalidate the
 * resulting mapTileRect-relative rect on win_hwnd[1].  While BoyHere is 3
 * or 4, do it again for the mow-cursor bitmap (0x4ba + (~BoyDir&1)) at
 * (MowY*4, MowX*4).  Unlock mapBuf, then run the same match_position[0]
 * (a handle) dashed-fill tail idiom used by DrawMapSpider (advancing by
 * "multiplier"), and finally set newMapForce.
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

extern unsigned int near mapBuf;
extern int far FootHere;
extern int far FootY;
extern int far FootX;
extern unsigned char far BoyDir;
extern int far MowY;
extern int far MowX;
extern int near BoyHere;
extern struct Rect far mapTileRect;
extern int far mapXsize;
extern int far mapYsize;
extern int near win_hwnd[];
extern unsigned int far lastMapMapBuf;
extern int far multiplier;
extern int far newMapForce;

extern void far *mem_Lock(unsigned int handle);
extern int far mem_Unlock(unsigned int handle);
extern void far DrawBitMapToBuffer(void far *buf, int x4, int y4, int height, int width, int bitmapID, int far *outH, int far *outW);
extern void far pascal InvalidateRect(int window, struct WinRect far *rect, int erase);

void far DrawMapFoot(void)
{
    void far *buf;
    int outW, outH;
    int x4, y4;
    struct WinRect rect;
    int far *pHandle;
    void far * volatile p;
    int limit;
    char far *dst;

    buf = mem_Lock(mapBuf);

    if (!FootHere)
        return;

    y4 = FootX << 2;
    x4 = FootY << 2;
    DrawBitMapToBuffer(buf, x4, y4, mapYsize << 6, mapXsize << 7,
                        (BoyDir & 3) + 0x4b0, &outH, &outW);

    rect.top = mapTileRect.top + y4;
    rect.left = mapTileRect.left + x4;
    rect.right = rect.left + outW;
    rect.bottom = rect.top + outH;
    InvalidateRect(win_hwnd[1], &rect, 0);

    if (BoyHere == 3 || BoyHere == 4) {
        y4 = MowX << 2;
        x4 = MowY << 2;
        DrawBitMapToBuffer(buf, x4, y4, mapYsize << 6, mapXsize << 7,
                            (~BoyDir & 1) + 0x4ba, &outH, &outW);

        rect.top = mapTileRect.top + y4;
        rect.left = mapTileRect.left + x4;
        rect.right = rect.left + outW;
        rect.bottom = rect.top + outH;
        InvalidateRect(win_hwnd[1], &rect, 0);
    }

    mem_Unlock(mapBuf);

    y4 = FootX;
    if (lastMapMapBuf != 0) {
        p = mem_Lock(lastMapMapBuf);
        dst = (char far *)p + multiplier * y4;
        limit = y4 + 8;
        if (limit > y4 && y4 < 0x40 && y4 >= 0) {
            for (; y4 < limit; y4++) {
                *dst = (char)0xff;
                dst += multiplier;
            }
        }
        mem_Unlock(lastMapMapBuf);
    }

    newMapForce = 1;
}
