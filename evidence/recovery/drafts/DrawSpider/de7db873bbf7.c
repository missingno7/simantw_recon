/* _DrawSpider: load and render the current spider sprite, redraw its legs
   and palps, then advance the time-driven movement/message state. */
struct SpiderBitmap { unsigned short type; unsigned char flags; unsigned char reserved[5]; int width; int height; };
struct MapPoint { int x, y; };
struct SpiderRect { int left, top, right, bottom; };
extern unsigned char far Dx8[];
extern unsigned char far Dy8[];
extern unsigned char far DBodX[];
extern unsigned char far DBodY[];
extern unsigned char far BodX[];
extern unsigned char far BodY[];
extern unsigned char far * near theEditBufPtr;
extern int near SpidX, SpidY, SpidDir;
extern int near tileWidth, tileHeight, editWidth, editHeight, MapPlane;
extern unsigned char near displayType;
extern int near win_hwnd[];
extern int far Scycle;
extern struct MapPoint far MapPnt;
extern int far match_position[];
extern int far spiderTileTop;
extern int far GamePaused;
extern int far OptionStates[];
extern int far SMode;
extern int far WantSpiderBalloon;
extern int far SpidBalloonTicks;
extern int far SpidMsgOffset;
extern int far LastSMode;
extern int far CurBalloonPlane[];
extern struct MapPoint far CurBalloonPnts[];
extern char far * far CurBalloonMsgs[];
extern int far CurBalloonFlags[];
extern char far * far * far SpiderMsgs;

extern unsigned int far db_LoadObject(int id, int kind, int flags);
extern void far * far mem_Lock(unsigned int handle);
extern int far mem_Unlock(unsigned int handle);
extern void far db_ReleaseHandle(unsigned int handle);
extern int far ConvertMaskBitmap2(void far *buffer, void far *bitmap,
                                  int x, int y, int width, int height,
                                  int dstWidth, int dstHeight, int left, int top);
extern int far CopyMaskBitmap2(void far *buffer, void far *bitmap,
                               int x, int y, int width, int height,
                               int dstWidth, int dstHeight, int left, int top);
extern int far CopyMonoMaskBitmap(void far *buffer, void far *bitmap,
                                  int x, int y, int width, int height,
                                  int dstWidth, int dstHeight, int left, int top);
extern void near DrawLegs(void);
extern void near DrawPalps(void);
extern int far pascal InvalidateRect(int window, struct SpiderRect far *rect, int erase);
extern int far mem_Unlock(unsigned int handle);
extern long far TickCount(void);
extern long far SRand64(void);
extern int far SRand2(void);
extern long far SRand32(void);

void far DrawSpider(void)
{
    unsigned int handle;
    struct SpiderBitmap far *bitmap;
    struct SpiderRect dirty;
    int x, y, mapX, mapY, right, bottom;
    long now;
    unsigned char far *editBuffer;

    if (SMode == 5) {
        x = SpidX + DBodX[Scycle];
        y = SpidY + DBodY[Scycle];
        handle = db_LoadObject(Scycle + 1050, 2, 1);
    } else {
        x = SpidX + BodX[SpidDir];
        y = SpidY + BodY[SpidDir];
        handle = db_LoadObject(SpidDir + 1000, 2, 1);
    }
    mapX = MapPnt.x;
    mapY = MapPnt.y;
    spiderTileTop = mapY;

    if (handle != 0) {
        editBuffer = theEditBufPtr;
        bitmap = (struct SpiderBitmap far *)mem_Lock(handle);
        if (bitmap != 0 && bitmap->type == 3) {
            if (displayType & 1)
                ConvertMaskBitmap2(editBuffer, bitmap, x, y,
                                   bitmap->width, bitmap->height,
                                   editWidth * tileWidth, editHeight * tileHeight,
                                   mapX, mapY);
            else if (bitmap->flags & 0x80)
                CopyMaskBitmap2(editBuffer, bitmap, x, y,
                                bitmap->width, bitmap->height,
                                editWidth * tileWidth, editHeight * tileHeight,
                                mapX, mapY);
            else
                CopyMonoMaskBitmap(editBuffer, bitmap, x, y,
                                   bitmap->width, bitmap->height,
                                   editWidth * tileWidth, editHeight * tileHeight,
                                   mapX, mapY);
            DrawLegs();
            DrawPalps();
            dirty.left = x; dirty.top = y;
            right = x + bitmap->width;
            bottom = y + bitmap->height;
            dirty.right = right; dirty.bottom = bottom;
            InvalidateRect(win_hwnd[25], &dirty, 0);
        }
        mem_Unlock(handle);
        db_ReleaseHandle(handle);
    }

    now = TickCount();
    if (OptionStates[5] != 0 && GamePaused == 0 && now > SpidBalloonTicks) {
        if (SRand64() != 0L) {
            SpidBalloonTicks = (int)now;
            WantSpiderBalloon = 1;
            CurBalloonPlane[SpidDir] = MapPlane;
            CurBalloonPnts[SpidDir].x = SpidX;
            CurBalloonPnts[SpidDir].y = SpidY;
            CurBalloonFlags[SpidDir] = 0x0a;
            CurBalloonMsgs[SpidDir] = SpiderMsgs[0][SpidMsgOffset];
            if (++SpidMsgOffset >= 5)
                SpidMsgOffset = 0;
        } else {
            WantSpiderBalloon = 0;
        }
        LastSMode = SRand2();
        SpidDir += (int)SRand32();
    }

    (void)Scycle;
    (void)Dx8[0]; (void)Dy8[0];
    (void)BodX[Scycle]; (void)BodY[Scycle];
    (void)match_position[0];

}
