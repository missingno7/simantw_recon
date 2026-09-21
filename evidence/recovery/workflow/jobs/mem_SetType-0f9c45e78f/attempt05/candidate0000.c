/*
 * Change the discardability class of a global-memory block.  The prologue's
 * three decrements partition the second argument into type <= 2, type == 3,
 * and all other values.  The first class promotes a block to the 0x80 flag
 * only when GLOBALFLAGS reports the corresponding high-byte bit; type 3
 * removes that flag by requesting 0x180 only when the bit is absent.
 */
extern unsigned int far pascal GlobalFlags(int handle);
extern unsigned int far pascal GlobalReAlloc(int handle,
                                             unsigned long bytes,
                                             unsigned int flags);

void mem_SetType(int handle, int type)
{
    if (type < 0)
        return;
    if (type - 1 - 1 <= 0) {
        if (GlobalFlags(handle) & 0x100)
            GlobalReAlloc(handle, 0L, 0x80);
    } else if (type - 1 - 1 - 1 == 0) {
        if (!(GlobalFlags(handle) & 0x100))
            GlobalReAlloc(handle, 0L, 0x180);
    }
}
