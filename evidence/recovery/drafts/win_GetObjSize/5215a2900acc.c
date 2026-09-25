/*
 * Hypothesis: lock the packed object number's window, copy that object's
 * four-word rectangle into the historical local rectangle, and return its
 * width and height through the far result pointer.  The bucket index is the
 * signed high byte and the object index is the low byte; the shared bucket
 * layout and 0x2c rectangle-pointer table are established by win_ObjAddr and
 * win_GetObjRect.
 */
struct WinRect {
    int left;
    int top;
    int right;
    int bottom;
};

struct WinBucket {
    unsigned char header[0x2c];
    struct WinRect far *rects[256];
};

struct WinSize {
    int width;
    int height;
};

extern struct WinBucket far * near win_handles[];
extern void far win_LockWin(int objectNumber);
extern void far win_UnlockWin(int objectNumber);

void far win_GetObjSize(int objectNumber, struct WinSize far *size)
{
    struct WinRect rect;
    struct WinBucket far *bucket;

    win_LockWin(objectNumber);
    bucket = win_handles[objectNumber >> 8];
    rect = *bucket->rects[(unsigned char)objectNumber];
    size->width = rect.right - rect.left;
    size->height = rect.bottom - rect.top;
    win_UnlockWin(objectNumber);
}
