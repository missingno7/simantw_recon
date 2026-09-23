/* First semantic draft: reserve two GlobalAlloc blocks, release the reserve
 * under pressure, pause once when compaction restores enough free space,
 * otherwise report and terminate. The three near words and messages are
 * taken from the target DGROUP bytes at 087C-08EE. */
static unsigned int near reserveHandle = 0;
static unsigned int near softHandle = 0;
static int near lowMemoryReported = 0;

extern unsigned long far pascal GlobalCompact(unsigned long minimum);
extern unsigned int far pascal GlobalAlloc(unsigned int flags, unsigned long bytes);
extern unsigned int far pascal GlobalFree(unsigned int handle);
extern unsigned long far pascal GetFreeSpace(unsigned int flags);
extern void far SetPause(int paused);
extern void far PopMsg(char far *message);
extern void far WinPrintf(char far *format, ...);
extern void far CleanUp(void);
extern void far pascal PostQuitMessage(int code);
extern void far exit(int code);

void far RallocFindMem(unsigned long needed)
{
    if (softHandle == 0) {
        GlobalCompact(0xffffffffUL);
        softHandle = GlobalAlloc(2, 50000UL);
    }
    if (reserveHandle == 0) {
        if (GlobalCompact(0UL) > 100000UL) {
            GlobalCompact(0xffffffffUL);
            reserveHandle = GlobalAlloc(2, 100000UL);
        }
        lowMemoryReported = 0;
    }
    if (needed == 0xffffffffUL)
        return;
    if (GlobalCompact(0UL) >= needed && GetFreeSpace(0) >= needed)
        return;
    if (reserveHandle != 0) {
        GlobalFree(reserveHandle);
        reserveHandle = 0;
    }
    if (GlobalCompact(0xffffffffUL) >= needed) {
        if (lowMemoryReported)
            goto out_of_memory;
        SetPause(1);
        PopMsg("Running low on memory.  Pausing game.\nRefer to manual");
        lowMemoryReported = 1;
        goto finish;
    }
out_of_memory:
    WinPrintf("Free: %lu Size: %ld\n", GlobalCompact(0UL), needed);
    if (softHandle != 0)
        GlobalFree(softHandle);
    GlobalCompact(0xffffffffUL);
    PopMsg("Out of memory.  Terminating Program.");
    CleanUp();
    PostQuitMessage(0);
    exit(0);
finish:
    GlobalCompact(0xffffffffUL);
}
