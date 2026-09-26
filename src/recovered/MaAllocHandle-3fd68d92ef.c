/* Allocate a movable block, compact once if necessary, then retry. */
extern unsigned far pascal GlobalAlloc(unsigned, unsigned long);
extern unsigned long far pascal GlobalCompact(unsigned long);
unsigned MaAllocHandle(unsigned long bytes)
{
    unsigned handle = GlobalAlloc(0x42, bytes);
    if (!handle && GlobalCompact(bytes) >= bytes)
        handle = GlobalAlloc(0x42, bytes);
    return handle;
}
