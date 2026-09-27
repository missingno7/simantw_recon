/*
 * DrawSpider: choose the spider animation frame, draw its masked bitmap and
 * body parts, invalidate the covered edit-window region, then schedule or add
 * a spider message balloon. The tile clip window is the 8 by 8 region prepared
 * by PreDrawSpider; its cells are reset in the edit buffer after invalidation.
 */
struct SpiderBitmap {
    unsigned short type;
    unsigned char flags;
    unsigned char reserved[5];
    int width;
    int height;
};
struct MapPoint { int x; int y; };
struct SpiderRect { int left; int top; int right; int bottom; };

extern unsigned char far * near theEditBufPtr;
extern int near tileWidth;
extern int near tileHeight;
extern int near editWidth;
extern int near editHeight;
extern int near MapPlane;
extern int near win_hwnd[];
extern unsigned char near displayType;
extern int near SpidX;
extern int near SpidY;
extern int near SpidDir;
extern int far SMode;
extern int far Scycle;
extern char far DBodX[];
extern char far DBodY[];
extern char far BodX[];
extern char far BodY[];
extern char far Dx8[];
extern char far Dy8[];
extern struct MapPoint far MapPnt;
extern int far spiderTileLeft;
extern int far spiderTileTop;
extern int far GamePaused;
extern int far OptionStates[];
extern long far SpidBalloonTicks;
extern int far WantSpiderBalloon;
extern int far SpidMsgOffset;
extern int far LastSMode;
extern int far CurBalloonCnt;
extern struct MapPoint far CurBalloonPnts[];
extern int far CurBalloonPlane[];
extern int far CurBalloonFlags[];
extern char far * far CurBalloonMsgs[];
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
extern void near DrawLegs(int x, int y, int direction, int cycle);
extern void near DrawPalps(int x, int y, int direction);
extern int far pascal InvalidateRect(int window, struct SpiderRect far *rect,
                                    int erase);
extern long far TickCount(void);
extern long far SRand64(void);
extern int far SRand2(void);
extern long far SRand32(void);

void far DrawSpider(void)
{
    unsigned int handle;
    struct SpiderBitmap far *bitmap;
    struct SpiderRect dirty;
    unsigned char far *editBuffer;
    unsigned int far *editWords;
    int bodyX;
    int bodyY;
    int x;
    int y;
    int i;
    int left;
    int right;
    int top;
    int bottom;
    int clipLeft;
    int clipRight;
    int clipBottom;
    int xPixel;
    int yPixel;
    long delay;

    if (SMode == 5) {
        bodyX = DBodX[Scycle];
        bodyY = DBodY[Scycle];
        handle = db_LoadObject(Scycle + 0x41a, 2, 1);
    } else {
        bodyX = BodX[SpidDir];
        bodyY = BodY[SpidDir];
        handle = db_LoadObject(SpidDir + 0x3e8, 2, 1);
    }

    bitmap = (struct SpiderBitmap far *)mem_Lock(handle);
    if (bitmap->type == 3) {
        editBuffer = theEditBufPtr;
        x = SpidX + bodyX - MapPnt.x * tileWidth;
        y = SpidY + bodyY - MapPnt.y * tileHeight;
        if (displayType & 1) {
            ConvertMaskBitmap2(editBuffer, bitmap, x, y,
                               bitmap->width, bitmap->height,
                               editWidth * tileWidth, editHeight * tileHeight,
                               MapPnt.x, MapPnt.y);
        } else if (bitmap->flags & 0x80) {
            CopyMaskBitmap2(editBuffer, bitmap, x, y,
                            bitmap->width, bitmap->height,
                            editWidth * tileWidth, editHeight * tileHeight,
                            MapPnt.x, MapPnt.y);
        } else {
            CopyMonoMaskBitmap(editBuffer, bitmap, x, y,
                               bitmap->width, bitmap->height,
                               editWidth * tileWidth, editHeight * tileHeight,
                               MapPnt.x, MapPnt.y);
        }

        DrawLegs(x, y, SpidDir, Scycle & 7);
        DrawPalps(x, y, SpidDir);

        /* Invalidate the pixel rectangle covered by the spider's tile window.
           The rectangle is clipped to the edit view, while the tile indices
           below are clipped separately for resetting the edit-buffer cells. */
        if (spiderTileLeft < 0)
            dirty.left = MapPnt.x;
        else
            dirty.left = spiderTileLeft * tileWidth + MapPnt.x;
        dirty.right = (spiderTileLeft + 7) * tileWidth + MapPnt.x;
        xPixel = MapPnt.x + editWidth * tileWidth - 1;
        if (dirty.right > xPixel)
            dirty.right = xPixel;

        if (spiderTileTop < 0)
            dirty.top = MapPnt.y;
        else
            dirty.top = spiderTileTop * tileHeight + MapPnt.y;
        dirty.bottom = (spiderTileTop + 7) * tileHeight + MapPnt.y;
        yPixel = MapPnt.y + editHeight * tileHeight - 1;
        if (dirty.bottom > yPixel)
            dirty.bottom = yPixel;
        InvalidateRect(win_hwnd[25], &dirty, 0);

        clipLeft = spiderTileLeft;
        if (clipLeft < 0)
            clipLeft = 0;
        clipRight = spiderTileLeft + 7;
        if (clipRight >= editWidth)
            clipRight = editWidth - 1;
        i = spiderTileTop;
        if (i < 0)
            i = 0;
        clipBottom = spiderTileTop + 7;
        if (clipBottom >= editHeight)
            clipBottom = editHeight - 1;

        if (clipLeft <= clipRight && i <= clipBottom) {
            editWords = (unsigned int far *)editBuffer;
            for (left = clipLeft; left <= clipRight; left++) {
                i = spiderTileTop;
                if (i < 0)
                    i = 0;
                for (; i <= clipBottom; i++)
                    editWords[i * editWidth + left] = 0xffff;
            }
        }
    }
    mem_Unlock(handle);
    db_ReleaseHandle(handle);

    /* The randomized timer creates an opportunity for a balloon. The choice
       of text advances only when SRand2 returns zero; all failed or invisible
       opportunities take the shorter retry path below. */
    if (OptionStates[5] != 0 && GamePaused == 0 &&
        TickCount() > SpidBalloonTicks) {
        delay = SRand64();
        SpidBalloonTicks = delay + TickCount() + 0xb4L;
        if (SRand2() == 0) {
            WantSpiderBalloon = 1;
            SpidMsgOffset++;
            if (SpidMsgOffset >= 5)
                SpidMsgOffset = 0;
        } else {
            WantSpiderBalloon = 0;
        }
    }

    if (SMode == LastSMode && SMode <= 4 && WantSpiderBalloon != 0) {
        y = SpidY + (Dy8[SpidDir + 8] << 3);
        x = SpidX + (Dx8[SpidDir] << 3);
        yPixel = y / tileHeight;
        xPixel = x / tileWidth;

        if (CurBalloonCnt < 6 && MapPlane == 1 &&
            xPixel >= MapPnt.x && xPixel < MapPnt.x + editWidth &&
            yPixel >= MapPnt.y + 3 && yPixel < MapPnt.y + editHeight) {
            CurBalloonPnts[CurBalloonCnt].x = x;
            CurBalloonPnts[CurBalloonCnt].y = y;
            CurBalloonPlane[CurBalloonCnt] = 1;
            CurBalloonFlags[CurBalloonCnt] = 10;
            CurBalloonMsgs[CurBalloonCnt] =
                SpiderMsgs[CurBalloonCnt * 5 + SpidMsgOffset];
            CurBalloonCnt++;
            return;
        }
    }

    delay = SRand32();
    SpidBalloonTicks = delay + TickCount() + 30L;
    WantSpiderBalloon = 0;
    LastSMode = SMode;
}
