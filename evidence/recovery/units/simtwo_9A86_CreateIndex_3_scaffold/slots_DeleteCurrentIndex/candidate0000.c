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

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _OpenIndex.
 * It only reproduces the object's selector-pool allocation order for the
 * words C68C; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */

/* SCAFFOLD, not recovered source: the 70 bytes of private data between _DeleteCurrentIndex and _DeleteIndex (DGROUP B73E-B784, unclaimed members), copied from the image so the claimed pieces keep their layout. */

void far DeleteCurrentIndex(int recIndex)
{
    char far *oldBuf;
    char far *newBuf;
    int n;

    oldBuf = openDBData[recIndex].indexTable;
    openDBData[recIndex].header.recordCount--;
    n = openDBData[recIndex].header.recordCount;
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
