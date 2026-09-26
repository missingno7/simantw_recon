
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


/* Zero and write the 20-byte index header stored in an OpenDB PACK row. */
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
