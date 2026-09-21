/*
 * Hypothesis: resolve the packed object number through win_handles, copy
 * its far rectangle into a local four-word rectangle, apply the historical
 * ribbon adjustment, and test the supplied far point after unlocking.
 * The bucket and rectangle-pointer layout is independently established by
 * the recovered win_GetObjRect and win_GetObjSize helpers.
 */
struct CursorRect {
    int left;
    int top;
    int right;
    int bottom;
};

struct CursorPoint {
    int x;
    int y;
};

struct WinBucket {
    unsigned char header[0x2c];
    struct CursorRect far *rects[256];
};

extern struct WinBucket far * near win_handles[];
extern int near ribbonBarHeight;
extern void win_LockWin(int objectNumber);
extern void win_UnlockWin(int objectNumber);
extern int far PointInRect(struct CursorPoint far *point,
                           struct CursorRect far *rect);

int far win_IsPointInObj(struct CursorPoint far *point, int objectNumber)
{
    struct CursorRect rect;
    struct WinBucket far *bucket;

    win_LockWin(objectNumber);
    bucket = win_handles[objectNumber >> 8];
    rect = *bucket->rects[(unsigned char)objectNumber];
    if (ribbonBarHeight) {
        ++rect.right;
        ++rect.bottom;
    }
    win_UnlockWin(objectNumber);
    return PointInRect(point, &rect);
}
