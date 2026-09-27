/* Reviewed incremental unit source: OpenIndex/CreateIndex/CloseIndex/FindIndex/AddIndex candidates plus admitted delete controls.
 * MAPSYM code order; all seven index bodies are now present for object-context testing. */

struct OpenDB {
    char name[0x50];
    void far *indexTable;
    int recordCount;
    int headerWords[9];
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

void far OpenIndex(char far *path, int idx);

void far CreateIndex(char far *name, int idx);

void far CloseIndex(int idx);

int far AddIndex(int recIndex, int p2, int p3, int p4, void far *payload);

int far DeleteIndex(int recIndex, int b, int c);

/* Reviewed layout stand-ins preserve private strings owned by unclaimed
 * _CreateIndex and _CloseIndex. Their code stays outside the claimed runs. */

void far pool_data_fill_CreateIndex(void);

void far pool_data_fill_CloseIndex(void);

void far pool_data_fill_B73E(void);

void far DeleteCurrentIndex(int recIndex);

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
