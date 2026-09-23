/* Hypothesis: the signed high byte selects a window resource. Loading it returns
   a handle whose locked block is installed in win_handles. The bucket's object
   table contains far records with a type byte at offset 0x21. */
struct WinObject {
    unsigned char prefix[0x21];
    unsigned char type;
    unsigned char suffix[0x2a - 0x22];
    int width;
    int height;
};
struct WinBucket {
    unsigned char prefix[0x0c];
    int objectCount;
    unsigned char gap[0x2c - 0x0e];
    struct WinObject far *objects[256];
};
extern struct WinBucket far * near win_handles[];
extern unsigned int far db_LoadObject(int object, int kind, int lock);
extern void far *mem_Lock(unsigned int handle);
extern void far Punt(char far *message, ...);
extern void far win_LockWin(int objectNumber);
extern void far win_UnlockWin(int objectNumber);
extern int far match_position[];

void far win_LoadWindow(int objectNumber)
{
    unsigned int handle;
    struct WinBucket far *bucket;
    struct WinObject far *object;
    int i;

    handle = db_LoadObject((signed char)(objectNumber >> 8), 0, 1);
    if (!handle)
        Punt("Cannot load window", objectNumber);
    win_handles[objectNumber >> 8] = mem_Lock(handle);
    win_LockWin(objectNumber);
    bucket = win_handles[objectNumber >> 8];
    for (i = 0; i < bucket->objectCount; ++i) {
        object = bucket->objects[i];
        bucket->objects[i] = object;
    }
    win_UnlockWin(objectNumber);
}
