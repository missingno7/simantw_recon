
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
extern void near DosPunt(char far *message, ...);
extern void far Punt(char far *message, ...);
extern void far *mem_malloc(unsigned int size, char far *tag);
extern void far mem_free(void far *block);
extern void far *_fmemcpy(void far *destination, const void far *source, unsigned int count);
extern void far *FindIndex(int recIndex, int p2, int p3);
extern struct OpenDB far openDBData[];
extern int far lastTop;


/* Flush and release the index buffer in an OpenDB PACK row. */
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
