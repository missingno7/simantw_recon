/*
 * Keep the edit viewport's cached map position current.  When the cached and
 * live views overlap on the same map and terrain, scroll the existing pixels
 * and edit arrays; otherwise let the normal invalidation path redraw them.
 */
struct Rect {
    int left;
    int top;
    int right;
    int bottom;
};

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
extern void far UpdateEditWindow(void);
extern void far UpdateEditWindow(void);

void far updateedit_pool_scaffold(void);
#pragma alloc_text(POOLSTUB_TEXT, updateedit_pool_scaffold)
void far updateedit_pool_scaffold(void) { }

void far UpdateEditIfBufInvalid(void);
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


extern unsigned char near displayType;
extern unsigned int near editBuf;
extern void far *mem_Lock(unsigned int handle);
extern int far mem_Unlock(unsigned int handle);
extern char far * near tileDsp;
extern char far * near tileMask;
extern void far EditScrollUpColor(char far *, char far *, char far *, int, int, int, int);
extern void far EditScrollDownColor(char far *, char far *, char far *, int, int, int, int);
extern void far EditScrollLeftColor(char far *, char far *, char far *, int, int, int, int);
extern void far EditScrollRightColor(char far *, char far *, char far *, int, int, int, int);
extern void far pascal InvalidateRect(int window, void far *rect, unsigned flags);
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
    DrawEditBuffers();
    editForce = 0;
    ResetEditScrollRange(win_hwnd[0]);
    MSClipStart(win_hwnd[0]);
    DrawEditGraphs();
    MSClipEnd();
}
void far UpdateEditWindow(void) { UpdateEdit(); }

void far UpdateEditIfBufInvalid(void)
{
    int region;

    if (!editBufInvalidFlag)
        return;

    region = CreateRectRgn(0, 0, 10, 10);
    GetUpdateRgn(win_hwnd[0], region, 0);
    ValidateRgn(win_hwnd[0], region);
    UpdateWindow(win_hwnd[0]);
    DeleteObject(region);
    editForce = 1;
    DrawEditBuffers();
    editForce = 0;
}


/* Public members physically between the edit-buffer callers and helper. */

void far DrawEdit(void) { }
struct WinRect {
    int left;
    int top;
    int right;
    int bottom;
};

extern unsigned int near editBuf;
extern unsigned int near updateRgn;
extern unsigned char near displayType;
extern struct MapPoint far editTileRect;
extern int far match_position[];

extern void far *mem_Lock(unsigned int handle);
extern int far mem_Unlock(unsigned int handle);
extern int far pascal RectInRegion(unsigned int region, struct WinRect far *rect);
extern void far DoFastBitmap(int color, void far *buf, int h, int w, int y, int x);
extern void far DoFastMonoBitmap(void far *buf, int h, int w, int y, int x);
extern void far DrawEditGraphs(void);
extern void far win_GetObjRect(int flags, int window, struct WinRect far *rect);


/*
 * Hypothesis: choose a 64- or 128-pixel horizontal edit bound from MapPlane,
 * clamp the far match_position x coordinate using editWidth, then clamp y to
 * the 64-pixel edit area using editHeight.  Negative y is normalized and
 * returns immediately, matching the target's short second-path return.
 */
extern int near MapPlane;
extern int near editWidth;
extern int near editHeight;
extern int far match_position[];


static int near ScrollEditBy(int dx, int dy);

void far win_DrawEditWindow(int flags)
{
    struct WinRect rect;
    void far *buf;
    int py, px;

    if (!(flags & 2))
        return;

    if (editBuf != 0) {
        if (updateRgn == 0 ||
            RectInRegion(updateRgn, (struct WinRect far *)match_position)) {
            buf = mem_Lock(editBuf);
            px = editTileRect.x;
            py = editTileRect.y;
            if ((displayType & 1) == 0)
                DoFastBitmap(0, buf, tileHeight * editHeight, tileWidth * editWidth, py, px);
            else
                DoFastMonoBitmap(buf, tileHeight * editHeight, tileWidth * editWidth, py, px);
            mem_Unlock(editBuf);
        }
    }

    DrawEditGraphs();
    win_GetObjRect(7, win_hwnd[0], &rect);
}
void far BoundEditPosition(void)
{
    int limit;
    switch (MapPlane) {
    case 0:
    case 1:
        limit = 0x80;
        break;
    default:
        limit = 0x40;
        break;
    }

    if (match_position[0x3e97] < 0)
        match_position[0x3e97] = 0;
    else if (match_position[0x3e97] + editWidth > limit)
        match_position[0x3e97] = limit - editWidth;

    if (match_position[0x3e98] < 0) {
        match_position[0x3e98] = 0;
        return;
    }
    if (match_position[0x3e98] + editHeight > 0x40)
        match_position[0x3e98] = 0x40 - editHeight;
}
int far CenterEdit(int x, int y)
{
    int width;
    int height;
    int result;

    if (ScrollEditBy(x - MapPnt.x - editWidth / 2,
                     y - MapPnt.y - editHeight / 2)) {
        height = 64;
        switch (MapPlane) {
        case 0:
        case 1:
            width = 128;
            break;
        }
        if (MapPnt.x < 0)
            MapPnt.x = 0;
        else if (MapPnt.x + editWidth > width)
            MapPnt.x = width - editWidth;
        if (MapPnt.y < 0)
            MapPnt.y = 0;
        else if (MapPnt.y + editHeight > height)
            MapPnt.y = height - editHeight;
        result = 1;
    } else {
        result = 0;
    }
    return result;
}

/* Static edit-buffer renderer at ANTEDIT_MODULE:16D4. It rounds the client
   rectangle to tiles, renews the per-cell work tables when the bitmap is
   absent, clamps MapPnt, and redraws each tile before the overlay passes. */
static int near editCellHandle;
static int near editMaskHandle;
extern unsigned int near editBuf;
extern int near theEditBufPtr;
extern void far win_GetObjRect(int flags, int window, struct WinRect far *rect);
extern int far mem_Alloc(int group, char far *name, int flags, unsigned long bytes);
extern void far *mem_Lock(unsigned int handle);
extern int far mem_Unlock(unsigned int handle);
extern int far mem_Free(unsigned int handle);
extern void far PreDrawSpider(void);
extern void far DrawCurBalloons(void);
extern void far myServiceSong(void);
extern void far DrawSpider(void);
extern void far DrawBalloons(void);
extern void near RenderEditTile(int x, int y);
static void near DrawEditBuffers(void)
{
    struct WinRect rect;
    int x, y;
    unsigned long cells;
    unsigned char far *mask;

    if (editBuf == 0) {
        win_GetObjRect(4, win_hwnd[0], &rect);
        editHeight = (rect.bottom - rect.top + tileHeight - 1) / tileHeight;
        editWidth = (rect.right - rect.left + tileWidth - 1) / tileWidth;
        rect.right = rect.left + editWidth * tileWidth;
        rect.bottom = rect.top + editHeight * tileHeight;
        if (editCellHandle) { mem_Unlock(editCellHandle); mem_Free(editCellHandle); editCellHandle = 0; }
        if (editMaskHandle) { mem_Unlock(editMaskHandle); mem_Free(editMaskHandle); editMaskHandle = 0; }
        cells = (unsigned long)editWidth * editHeight;
        editCellHandle = mem_Alloc(0, "EditCells", 1, cells);
        editMaskHandle = mem_Alloc(0, "EditMasks", 1, cells * 2UL);
        mask = (unsigned char far *)mem_Lock(editMaskHandle);
        for (x = 0; x < (int)(cells * 2UL); ++x) mask[x] = 0xff;
        mem_Unlock(editMaskHandle);
        editBufInvalidFlag = 0;
        if (MapPlane > 1) {
            if (MapPnt.x + editWidth > 64) MapPnt.x = 64 - editWidth;
        } else if (MapPnt.x + editWidth > 128) MapPnt.x = 128 - editWidth;
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
        for (x = 0; x < editWidth; ++x) RenderEditTile(x, y);
        myServiceSong();
    }
    if (editForce) editBufInvalidFlag = 0;
    DrawSpider();
    DrawBalloons();
    mem_Unlock(editBuf);
    theEditBufPtr = 0;
}


/* Later direct caller of the same edit-buffer routine. */
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

static int near ScrollEditBy(int dx, int dy)
{
    int xStep;
    int yStep;
    register int i;
    unsigned long fraction;
    unsigned long error;

    if (dx == 0 && dy == dx)
        return 0;

    xStep = 1;
    yStep = 1;
    if (dx < 0) {
        xStep = -1;
        dx = -dx;
    }
    if (dy < 0) {
        yStep = -1;
        dy = -dy;
    }

    error = 0UL;
    if (dy >= dx) {
        fraction = ((unsigned long)dx << 16) / (unsigned long)dy;
        if (dy > 0) {
            for (i = dy; i > 0; --i) {
                MapPnt.y += yStep;
                error += fraction;
                if ((error >> 16) & 1UL) {
                    MapPnt.x += xStep;
                    error ^= 0x10000UL;
                }
            }
        }
    } else {
        fraction = ((unsigned long)dy << 16) / (unsigned long)dx;
        if (dx > 0) {
            for (i = dx; i > 0; --i) {
                MapPnt.x += xStep;
                error += fraction;
                if ((error >> 16) & 1UL) {
                    MapPnt.y += yStep;
                    error ^= 0x10000UL;
                }
            }
        }
    }
    return 1;
}
