/*
 * win_DrawEditWindow: redraw the ant-editor edit window when its dirty
 * flag bit is set.  If the edit buffer handle is set, and either there
 * is no update region or the update region overlaps the match-position
 * rectangle, the edit buffer is locked and blitted (mono or color,
 * chosen by displayType) at the editTileRect origin, scaled by
 * tileWidth/tileHeight * editWidth/editHeight, then unlocked.  The
 * edit graphs are always redrawn and the edit window's rect refreshed
 * via win_GetObjRect(7, ...) whenever the dirty bit was set at all.
 */
struct WinRect {
    int left;
    int top;
    int right;
    int bottom;
};

struct MapPoint {
    int x;
    int y;
};

extern unsigned int near editBuf;
extern unsigned int near updateRgn;
extern unsigned char near displayType;
extern int near tileWidth;
extern int near tileHeight;
extern int near editWidth;
extern int near editHeight;
extern struct MapPoint far editTileRect;
extern int far match_position[];

extern void far *mem_Lock(unsigned int handle);
extern int far mem_Unlock(unsigned int handle);
extern int far pascal RectInRegion(unsigned int region, struct WinRect far *rect);
extern void far DoFastBitmap(int color, void far *buf, int h, int w, int y, int x);
extern void far DoFastMonoBitmap(void far *buf, int h, int w, int y, int x);
extern void far DrawEditGraphs(void);
extern void far win_GetObjRect(int object, struct WinRect far *rect);

void far win_DrawEditWindow(int flags)
{
    struct WinRect rect;
    int px, py;
    void far *buf;
    unsigned int eb;

    if (!(flags & 2))
        return;

    eb = editBuf;
    if (eb != 0) {
        if (updateRgn == 0 ||
            RectInRegion(updateRgn, (struct WinRect far *)match_position)) {
            buf = mem_Lock(eb);
            px = editTileRect.x;
            py = editTileRect.y;
            if ((displayType & 1) == 0)
                DoFastBitmap(0, buf, tileHeight * editHeight, tileWidth * editWidth, py, px);
            else
                DoFastMonoBitmap(buf, tileHeight * editHeight, tileWidth * editWidth, py, px);
            mem_Unlock(eb);
        }
    }

    DrawEditGraphs();
    win_GetObjRect(7, &rect);
}
