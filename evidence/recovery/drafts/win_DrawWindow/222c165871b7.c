/* Round 6: call-binding and control-flow hypothesis. */
/* Reconstruct the per-window object draw pass from its bucket and hook table. */
struct WinObject {
    unsigned char reserved[0x24];
    unsigned char flags;
    unsigned char tail[0x30 - 0x25];
};
struct WinEntry {
    struct WinObject far *object;
};
struct WinBucket {
    unsigned char head[0x0c];
    int objectCount;
    unsigned char middle[0x1c - 0x0e];
    unsigned char flags;
    unsigned char rest[0x2c - 0x1d];
    struct WinEntry far *entries[256];
};
typedef void (far *WinDrawHook)(int);
extern struct WinBucket far * near win_handles[];
extern WinDrawHook far win_drawHooks[];
extern int far _updateRgn;
extern void win_LockWinHigh(int objectNumber);
extern void win_UnlockWin(int objectNumber);
extern int far pascal RectInRegion(int region, struct WinObject far *object);
extern void win_DrawObjectI(void far *object);

void far win_DrawWindow(int objectNumber)
{
    struct WinBucket far *bucket;
    struct WinEntry far *entry;
    struct WinObject far *object;
    int highIndex;
    int i;
    int drawn;
    int objectCount;
    int hookCalled;

    win_LockWinHigh(objectNumber);
    highIndex = objectNumber >> 8;
    bucket = win_handles[highIndex];
    if (!(bucket->flags & 0x20)) {
        if (win_drawHooks[highIndex]) {
            win_drawHooks[highIndex](1);
            drawn = 0;
            hookCalled = 1;
            objectCount = bucket->objectCount;
            i = 1;
            while (i < objectCount) {
                entry = bucket->entries[i];
                object = entry->object;
                if (!_updateRgn ||
                    RectInRegion(_updateRgn, object)) {
                    if (object->flags & 1) {
                        win_DrawObjectI(object);
                        if (!drawn) {
                            *(long far *)bucket = *(long far *)bucket->entries[0];
                            drawn = 1;
                        }
                    }
                }
                ++i;
            }
            if (hookCalled)
                win_drawHooks[highIndex](2);
        }
    }
    win_UnlockWin(objectNumber);
}
