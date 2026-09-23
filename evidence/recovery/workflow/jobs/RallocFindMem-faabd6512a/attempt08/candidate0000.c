/* First semantic draft: reserve two GlobalAlloc blocks, release the reserve
 * under pressure, pause once when compaction restores enough free space,
 * otherwise report and terminate. The three near words and messages are
 * taken from the target DGROUP bytes at 087C-08EE. */
static struct RallocState {
    unsigned int reserveHandle;
    unsigned int softHandle;
    int lowMemoryReported;
} near state = { 0, 0, 0 };
#define RALLOC_FORMAT "Free: %lu Size: %ld\n"
#define RALLOC_FATAL "Out of memory.  Terminating Program."
#define RALLOC_WARNING "Running low on memory.  Pausing game.\nRefer to manual"

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
    if (state.softHandle == 0) {
        GlobalCompact(0xffffffffUL);
        state.softHandle = GlobalAlloc(2, 50000UL);
    }
    if (state.reserveHandle == 0) {
        if (GlobalCompact(0UL) > 100000UL) {
            GlobalCompact(0xffffffffUL);
            state.reserveHandle = GlobalAlloc(2, 100000UL);
        }
        state.lowMemoryReported = 0;
    }
    if (needed == 0xffffffffUL)
        return;
    if (GlobalCompact(0UL) >= needed && GetFreeSpace(0) >= needed)
        return;
    if (state.reserveHandle != 0) {
        GlobalFree(state.reserveHandle);
        state.reserveHandle = 0;
    }
    if (GlobalCompact(0xffffffffUL) >= needed) {
        if (state.lowMemoryReported == 0) {
            SetPause(1);
            PopMsg(RALLOC_WARNING);
            state.lowMemoryReported = 1;
            goto finish;
        }
    }
    WinPrintf(RALLOC_FORMAT, GlobalCompact(0UL), needed);
    if (state.softHandle != 0)
        GlobalFree(state.softHandle);
    GlobalCompact(0xffffffffUL);
    PopMsg(RALLOC_FATAL);
    CleanUp();
    PostQuitMessage(0);
    exit(0);
finish:
    GlobalCompact(0xffffffffUL);
}
