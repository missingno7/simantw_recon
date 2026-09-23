/* First semantic draft: reserve two GlobalAlloc blocks, release the reserve
 * under pressure, pause once when compaction restores enough free space,
 * otherwise report and terminate. The three near words and messages are
 * taken from the target DGROUP bytes at 087C-08EE. */
static unsigned int near reserveHandle = 0;
static unsigned int near softHandle = 0;
int near lowMemoryReported = 0;
static struct MemoryMessages {
    char freeSize[21];
    char fatal[37];
    char warning[54];
} near messages = {
    "Free: %lu Size: %ld\n",
    "Out of memory.  Terminating Program.",
    "Running low on memory.  Pausing game.\nRefer to manual"
};

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
        if (lowMemoryReported == 0) {
            SetPause(1);
            PopMsg(messages.warning);
            lowMemoryReported = 1;
            goto finish;
        }
    }
    WinPrintf(messages.freeSize, GlobalCompact(0UL), needed);
    if (softHandle != 0)
        GlobalFree(softHandle);
    GlobalCompact(0xffffffffUL);
    PopMsg(messages.fatal);
    CleanUp();
    PostQuitMessage(0);
    exit(0);
finish:
    GlobalCompact(0xffffffffUL);
}
