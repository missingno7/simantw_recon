/*
 * Keep the edit viewport's cached map position current.  When the cached and
 * live views overlap on the same map and terrain, scroll the existing pixels
 * and edit arrays; otherwise let the normal invalidation path redraw them.
 */
struct MapPoint {
    int x;
    int y;
};

extern int near win_hwnd[];
extern int near scrollBarFlag;
extern int far editBufInvalidFlag;
extern int near editForce;
extern int near editWidth;
extern int near editHeight;
extern int near tileWidth;
extern int near tileHeight;
extern int near MapPlane;
extern int far TERRAINset;
extern struct MapPoint far editTileRect;
extern struct MapPoint far MapPnt;

extern int far win_IsWinOpen(int window);
extern int far win_IsWinInFront(int window);
extern int far win_IsWinExposed(int window);
/* Same-module far calls use LINK 5.30 NOP/PUSH CS/CALL lowering. */
extern void far ScrollEditArrays(int dx, int dy);
extern void far UpdateEditIfBufInvalid(void);
extern void far ResetEditScrollRange(int window);
extern void far DrawEditGraphs(void);
extern void far MSClipStart(int window);
extern void far MSClipEnd(void);

extern unsigned int far pascal CreateRectRgn(int left, int top, int right, int bottom);
extern void far pascal ScrollWindow(unsigned int window, int dx, int dy, struct Rect far *rect, struct Rect far *clip);
extern int far pascal GetUpdateRgn(unsigned int window, unsigned int region, int erase);
extern void far pascal ValidateRgn(unsigned int window, unsigned int region);
extern void far pascal UpdateWindow(unsigned int window);
extern void far pascal InvalidateRgn(unsigned int window, unsigned int region, int erase);
extern int far pascal DeleteObject(unsigned int object);

static int lastMapX = -1;
static int lastMapY = -1;
static int lastMapPlane = -1;
static int lastTerrain = -1;
static void near DrawEditBuffers(void);


extern int far editBufInvalidFlag;
extern int near win_hwnd[2];
extern int near editForce;

extern int far pascal CreateRectRgn(int left, int top, int right, int bottom);
extern int far pascal GetUpdateRgn(int window, int region, int erase);
extern int far pascal ValidateRgn(int window, int region);
extern int far pascal UpdateWindow(int window);
extern int far pascal DeleteObject(int object);
static void near DrawEditBuffers(void);


/* DoEditScrollLine: scroll the edit tile buffer one line in direction c
 * ('u'/'d'/'l'/'r'), then refresh the display. For color displays
 * (!(displayType&1)) the edit buffer is locked, the matching
 * EditScroll{Up,Down,Left,Right}Color helper does the shift (passed the
 * locked buffer, tileDsp, tileMask and the tile/edit geometry -- same
 * far-pointer arguments as win_EditChanged/ClearEditDeltaTables build),
 * the buffer is unlocked, the edit window redrawn (UpdateEdit,
 * InvalidateRect, UpdateWindow); for the monochrome-class path the color
 * scroll is skipped and UpdateEdit is called directly. Finally, if the
 * map window (object 0x100) is open, the map cursor is erased and
 * redrawn inside an MSClipStart/MSClipEnd pair on the yard window
 * (win_hwnd[1]), matching CenterAnt's identical clip/cursor shape. */
extern unsigned char near displayType;
extern int near editBuf;
extern void far *mem_Lock(unsigned int handle);
extern int far mem_Unlock(unsigned int handle);

extern int near tileWidth;
extern int near tileHeight;
extern int near editWidth;
extern int near editHeight;
extern char far * near tileDsp;
extern char far * near tileMask;

extern void far EditScrollUpColor(char far *buf, char far *dsp, char far *mask,
                                   int editHeight, int editWidth, int tileHeight, int tileWidth);
extern void far EditScrollDownColor(char far *buf, char far *dsp, char far *mask,
                                     int editHeight, int editWidth, int tileHeight, int tileWidth);
extern void far EditScrollLeftColor(char far *buf, char far *dsp, char far *mask,
                                     int editHeight, int editWidth, int tileHeight, int tileWidth);
extern void far EditScrollRightColor(char far *buf, char far *dsp, char far *mask,
                                      int editHeight, int editWidth, int tileHeight, int tileWidth);

extern void far UpdateEdit(void);
extern int near win_hwnd[];
extern void far pascal InvalidateRect(int window, void far *rect, unsigned flags);
extern void far pascal UpdateWindow(int window);

extern int far win_IsWinOpen(int window);
extern void far MSClipStart(int window);
extern void far MSClipEnd(void);
extern void far EraseMapCursor(void);
extern void far DrawMapCursor(void);


void far UpdateEdit(void)
{
    struct Rect rect;
    unsigned int region;
    int dx;
    int dy;
    volatile int currentTerrain;
    int oldX;
    int oldY;

    if (!win_IsWinOpen(0))
        return;

    if (scrollBarFlag) {
        oldX = lastMapX;
        oldY = lastMapY;
        region = CreateRectRgn(0, 0, 1, 1);
        rect.left = editTileRect.x;
        rect.top = editTileRect.y;
        rect.right = rect.left + tileWidth * editWidth;
        rect.bottom = rect.top + tileHeight * editHeight;
        dx = tileWidth * (oldX - MapPnt.x);
        dy = tileHeight * (oldY - MapPnt.y);
        ScrollWindow(win_hwnd[0], dx, dy, &rect, &rect);
        GetUpdateRgn(win_hwnd[0], region, 0);
        ValidateRgn(win_hwnd[0], region);
        UpdateWindow(win_hwnd[0]);
        InvalidateRgn(win_hwnd[0], region, 0);
        DeleteObject(region);
    } else {
        if (lastMapX == -1)
            goto update_cache;
        if (lastMapY == -1)
            goto update_cache;
        if (lastMapX != MapPnt.x)
            goto check_x_left;
        if (lastMapY != MapPnt.y)
            goto check_x_left;
        goto update_cache;

check_x_left:
        if (MapPnt.x - editWidth < lastMapX)
            goto check_x_right;
        goto update_cache;

check_x_right:
        if (MapPnt.x + editWidth > lastMapX)
            goto check_y_top;
        goto update_cache;

check_y_top:
        if (MapPnt.y - editHeight < lastMapY)
            goto check_y_bottom;
        goto update_cache;

check_y_bottom:
        if (MapPnt.y + editHeight > lastMapY)
            goto check_plane;
        goto update_cache;

check_plane:
        if (MapPlane == lastMapPlane)
            goto check_terrain;
        goto update_cache;

check_terrain:
        if (TERRAINset == lastTerrain)
            goto check_front;
        goto update_cache;

check_front:
        if (win_IsWinInFront(0))
            goto check_exposed;
        goto update_cache;

check_exposed:
        if (win_IsWinExposed(0)) {
            oldX = lastMapX;
            oldY = lastMapY;
            region = CreateRectRgn(0, 0, 1, 1);
            rect.left = editTileRect.x;
            rect.top = editTileRect.y;
            rect.right = rect.left + tileWidth * editWidth;
            rect.bottom = rect.top + tileHeight * editHeight;
            dx = tileWidth * (oldX - MapPnt.x);
            dy = tileHeight * (oldY - MapPnt.y);
            ScrollWindow(win_hwnd[0], dx, dy, &rect, &rect);
            GetUpdateRgn(win_hwnd[0], region, 0);
            ValidateRgn(win_hwnd[0], region);
            UpdateWindow(win_hwnd[0]);
            InvalidateRgn(win_hwnd[0], region, 0);
            DeleteObject(region);
            /* Segment-8 invalidation word at SIMANT_DATA_GROUP 0x8df6. */
            editBufInvalidFlag = 1;
            ScrollEditArrays(lastMapX - MapPnt.x, lastMapY - MapPnt.y);
        }
    }

update_cache:
    currentTerrain = TERRAINset;
    if (currentTerrain != lastTerrain)
        editForce = 1;
    lastMapX = MapPnt.x;
    lastMapY = MapPnt.y;
    lastMapPlane = MapPlane;
    lastTerrain = currentTerrain;
    UpdateEditIfBufInvalid();
    editForce = 0;
    ResetEditScrollRange(win_hwnd[0]);
    MSClipStart(win_hwnd[0]);
    DrawEditGraphs();
    DrawEditBuffers();
    MSClipEnd();
}
void far UpdateEditIfBufInvalid(void)
{
    int region;

    if (!editBufInvalidFlag)
        return;

    region = CreateRectRgn(0, 0, 10, 10);
    GetUpdateRgn(win_hwnd[0], region, 0);
    ValidateRgn(win_hwnd[0], region);
    UpdateWindow(win_hwnd);
    DeleteObject(region);
    editForce = 1;
    DrawEditBuffers();
    editForce = 0;
}

/* Unnamed edit renderer at ANTEDIT_MODULE:16D4. The two retained handles are
   private edit-sized work tables; the bitmap handle remains editBuf. */
static int near editCellHandle;
static int near editMaskHandle;
extern int near editBuf;
extern int near theEditBufPtr;
extern int near editForce;
extern int far win_GetObjRect(int window, struct Rect far *rect, int flags);
extern int far mem_Alloc(int group, char far *name, int flags, unsigned long bytes);
extern void far *mem_Lock(int handle);
extern int far mem_Unlock(int handle);
extern int far mem_Free(int handle);
extern void far PreDrawSpider(void);
extern void far DrawCurBalloons(void);
extern void far myServiceSong(void);
extern void far DrawSpider(void);
extern void far DrawBalloons(void);
extern void near RenderEditTile(int x, int y);
static void near DrawEditBuffers(void)
{
    struct Rect rect;
    int x, y;
    unsigned long cells;

    if (editBuf == 0) {
        win_GetObjRect(win_hwnd[0], &rect, 4);
        editHeight = (rect.bottom - rect.top + tileHeight - 1) / tileHeight;
        editWidth = (rect.right - rect.left + tileWidth - 1) / tileWidth;
        rect.right = rect.left + editWidth * tileWidth;
        rect.bottom = rect.top + editHeight * tileHeight;

        if (editCellHandle) {
            mem_Unlock(editCellHandle);
            mem_Free(editCellHandle);
            editCellHandle = 0;
        }
        if (editMaskHandle) {
            mem_Unlock(editMaskHandle);
            mem_Free(editMaskHandle);
            editMaskHandle = 0;
        }
        cells = (unsigned long)editWidth * editHeight;
        editCellHandle = mem_Alloc(0, "EditCells", 1, cells);
        editMaskHandle = mem_Alloc(0, "EditMasks", 1, cells * 2UL);
        if (mem_Lock(editMaskHandle))
            _fmemset(mem_Lock(editMaskHandle), 0xff, (unsigned)cells * 2);

        editBufInvalidFlag = 0;
        if (MapPlane > 1) {
            if (MapPnt.x + editWidth > 64)
                MapPnt.x = 64 - editWidth;
        } else if (MapPnt.x + editWidth > 128) {
            MapPnt.x = 128 - editWidth;
        }
        if (MapPnt.x < 0) MapPnt.x = 0;
        if (MapPnt.y < 0) MapPnt.y = 0;
        else if (MapPnt.y + editHeight > 64) MapPnt.y = 64 - editHeight;
        ResetEditScrollRange(win_hwnd[0]);
        editBuf = mem_Alloc(0, "EditBitmap", 1,
            (unsigned long)editWidth * tileWidth * editHeight * tileHeight + 32UL);
    }

    theEditBufPtr = (int)mem_Lock(editBuf);
    PreDrawSpider();
    DrawCurBalloons();
    for (y = 0; y < editHeight; ++y) {
        for (x = 0; x < editWidth; ++x) {
            RenderEditTile(x, y);
        }
        myServiceSong();
    }
    if (editForce) editBufInvalidFlag = 0;
    DrawSpider();
    DrawBalloons();
    mem_Unlock(editBuf);
    theEditBufPtr = 0;
}

void far DoEditScrollLine(char c)
{
    char far *buf;

    if (!(displayType & 1)) {
        buf = mem_Lock(editBuf);
        switch (c) {
        case 'u':
            EditScrollUpColor(buf, tileDsp, tileMask, editHeight, editWidth, tileHeight, tileWidth);
            break;
        case 'd':
            EditScrollDownColor(buf, tileDsp, tileMask, editHeight, editWidth, tileHeight, tileWidth);
            break;
        case 'l':
            EditScrollLeftColor(buf, tileDsp, tileMask, editHeight, editWidth, tileHeight, tileWidth);
            break;
        case 'r':
            EditScrollRightColor(buf, tileDsp, tileMask, editHeight, editWidth, tileHeight, tileWidth);
            break;
        }
        mem_Unlock(editBuf);
        DrawEditBuffers();
        InvalidateRect(win_hwnd[0], (void far *)0, 0);
        UpdateWindow(win_hwnd[0]);
    } else {
        DrawEditBuffers();
    }

    if (win_IsWinOpen(0x100)) {
        MSClipStart(win_hwnd[1]);
        EraseMapCursor();
        DrawMapCursor();
        MSClipEnd();
    }
}
