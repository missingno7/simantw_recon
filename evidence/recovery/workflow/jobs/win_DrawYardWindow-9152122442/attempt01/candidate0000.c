/*
 * win_DrawYardWindow(flags): flags&1 redraws the map-overview bitmap,
 * flags&2 redraws the colony display.  Bit 1: erase the CurYardPnt
 * inversion cursor if shown, clear newMapForce, call AllocateMapBuffer();
 * if mapBufOK, lock mapBuf and pick an origin/bitmap set: YardMode 0/1 use
 * object 0x1903 and bitmap 0x1b58+YardMode; other modes use object 0x1914
 * and either the mono bitmap 0x1b5a or, for colour, bitmaps
 * 0x1b6c/0x1b6d/0x1b6e summed into one height (with a displayType==10
 * shortcut using only 0x1b6c).  The draw is clipped to
 * min(bitmapHeight, mapYsize<<6) by mapXsize<<7 and issued through
 * DoFastMonoBitmap or DoFastBitmap, then mapBuf is unlocked.  Bit 2:
 * for YardMode>1 clear ColonyUpdateFlag and draw via DrawSimColonies
 * (mode 2) or DrawColonyBars (other modes>1); copy newMapForce to
 * mapForce; redraw the inversion cursor if it was not already shown.
 */
struct WinRect {
    int left;
    int top;
    int right;
    int bottom;
};

struct BitmapSize {
    int width;
    int height;
};

struct Point {
    int x;
    int y;
};

static int near yardPatchShown = 0;

extern int near mapBufOK;
extern int far newMapForce;
extern unsigned int far mapBuf;
extern int far mapForce;
extern int far ColonyUpdateFlag;
extern struct Point far CurYardPnt;
extern int far mapYsize;
extern int far mapXsize;
extern int near YardMode;
extern unsigned char near displayType;

extern void far InvertPatch(int x, int y);
extern void far AllocateMapBuffer(void);
extern void far *mem_Lock(unsigned int handle);
extern int far mem_Unlock(unsigned int handle);
extern void far win_GetObjRect(int object, struct WinRect far *rect);
extern void far gr_BitMapSize(struct BitmapSize far *size, int bitmap);
extern void far DoFastBitmap(int a, int b, int width, int height, void far *buf, int mask);
extern void far DoFastMonoBitmap(int a, int b, int width, int height, void far *buf);
extern void far DrawSimColonies(int mode);
extern void far DrawColonyBars(int mode);

void far win_DrawYardWindow(int flags)
{
    struct WinRect rect;
    struct BitmapSize size;
    void far *buf;
    int ox, oy;
    int total;
    int width, height;

    if ((flags & 1) == 0)
        goto skipBitmap;

    if (yardPatchShown != 0) {
        InvertPatch(CurYardPnt.x, CurYardPnt.y);
        yardPatchShown = 0;
    }
    newMapForce = 0;
    AllocateMapBuffer();
    if (mapBufOK == 0)
        goto skipBitmap;

    buf = mem_Lock(mapBuf);

    if (YardMode != 0 && YardMode != 1) {
        win_GetObjRect(0x1914, &rect);
        ox = rect.left;
        if (displayType & 1) {
            oy = rect.top;
            gr_BitMapSize(&size, 0x1b5a);
            goto drawMono;
        }
        oy = rect.bottom + 1;
        if (displayType == 10) {
            gr_BitMapSize(&size, 0x1b6c);
            goto drawColor;
        }
        gr_BitMapSize(&size, 0x1b6c);
        total = size.height;
        gr_BitMapSize(&size, 0x1b6d);
        total += size.height;
        gr_BitMapSize(&size, 0x1b6e);
        total += size.height;
        size.height = total;
        goto drawColor;
    }

    win_GetObjRect(0x1903, &rect);
    ox = rect.left;
    oy = rect.top;
    gr_BitMapSize(&size, 0x1b58 + YardMode);
    if (displayType & 1)
        goto drawMono;

drawColor:
    height = mapYsize << 6;
    if (height > size.height)
        height = size.height;
    width = mapXsize << 7;
    DoFastBitmap(ox, oy, width, height, buf, 0);
    goto unlockBuf;

drawMono:
    height = mapYsize << 6;
    if (height > size.height)
        height = size.height;
    width = mapXsize << 7;
    DoFastMonoBitmap(ox, oy, width, height, buf);

unlockBuf:
    mem_Unlock(mapBuf);

skipBitmap:
    if (flags & 2) {
        if (YardMode > 1) {
            ColonyUpdateFlag = 0;
            if (YardMode == 2)
                DrawSimColonies(YardMode);
            else
                DrawColonyBars(YardMode);
        }
        mapForce = newMapForce;
        if (yardPatchShown == 0) {
            InvertPatch(CurYardPnt.x, CurYardPnt.y);
            yardPatchShown = 1;
        }
    }
}
