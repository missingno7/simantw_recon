/* Candidate reconstruction of the allocator timestamp refresh. */
struct RallocFreshenRecord {
    unsigned char unused[10];
    unsigned long stamp;
};

extern unsigned long far pascal GetTickCount(void);

void RallocFreshen(struct RallocFreshenRecord far *record)
{
    record->stamp = GetTickCount();
}
