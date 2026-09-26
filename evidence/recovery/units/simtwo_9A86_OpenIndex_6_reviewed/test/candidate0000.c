/* Reviewed incremental unit source: OpenIndex/CreateIndex/CloseIndex/FindIndex candidates plus admitted delete controls.
 * MAPSYM code order; The AddIndex private-data block remains a POOLSTUB_TEXT scaffold. */

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
struct IndexEntry {
    void far *payload;
    int value;
    unsigned char caste;
    unsigned char kind;
};
extern int far sprintf(char far *buffer, char far *format, ...);
extern int far pascal _lopen(char far *path, int mode);
extern int far pascal _lcreat(char far *path, int attrib);
extern long far pascal _lread(int handle, void far *buffer, unsigned count);
extern long far pascal _lwrite(int handle, void far *buffer, unsigned count);
extern int far pascal _lclose(int handle);
extern long far pascal _llseek(int handle, long offset, int origin);
extern int near errno;
extern void far DosPunt(char far *message, ...);
extern void far Punt(char far *message, ...);
extern void far *mem_malloc(unsigned int size, char far *tag);
extern void far mem_free(void far *block);
extern void far *_fmemcpy(void far *destination, const void far *source, unsigned int count);
extern void far *FindIndex(int recIndex, int p2, int p3);
extern struct OpenDB far openDBData[];
extern int far lastTop;


void far OpenIndex(char far *path, int idx);
void far CreateIndex(char far *name, int idx);
void far CloseIndex(int idx);
void far pool_data_fill_B73E(void);
int far DeleteIndex(int recIndex, int b, int c);

#pragma alloc_text(POOLSTUB_TEXT, pool_data_fill_B73E)
#pragma alloc_text(RUN2_TEXT, DeleteIndex)

/* Candidate source for the member being added. */
void far OpenIndex(char far *path, int idx)
{
    char name[100];
    int handle;
    unsigned size;
    void far *buf;

    sprintf(name, "%s.ndx", path);
    openDBData[idx].pad2 = handle = _lopen(name, 2);
    if (handle <= 0)
        DosPunt("Index file missing");
    _lread(handle, &openDBData[idx].recordCount, 20);
    size = openDBData[idx].recordCount << 3;
    buf = mem_malloc(size, name);
    openDBData[idx].indexTable = buf;
    if (buf == 0)
        Punt("Not enough memory to read index file in.");
    _lread(handle, buf, size);
    _lclose(handle);
}


void far CreateIndex(char far *name, int idx)
{
    char buf[100];
    int handle;
    int far *hdr;
    unsigned size;
    void far *data;

    sprintf(buf, "%s.ndx", name);
    handle = _lcreat(buf, 0);
    openDBData[idx].pad2 = handle;
    if (handle <= 0)
        DosPunt("Can't create index file", buf, errno);

    hdr = &openDBData[idx].recordCount;
    hdr[0] = 0; hdr[1] = 0; hdr[2] = 0; hdr[3] = 0; hdr[4] = 0;
    hdr[5] = 0; hdr[6] = 0; hdr[7] = 0; hdr[8] = 0; hdr[9] = 0;

    _lwrite(handle, hdr, 0x14);
    size = (unsigned)(hdr[0] * 8);
    if (hdr[0] != 0) {
        data = mem_malloc(size, "index");
        openDBData[idx].indexTable = data;
    } else {
        openDBData[idx].indexTable = 0;
    }
    _lclose(handle);
}


void far CloseIndex(int idx)
{
    char name[100];
    long count;
    void far *header;
    void far *buf;
    int handle;

    sprintf(name, "%s.ndx", openDBData[idx].name);
    if (openDBData[idx].dirty == 0)
        goto release;
    handle = _lcreat(name, 0);
    openDBData[idx].pad2 = handle;
    if (handle <= 0)
        DosPunt("Index file missing");
    _llseek(handle, 0L, 0);
    header = &openDBData[idx].recordCount;
    _lwrite(handle, header, 20);
    count = openDBData[idx].recordCount;
    if (count != 0)
        _lwrite(handle, openDBData[idx].indexTable, count << 3);
    _lclose(handle);
release:
    buf = openDBData[idx].indexTable;
    if (buf != 0)
        mem_free(buf);
}


void far *FindIndex(int recIndex, int p2, int p3);


/* Lower-bound search; lastTop and lastPos are the original PACK publics. */
void far *FindIndex(int idx, int value, int caste)
{
    extern struct OpenDB __based(__segname("PACK")) openDBData[];
    extern int __based(__segname("PACK")) lastTop;
    extern struct IndexEntry far * __based(__segname("PACK")) lastPos;
    int high;
    int maxIndex;
    int mid;
    unsigned char targetCaste = (unsigned char)caste;

    lastTop = 0;
    high = openDBData[idx].recordCount - 1;
    maxIndex = high;
    if (high >= 0) {
        do {
            mid = (lastTop + high) / 2;
            lastPos = (struct IndexEntry far *)((char far *)openDBData[idx].indexTable + mid * 8);
            if (lastPos->caste > targetCaste ||
                (lastPos->caste == targetCaste && lastPos->value >= value))
                high = mid - 1;
            else
                lastTop = mid + 1;
        } while (lastTop <= high);
    }
    if (lastTop > maxIndex)
        return 0;
    lastPos = (struct IndexEntry far *)((char far *)openDBData[idx].indexTable + lastTop * 8);
    if (lastPos->value == value && lastPos->caste == targetCaste)
        return lastPos;
    return 0;
}


void far DeleteCurrentIndex(int recIndex)
{
    char far *oldBuf;
    char far *newBuf;
    int n;

    oldBuf = openDBData[recIndex].indexTable;
    openDBData[recIndex].recordCount--;
    n = openDBData[recIndex].recordCount;
    if (n < 0)
        Punt("Error-attempt to delete index with there weren't any");
    if (n == 0)
        newBuf = 0;
    else {
        oldBuf = openDBData[recIndex].indexTable;
        newBuf = mem_malloc(n * 8, "record");
        if (newBuf == 0)
            Punt("Not enough memory to delete indices");
        _fmemcpy(newBuf, oldBuf, (unsigned int)(lastTop * 8));
        _fmemcpy(newBuf + lastTop * 8, oldBuf + (lastTop + 1) * 8,
                 (unsigned int)((n - lastTop) * 8));
    }
    openDBData[recIndex].indexTable = newBuf;
    mem_free(oldBuf);
}

/* SCAFFOLD, not recovered source: the 70 bytes of private data between _DeleteCurrentIndex and _DeleteIndex (DGROUP B73E-B784, unclaimed members), copied from the image so the claimed pieces keep their layout. */
void far pool_data_fill_B73E(void)
{
    volatile char far *p;

    p = "\111\104\040\043\040\141\154\162\145\141\144\171\040\160\162\145\163\145\156\164\040\151\156\040\146\151\154\145\000\162\145\143\157\162\144\000\116\157\164\040\145\156\157\165\147\150\040\155\145\155\157\162\171\040\146\157\162\040\156\145\167\040\151\156\144\151\143\145\163";
}

int far DeleteIndex(int recIndex, int b, int c)
{
    void far *newBuf;
    void far *oldBuf;
    int n;

    if (FindIndex(recIndex, b, c) == 0) {
        Punt("ID # not found.");
        return 0;
    }
    openDBData[recIndex].recordCount--;
    n = openDBData[recIndex].recordCount;
    newBuf = mem_malloc(n * 8, "record");
    if (newBuf == 0)
        Punt("Not enough memory for new indices");
    oldBuf = openDBData[recIndex].indexTable;
    _fmemcpy(newBuf, oldBuf, (unsigned int)((lastTop + 1) * 8));
    _fmemcpy((char far *)newBuf + (lastTop + 1) * 8,
             (char far *)oldBuf + (lastTop + 2) * 8,
             (unsigned int)((n - lastTop - 1) * 8));
    mem_free(oldBuf);
    openDBData[recIndex].indexTable = newBuf;
}

