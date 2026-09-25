/* Ralloc and RallocFree share the live-allocation counter at DGROUP. */
struct RallocRecord {
    void far *data;
    unsigned int handle;
    long size;
    unsigned long tick;
    int tag;
};

static unsigned long near rallocCount = 0;

extern void far RallocFindMem();
extern unsigned int far pascal GlobalAlloc(unsigned int flags,
                                           unsigned long bytes);
extern void far * far pascal GlobalLock(unsigned int handle);
extern unsigned int far pascal GlobalFree(unsigned int handle);
extern int far pascal GlobalUnlock(unsigned int handle);
extern unsigned int far pascal GlobalReAlloc(unsigned int handle,
                                             unsigned long bytes,
                                             unsigned int flags);
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

struct RallocRecord far *far RallocRealloc(struct RallocRecord far *record,
                                            long size, int tag)
{
    unsigned int handle;
    struct RallocRecord far *block;

    handle = record->handle;
    GlobalUnlock(handle);
    RallocFindMem(size + 0x11);
    handle = GlobalReAlloc(handle, size + 0x11, 2);
    if (handle == 0)
        return 0;
    block = GlobalLock(handle);
    if (block == 0) {
        GlobalFree(handle);
        return 0;
    }
    block->data = (char far *)block + 0x10;
    block->handle = handle;
    block->tick = GetTickCount();
    block->tag = tag;
    block->size = size;
    return block;
}

void RallocFree(struct RallocRecord far *record)
{
    unsigned int handle;

    handle = record->handle;
    --rallocCount;
    GlobalUnlock(handle);
    GlobalFree(handle);
    RallocFindMem(-1, -1);
}
