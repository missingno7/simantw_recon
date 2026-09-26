/* Candidate translation unit simtwo_9A86: composed from preserved exact-body sources
 * in MAPSYM order. Internal evidence id, not a historical filename.
 * Members: _OpenIndex, _CreateIndex, _CloseIndex, _FindIndex, _DeleteCurrentIndex, _AddIndex, _DeleteIndex */

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

void far OpenIndex(char far *path, int idx)
{
    char name[100];
    int handle;
    unsigned size;
    void far *buf;

    sprintf(name, "%s.ndx", path);
    openDBData[idx].pad2 = handle = _lopen(name, 2);
    if (handle <= 0)
        DosPunt("Can't open index file");
    _lread(handle, &openDBData[idx].recordCount, 20);
    size = openDBData[idx].recordCount << 3;
    buf = mem_malloc(size, name);
    openDBData[idx].indexTable = buf;
    if (buf == 0)
        Punt("Out of memory");
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

int far AddIndex(int recIndex, int p2, int p3, int p4, void far *payload)
{
    void far * volatile oldBuf;
    void far *newBuf;
    struct IndexEntry entry;
    int n;

    oldBuf = openDBData[recIndex].indexTable;
    if (FindIndex(recIndex, p2, p3) != 0) {
        Punt("ID # already present in file");
        return 0;
    }
    entry.value = p2;
    entry.caste = (unsigned char)p3;
    entry.kind = (unsigned char)p4;
    entry.payload = payload;

    openDBData[recIndex].recordCount++;
    n = openDBData[recIndex].recordCount;
    newBuf = mem_malloc(n * 8, "record");
    if (newBuf == 0)
        Punt("Not enough memory for new indices");

    if (openDBData[recIndex].recordCount == 1) {
        if (oldBuf != 0)
            mem_free(oldBuf);
        *(struct IndexEntry far *)newBuf = entry;
    } else {
        oldBuf = openDBData[recIndex].indexTable;
        _fmemcpy(newBuf, oldBuf, (unsigned int)(lastTop * 8));
        *(struct IndexEntry far *)((char far *)newBuf + lastTop * 8) = entry;
        _fmemcpy((char far *)newBuf + (lastTop + 1) * 8,
                 (char far *)oldBuf + lastTop * 8,
                 (unsigned int)((n - lastTop - 1) * 8));
        mem_free(oldBuf);
    }
    openDBData[recIndex].indexTable = newBuf;
    return 1;
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

