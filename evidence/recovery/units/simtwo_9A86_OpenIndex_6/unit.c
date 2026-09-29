/* Candidate translation unit simtwo_9A86_OpenIndex_6: composed from preserved exact-body sources
 * in MAPSYM order. Internal evidence id, not a historical filename.
 * Members: _OpenIndex, _CreateIndex, _CloseIndex, _FindIndex, _DeleteCurrentIndex, _AddIndex */

struct OpenIndexRec {
    char name[0x50];
    void far *indexTable;
    int recordCount;
    unsigned char pad1[0x20];
    int handle;
    unsigned char pad2[4];
};
extern int far sprintf(char far *buffer, char far *format, ...);
extern int far pascal _lopen(char far *path, int mode);
extern long far pascal _lread(int handle, void far *buffer, unsigned count);
extern int far pascal _lclose(int handle);
extern void far Punt(char far *message);
extern void far DosPunt(char far *message, ...);
extern void far *mem_malloc(unsigned int size, char far *tag);
struct IndexHeader {
    int recordCount;
    int field2;
    long stat1;
    long stat2;
    long stat3;
    int field8;
    int field9;
};
struct OpenDB {
    char name[0x50];
    void far *indexTable;
    struct IndexHeader header;
    unsigned char pad1[4];
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
extern int far pascal _lcreat(char far *path, int attrib);
extern long far pascal _lwrite(int handle, void far *buffer, unsigned count);
extern long far pascal _llseek(int handle, long offset, int origin);
extern int near errno;
extern void mem_free(void far *block);
extern void far *_fmemcpy(void far *destination, const void far *source, unsigned int count);
extern void far *FindIndex(int recIndex, int p2, int p3);
extern struct OpenDB far openDBData[];
extern int far lastTop;
void far pool_stub_OpenIndex(void);
void far pool_data_fill_B73E(void);
int far DeleteIndex(int recIndex, int b, int c);
void far CreateIndex(char far *name, int idx);
void far DeleteCurrentIndex(int recIndex);
void far pool_data_fill_OpenIndex(void);
void far pool_data_fill_CloseIndex(void);
struct OpenDB_2 {
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
extern struct IndexEntry far * far lastPos;
struct IndexRec {
    void far *data;
    int count;
    char pad[124 - 6];
};
struct IndexEntry_2 {
    void far *payload;
    int p2;
    unsigned char p3;
    unsigned char p4;
};
union OldBufferLifetime {
    void far * volatile initial;
    void far *current;
};
extern char far match_position[];
extern void far *memcpy(void far *dst, const void far *src, unsigned int count);

#define openDBData ((struct OpenIndexRec far *)openDBData)  /* shape view of the unit declaration for this member only */
void far OpenIndex(char far *path, int idx)
{
    char name[100];
    int handle;
    int recordIndex = idx;
    unsigned size;
    void far *buf;

    sprintf(name, "%s.ndx", path);
    handle = openDBData[recordIndex].handle = _lopen(name, 2);
    if (handle <= 0)
        DosPunt("Index file missing");
    _lread(handle, &openDBData[idx].recordCount, 20);
    size = openDBData[idx].recordCount << 3;
    buf = (openDBData[idx].indexTable = mem_malloc(size, name));
    if (buf == 0)
        Punt("Not enough memory to read index file in.");
    _lread(handle, buf, size);
    _lclose(handle);
}
#undef openDBData

void far CreateIndex(char far *name, int idx)
{
    char buf[100];
    int handle;
    struct IndexHeader far *header;
    unsigned size;

    sprintf(buf, "%s.ndx", name);
    handle = openDBData[idx].pad2 = _lcreat(buf, 0);
    if (handle <= 0)
        DosPunt("Can't create index file", buf, errno);

    openDBData[idx].header.recordCount = 0;
    openDBData[idx].header.field2 = 0;
    openDBData[idx].header.stat1 = 0;
    openDBData[idx].header.stat2 = 0;
    openDBData[idx].header.stat3 = 0;
    openDBData[idx].header.field8 = 0;
    openDBData[idx].header.field9 = 0;

    header = &openDBData[idx].header;
    _lwrite(handle, header, 0x14);
    size = (unsigned)(openDBData[idx].header.recordCount * 8);
    if (size != 0) {
        openDBData[idx].indexTable = mem_malloc(size, "index");
    } else {
        openDBData[idx].indexTable = 0;
    }
    _lclose(handle);
}

#define openDBData ((struct OpenDB_2 far *)openDBData)  /* shape view of the unit declaration for this member only */
void far CloseIndex(int idx)
{
  char name[100];
  void far *header;
  volatile void *buf;
  int handle;
  sprintf(name, "%s.ndx", openDBData[idx].name);
  if (openDBData[idx].dirty == 0)
    goto release;
  handle = (openDBData[idx].pad2 = _lcreat(name, 0));
  if (handle <= 0)
    DosPunt("Index file missing");
  _llseek(handle, 0L, 0);
  header = &openDBData[idx].recordCount;
  _lwrite(handle, header, 20);
  if (openDBData[idx].recordCount != 0)
    _lwrite(handle, openDBData[idx].indexTable, openDBData[idx].recordCount << 3);
  _lclose(handle);
  release:
  if (openDBData[idx].indexTable != 0)
    mem_free(openDBData[idx].indexTable);
}
#undef openDBData

void far *FindIndex(int idx, int value, int caste)
{
    int high;
    int maxIndex;
    int mid;

    lastTop = 0;
    high = openDBData[idx].header.recordCount - 1;
    maxIndex = high;
    if (high == -1)
        return 0;
    if (high >= 0) {
        do {
            mid = (lastTop + high) / 2;
            lastPos = (struct IndexEntry far *)((char far *)openDBData[idx].indexTable + mid * 8);
            if (lastPos->caste > caste ||
                (lastPos->caste == caste && lastPos->value >= value))
                high = mid - 1;
            else
                lastTop = mid + 1;
        } while (lastTop <= high);
    }
    if (lastTop > maxIndex)
        return 0;
    lastPos = (struct IndexEntry far *)((char far *)openDBData[idx].indexTable + lastTop * 8);
    if (lastPos->value == value && lastPos->caste == caste)
        return lastPos;
    return 0;
}

#define openDBData ((struct OpenDB_2 far *)openDBData)  /* shape view of the unit declaration for this member only */
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
#undef openDBData

int far AddIndex(int recIndex, int p2, int p3, int p4, void far *payload)
{
    union OldBufferLifetime oldBuffer;
    void far *newBuf;
    struct IndexEntry_2 entry;
    int n;
    int k;

    oldBuffer.initial = ((struct IndexRec far *)(match_position + 0x7458))[recIndex].data;

    if (FindIndex(recIndex, p2, p3) != 0) {
        Punt("AddIndex: duplicate index");
        return 0;
    }

    entry.p2 = p2;
    entry.p3 = (unsigned char)p3;
    entry.p4 = (unsigned char)p4;
    entry.payload = payload;

    ((struct IndexRec far *)(match_position + 0x7458))[recIndex].count++;
    n = ((struct IndexRec far *)(match_position + 0x7458))[recIndex].count;

    newBuf = mem_malloc(n * 8, "AddIndex");
    if (newBuf == 0)
        Punt("AddIndex: out of memory");

    if (((struct IndexRec far *)(match_position + 0x7458))[recIndex].count == 1) {
        if (oldBuffer.initial != 0)
            mem_free(oldBuffer.initial);
        *(struct IndexEntry_2 far *)newBuf = entry;
    } else {
        oldBuffer.current = ((struct IndexRec far *)(match_position + 0x7458))[recIndex].data;

        memcpy((unsigned char far *)newBuf, (unsigned char far *)oldBuffer.current, lastTop * 8);

        *(struct IndexEntry_2 far *)((unsigned char far *)newBuf + lastTop * 8) = entry;

        memcpy((unsigned char far *)newBuf + (lastTop + 1) * 8, (unsigned char far *)oldBuffer.current + lastTop * 8, (n - lastTop - 1) * 8);

        mem_free(oldBuffer.current);
    }

    ((struct IndexRec far *)(match_position + 0x7458))[recIndex].data = newBuf;
    return 1;
}

