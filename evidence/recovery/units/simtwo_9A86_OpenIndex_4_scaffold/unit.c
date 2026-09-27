/* Candidate translation unit simtwo_9A86_OpenIndex_4_scaffold: composed from preserved exact-body sources
 * in MAPSYM order. Internal evidence id, not a historical filename.
 * Members: _OpenIndex, _CreateIndex, _DeleteCurrentIndex, _DeleteIndex
 * SCAFFOLDED: claimed members in 3 code runs; no pool stand-ins were needed. */

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
extern void far Punt(char far *message, ...);
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
extern void far mem_free(void far *block);
extern void far *_fmemcpy(void far *destination, const void far *source, unsigned int count);
extern void far *FindIndex(int recIndex, int p2, int p3);
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
extern struct OpenDB_2 far openDBData[];


void far pool_data_fill_B6C4(void);
void far pool_data_fill_B73E(void);
void far DeleteCurrentIndex(int recIndex);
int far DeleteIndex(int recIndex, int b, int c);

#pragma alloc_text(POOLSTUB_TEXT, pool_data_fill_B6C4)
#pragma alloc_text(POOLSTUB_TEXT, pool_data_fill_B73E)
#pragma alloc_text(RUN2_TEXT, DeleteCurrentIndex)
#pragma alloc_text(RUN3_TEXT, DeleteIndex)

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

#define openDBData ((struct OpenDB far *)openDBData)  /* shape view of the unit declaration for this member only */
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
#undef openDBData

/* SCAFFOLD, not recovered source: the 26 bytes of private data between _CreateIndex and _DeleteCurrentIndex (DGROUP B6C4-B6DE, unclaimed members), copied from the image so the claimed pieces keep their layout. */
void far pool_data_fill_B6C4(void)
{
    volatile char far *p;

    p = "\045\163\056\156\144\170\000\111\156\144\145\170\040\146\151\154\145\040\155\151\163\163\151\156\147";
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

