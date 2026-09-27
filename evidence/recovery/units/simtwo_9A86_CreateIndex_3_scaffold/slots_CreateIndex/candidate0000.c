/* Candidate translation unit simtwo_9A86_DeleteCurrentIndex_2_scaffold: composed from preserved exact-body sources
 * in MAPSYM order. Internal evidence id, not a historical filename.
 * Members: _DeleteCurrentIndex, _DeleteIndex
 * SCAFFOLDED: unclaimed members _OpenIndex are stand-ins in POOLSTUB_TEXT (pool order only, never compared). */

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
