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
extern struct WinBucket far * __based(__segname("SIMANT_DATA_GROUP")) win_handles[];
extern WinDrawHook __based(__segname("PACK")) win_drawHooks[];
extern int far _updateRgn;
extern void far win_LockWinHigh(int objectNumber);
extern void far win_UnlockWin(int objectNumber);
extern int far pascal RectInRegion(int region, struct WinObject far *object);
extern void far win_DrawObjectI(void far *object);

void far win_DrawWindow(int objectNumber)
{
    struct WinBucket far *bucket;
    struct WinEntry far *entry;
    struct WinObject far *object;
    int highIndex;
    int i;
    int drawn;

    win_LockWinHigh(objectNumber);
    highIndex = (objectNumber >> 8) * 4;
    bucket = *(struct WinBucket far * far *)((char near *)win_handles + highIndex);
    if (!(bucket->flags & 0x20)) {
        if (*(WinDrawHook far *)((char far *)win_drawHooks + highIndex)) {
            *(WinDrawHook far *)((char far *)win_drawHooks + highIndex)(1);
            drawn = 1;
            i = 1;
            while (i < bucket->objectCount) {
                entry = bucket->entries[i];
                object = entry->object;
                if (!_updateRgn ||
                    RectInRegion(_updateRgn, object)) {
                    if (object->flags & 1) {
                        win_DrawObjectI(object);
                        if (!drawn) {
                            *(long far *)bucket = *(long far *)bucket->entries[0];
                        }
                    }
                }
                ++i;
            }
        }
    }
    win_UnlockWin(objectNumber);
}
