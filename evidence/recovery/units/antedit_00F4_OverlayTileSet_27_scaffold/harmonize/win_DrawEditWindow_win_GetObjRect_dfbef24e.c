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
extern int near updateRgn;

extern unsigned char near displayType;
extern int near editHeight;
extern int near tileHeight;
extern int near editWidth;
extern int near tileWidth;
extern struct MapPoint far editTileRect;
extern int far match_position[];

extern void far *mem_Lock(unsigned int handle);
extern int far mem_Unlock(unsigned int handle);
extern int far pascal RectInRegion(unsigned int region, struct WinRect far *rect);
extern void far DoFastBitmap(int x, int y, int width, int height, char far *bits, int flags);

extern void far DoFastMonoBitmap(int x, int y, int width, int height, char far *bits);

extern void far DrawEditGraphs(void);
extern void far win_GetObjRect(int object, struct ScentRect far *rect);

void far win_DrawEditWindow(int flags)
{
    struct WinRect rect;
    register char far *buf;
    struct MapPoint drawOrigin;

    if (!(flags & 2))
        return;

    if (editBuf != 0) {
        if (updateRgn != 0 &&
            RectInRegion(updateRgn, (struct WinRect far *)&editTileRect) == 0)
            goto skipBitmap;
        buf = mem_Lock(editBuf);
        drawOrigin.x = editTileRect.x;
        drawOrigin.y = editTileRect.y;
        if ((displayType & 1) == 0)
            DoFastBitmap(drawOrigin.x, drawOrigin.y, tileWidth * editWidth, tileHeight * editHeight, buf, 0);
        else
            DoFastMonoBitmap(drawOrigin.x, drawOrigin.y, tileWidth * editWidth, tileHeight * editHeight, buf);
        mem_Unlock(editBuf);
    }

skipBitmap:
    DrawEditGraphs();
    win_GetObjRect(7, &rect);
}
