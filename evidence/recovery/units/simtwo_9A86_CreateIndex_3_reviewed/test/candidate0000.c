/* Candidate translation unit simtwo_9A86_DeleteCurrentIndex_2_scaffold: composed from preserved exact-body sources
 * in MAPSYM order. Internal evidence id, not a historical filename.
 * Members: _DeleteCurrentIndex, _DeleteIndex
 * SCAFFOLDED: unclaimed members _OpenIndex are stand-ins in POOLSTUB_TEXT (pool order only, never compared). */

struct IndexFileHeader {
    int recordCount;
    int words[9];
};
struct OpenDB {
    char name[0x50];
    void far *indexTable;
    struct IndexFileHeader indexHeader;
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


void far pool_stub_OpenIndex(void);
void far pool_data_fill_B73E(void);
int far DeleteIndex(int recIndex, int b, int c);



/* Reviewed stand-ins preserve the unclaimed OpenIndex selector and its
 * private strings, plus CloseIndex's strings, in MAPSYM order. */
void far CreateIndex(char far *name, int idx);
void far DeleteCurrentIndex(int recIndex);
void far pool_data_fill_OpenIndex(void);
void far pool_data_fill_CloseIndex(void);
void far pool_stub_OpenIndex(void);
void far pool_data_fill_B73E(void);

#pragma alloc_text(POOLSTUB_TEXT, pool_stub_OpenIndex, pool_data_fill_OpenIndex, pool_data_fill_CloseIndex, pool_data_fill_B73E)
#pragma alloc_text(RUN2_TEXT, DeleteCurrentIndex)
#pragma alloc_text(RUN3_TEXT, DeleteIndex)

void far pool_stub_OpenIndex(void)
{
    volatile int t;

    t = *(int far *)openDBData;
}


void far pool_data_fill_OpenIndex(void)
{
    volatile char far *p;
    p = "%s.ndx";
    p = "Index file missing";
    p = "Not enough memory to read index file in.";
}

void far CreateIndex(char far *name, int idx)
{
    char buf[100];
    int handle;
    int far *header;
    unsigned size;

    sprintf(buf, "%s.ndx", name);
    handle = openDBData[idx].pad2 = _lcreat(buf, 0);
    if (handle <= 0)
        DosPunt("Can't create index file", buf, errno);

    openDBData[idx].indexHeader.recordCount = 0;
    openDBData[idx].indexHeader.words[0] = 0;
    openDBData[idx].indexHeader.words[2] = 0;
    openDBData[idx].indexHeader.words[1] = 0;
    openDBData[idx].indexHeader.words[4] = 0;
    openDBData[idx].indexHeader.words[3] = 0;
    openDBData[idx].indexHeader.words[6] = 0;
    openDBData[idx].indexHeader.words[5] = 0;
    openDBData[idx].indexHeader.words[7] = 0;
    openDBData[idx].indexHeader.words[8] = 0;

    header = &openDBData[idx].indexHeader.recordCount;
    _lwrite(handle, header, 0x14);
    size = (unsigned)(openDBData[idx].indexHeader.recordCount * 8);
    if (size != 0) {
        openDBData[idx].indexTable = mem_malloc(size, "index");
    } else {
        openDBData[idx].indexTable = 0;
    }
    _lclose(handle);
}


void far pool_data_fill_CloseIndex(void)
{
    volatile char far *p;
    p = "%s.ndx";
    p = "Index file missing";
}

void far DeleteCurrentIndex(int recIndex)
{
    char far *oldBuf;
    char far *newBuf;
    int n;

    oldBuf = openDBData[recIndex].indexTable;
    openDBData[recIndex].indexHeader.recordCount--;
    n = openDBData[recIndex].indexHeader.recordCount;
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
    openDBData[recIndex].indexHeader.recordCount--;
    n = openDBData[recIndex].indexHeader.recordCount;
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