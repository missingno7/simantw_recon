/*
 * YardArea(p): bucket an ant record's position into the colony-bar grid
 * (row 0-15 from p->py, col 0-11 from row*10+p->px), matching the same
 * 10px/28px, mapTileRect-relative arithmetic DrawColonyBars uses for its
 * 16x12 grid.  Out-of-range values do nothing.  In range: bring up the
 * yard window (UpdateWindow/MSClipStart on win_hwnd[25]), erase the
 * CurYardPnt inversion cursor if shown, record the bucket into YMapPnt,
 * optionally XferPatch() when p's flags byte (+7) has bit 0x20 or 0x40
 * set, then re-clip and redraw the cursor if it was not already shown.
 */
struct Rect {
    int left;
    int top;
    int right;
    int bottom;
};

struct Point {
    int x;
    int y;
};

struct AntRec {
    unsigned char pad[7];
    unsigned char flags;
    int px;
    int py;
};

extern struct Point near patchRgn;
extern struct Rect far mapTileRect;
extern struct Point far YMapPnt;
extern struct Point far CurYardPnt;
extern int near win_hwnd[];
extern int near yardPatchShown;

extern void far pascal UpdateWindow(int window);
extern void far MSClipStart(int window);
extern void far MSClipEnd(void);
extern void far InvertPatch(int x, int y);
extern void far XferPatch(void);

void far YardArea(struct AntRec far *p)
{
    int row;
    int col;

    row = (p->py - mapTileRect.top - patchRgn.y) / 10;
    col = (row * 10 + p->px - mapTileRect.left - patchRgn.x) / 28;

    if (col < 0)
        return;
    if (col >= 0xc)
        return;
    if (row < 0)
        return;
    if (row >= 0x10)
        return;

    UpdateWindow(win_hwnd[25]);
    MSClipStart(win_hwnd[25]);

    if (yardPatchShown != 0) {
        InvertPatch(CurYardPnt.x, CurYardPnt.y);
        yardPatchShown = 0;
    }
    MSClipEnd();

    YMapPnt.x = col;
    YMapPnt.y = row;

    if (p->flags & 0x60) {
        XferPatch();
    }

    MSClipStart(win_hwnd[25]);
    if (yardPatchShown == 0) {
        InvertPatch(CurYardPnt.x, CurYardPnt.y);
        yardPatchShown = 1;
    }
    MSClipEnd();
}
