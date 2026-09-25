/* Supervisor hypothesis: Private initialized 32-bit live-allocation counter; SUB/SBB identifies its width and fixture bytes establish a zero initializer. */
/*
 * Release one allocator record.  The record stores its Windows global
 * handle at offset four; the live-allocation count is decremented before the
 * handle is unlocked and freed, then the allocator's free-list search is
 * refreshed with the two sentinel bounds.
 */
struct RallocRecord {
    void far *data;
    unsigned int handle;
};

static unsigned long near rallocCount = 0;
extern int far pascal GlobalUnlock(unsigned int handle);
extern unsigned int far pascal GlobalFree(unsigned int handle);
extern void far RallocFindMem(int low, int high);

void RallocFree(struct RallocRecord far *record)
{
    unsigned int handle;

    handle = record->handle;
    --rallocCount;
    GlobalUnlock(handle);
    GlobalFree(handle);
    RallocFindMem(-1, -1);
}
