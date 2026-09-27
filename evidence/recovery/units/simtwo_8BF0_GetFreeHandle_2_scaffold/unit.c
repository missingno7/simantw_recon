/* Candidate translation unit simtwo_8BF0_GetFreeHandle_2_scaffold: composed from preserved exact-body sources
 * in MAPSYM order. Internal evidence id, not a historical filename.
 * Members: _GetFreeHandle, _DosPunt
 * SCAFFOLDED: claimed members in 1 code runs; no pool stand-ins were needed. */

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
extern struct OpenDB __based(__segname("PACK")) openDBData[4];
extern int near errno;
extern char far * near sys_errlist[];
extern void far Punt(char far *message, ...);


void far pool_data_fill_B4F8(void);

#pragma alloc_text(POOLSTUB_TEXT, pool_data_fill_B4F8)

static int openDBInitialized = 0;
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

/* SCAFFOLD, not recovered source: the 114 bytes of private data between _DosPunt and _DosPunt (DGROUP B4F8-B56A, unclaimed members), copied from the image so the claimed pieces keep their layout. */
void far pool_data_fill_B4F8(void)
{
    volatile char far *p;

    p = "\040\040\131\157\165\040\156\145\145\144\040\141\040\163\164\141\164\145\155\145\156\164\040\047\106\111\114\105\123\075\061\062\047\040\151\156\012\171\157\165\162\040\143\157\156\146\151\147\056\163\171\163\040\146\151\154\145\056\040\040\120\154\145\141\163\145\040\162\145\146\145\162\040\164\157\040\171\157\165\162\040\144\157\163\040\155\141\156\165\141\154\012\146\157\162\040\155\157\162\145\040\151\156\146\157\162\155\141\164\151\157\156\056";
}

void DosPunt(int first, int second)
{
    if (errno == 0x18) {
        Punt("Too many open files");
    }
    Punt("DOS error %d: %s (%d, %d)", first, second, errno,
         sys_errlist[errno]);
}

