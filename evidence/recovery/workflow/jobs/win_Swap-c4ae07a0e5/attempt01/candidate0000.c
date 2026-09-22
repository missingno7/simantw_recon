/*
 * win_Swap: hand a window object's on-screen position to another object.
 * A no-op unless win_hwnd[objectNumber>>8] is already open.  The source
 * bucket is locked; its saved rectangle (info[0]->savedRect, the far
 * WindowInfo the bucket's info[] table addresses, exactly the far pointer
 * win_GetObjRect/win_ClearObjArea read at bucket+0x2c) and its own current
 * rectangle (the bucket header's own leading WinRect) are copied out, the
 * bucket's flags byte at +0x1d has bit 1 cleared, and it is unlocked.  The
 * destination bucket is then locked: its info[0]->savedRect left/top are
 * set from the source's saved rect, its own rectangle is set from the
 * source's rectangle and immediately re-propagated into info[0]->rect (a
 * genuine memory-to-memory chain, not a single copy), its header's newRect
 * field at +0x10 gets the caller's four coordinates, win_Recalc lays the
 * window out, its flags byte gets bit 1 set, and it is unlocked.  Finally
 * the source's HWND is tagged onto the destination via SetProp (the same
 * "INDEX" literal INDIRECTDLGPROC uses, at a different DGROUP address),
 * moved into win_hwnd[otherObjectNumber>>8], the source's win_hwnd slot is
 * cleared, the (now relocated) window is shown and invalidated.
 */
struct WinRect {
    int left;
    int top;
    int right;
    int bottom;
};

struct WindowInfo {
    struct WinRect rect;
    struct WinRect savedRect;
    struct WinRect newRect;
};

struct WinBucket {
    struct WinRect rect;
    unsigned char pad1[0x10 - 8];
    struct WinRect newRect;
    unsigned char pad2[0x1d - 0x18];
    unsigned char flags;
    unsigned char pad3[0x2c - 0x1e];
    struct WindowInfo far *info[256];
};

extern struct WinBucket far * near win_handles[];
extern int near win_hwnd[];

extern void far win_LockWin(int objectNumber);
extern void far win_UnlockWin(int objectNumber);
extern void far win_Recalc(int window);
extern int far pascal SetProp(unsigned hwnd, char far *name, unsigned data);
extern void far pascal ShowWindow(int window, int command);
extern void far pascal InvalidateRect(int window, void far *rect, int erase);

void far win_Swap(int objectNumber, int otherObjectNumber, int reserved,
                  int left, int top, int right, int bottom)
{
    struct WinBucket far *bucket;
    struct WinBucket far *otherBucket;
    struct WindowInfo far *info;
    struct WindowInfo far *otherInfo;
    struct WinRect savedRect;
    struct WinRect rect;

    if (win_hwnd[objectNumber >> 8] == 0)
        return;

    win_LockWin(objectNumber);
    bucket = win_handles[objectNumber >> 8];
    info = bucket->info[0];
    savedRect = info->savedRect;
    rect = bucket->rect;
    bucket->flags &= ~2;
    win_UnlockWin(objectNumber);

    win_LockWin(otherObjectNumber);
    otherBucket = win_handles[otherObjectNumber >> 8];
    otherInfo = otherBucket->info[0];
    otherInfo->savedRect.left = savedRect.left;
    otherInfo->savedRect.top = savedRect.top;
    otherBucket->rect = rect;
    otherInfo->rect = otherBucket->rect;
    otherBucket->newRect.left = left;
    otherBucket->newRect.top = top;
    otherBucket->newRect.right = right;
    otherBucket->newRect.bottom = bottom;
    win_Recalc(otherObjectNumber);
    otherBucket->flags |= 2;
    win_UnlockWin(otherObjectNumber);

    SetProp(win_hwnd[objectNumber >> 8], "INDEX", otherObjectNumber);
    win_hwnd[otherObjectNumber >> 8] = win_hwnd[objectNumber >> 8];
    win_hwnd[objectNumber >> 8] = 0;
    ShowWindow(win_hwnd[otherObjectNumber >> 8], 5);
    InvalidateRect(win_hwnd[otherObjectNumber >> 8], 0, 1);
}
