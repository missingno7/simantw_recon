/* Hypothesis: explicit shared success and exhausted-record labels set the bottom return layout. */
struct OpenDB {
    char name[0x50];
    void far *indexTable;
    int recordCount;
    unsigned char pad1[0x6c - 0x56];
    int count;
    long freeBytes;
    long wastedBytes;
    int pad2;
    int file;
    int dirty;
};
static int openDBInitialized = 0;
extern struct OpenDB __based(__segname("PACK")) openDBData[4];

int GetFreeHandle(void)
{
    struct OpenDB __based(__segname("PACK")) *slot;
    int count;

    if (openDBInitialized != 0)
        goto scan_slots;
    openDBInitialized = 1;
    slot = &openDBData[0];
    do { slot->name[0] = 0; ++slot; } while (slot < &openDBData[4]);
scan_slots:
    count = 0;
    slot = &openDBData[0];
scan:
    if (slot->name[0] == 0)
        goto found;
    ++count;
    ++slot;
    if (slot < &openDBData[4])
        goto scan;
    goto full;
found:
    return count;
full:
    return -1;
}
