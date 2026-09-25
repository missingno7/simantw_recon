/*
 * Ralloc: allocate a tracked block of size bytes.  The allocator's free
 * search is refreshed for size + 17 bytes, then a moveable Windows global
 * block of that size is allocated and locked (a failure returns NULL,
 * freeing the handle if only the lock failed).  The 16-byte record at the
 * start of the block receives the far pointer to its data (record + 16),
 * the global handle, the tick count, the caller's tag and the requested
 * size; the private live-allocation counter shared with RallocFree grows
 * and the record pointer is returned.
 */
struct RallocRecord {
    void far *data;
    unsigned int handle;
    long size;
    unsigned long tick;
    int tag;
};

static unsigned long near rallocCount = 0;
extern void far RallocFindMem(long bytes);
extern unsigned int far pascal GlobalAlloc(unsigned int flags, unsigned long bytes);
extern void far * far pascal GlobalLock(unsigned int handle);
extern unsigned int far pascal GlobalFree(unsigned int handle);
extern unsigned long far pascal GetTickCount(void);

struct RallocRecord far *far Ralloc(long size, int tag)
{
    unsigned int handle;
    struct RallocRecord far *record;

    RallocFindMem(size + 0x11);
    handle = GlobalAlloc(2, size + 0x11);
    if (handle == 0)
        return 0;
    record = GlobalLock(handle);
    if (record == 0) {
        GlobalFree(handle);
        return 0;
    }
    record->data = (char far *)record + 0x10;
    record->handle = handle;
    record->tick = GetTickCount();
    record->tag = tag;
    record->size = size;
    rallocCount++;
    return record;
}
