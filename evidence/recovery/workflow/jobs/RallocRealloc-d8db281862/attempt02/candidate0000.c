/*
 * RallocRealloc: resize a tracked block.  The record's global handle is
 * unlocked, the allocator's free search is refreshed for size + 17 bytes
 * and the block is reallocated (moveable) to that size; a failure returns
 * NULL.  The block is locked again (freeing the handle if the lock fails)
 * and the 16-byte record at its start is rebuilt: the far data pointer
 * (record + 16), the handle, the tick count, the caller's tag and the
 * requested size.  The new record pointer is returned.
 */
struct RallocRecord {
    void far *data;
    unsigned int handle;
    long size;
    unsigned long tick;
    int tag;
};

extern void far RallocFindMem(long bytes);
extern int far pascal GlobalUnlock(unsigned int handle);
extern unsigned int far pascal GlobalReAlloc(unsigned int handle, unsigned long bytes, unsigned int flags);
extern void far * far pascal GlobalLock(unsigned int handle);
extern unsigned int far pascal GlobalFree(unsigned int handle);
extern unsigned long far pascal GetTickCount(void);

struct RallocRecord far *far RallocRealloc(struct RallocRecord far *record, long size, int tag)
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
