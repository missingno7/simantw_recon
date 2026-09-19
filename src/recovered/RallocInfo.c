/* Candidate reconstruction of the allocator-size diagnostic. */
struct RallocInfoRecord {
    unsigned char unused[6];
    unsigned long size;
};

extern void far WinPrintf(char far *format, ...);

void RallocInfo(struct RallocInfoRecord far *record)
{
    WinPrintf("RallocInfo(Size=%lu)\n", record->size);
}
