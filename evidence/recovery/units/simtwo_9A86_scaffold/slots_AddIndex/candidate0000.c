
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


/* Insert a sorted eight-byte entry into the current slot's index buffer. */
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
