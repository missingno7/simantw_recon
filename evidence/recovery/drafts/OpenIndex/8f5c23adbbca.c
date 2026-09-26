/* R1 controlled residue hypothesis. */
/* Open the slot's index file and install its loaded table in openDBData. */
struct OpenIndexRec {
    char name[0x50];
    void far *indexTable;
    int recordCount;
    unsigned char pad1[0x20];
    int handle;
    unsigned char pad2[4];
};
extern struct OpenIndexRec far openDBData[];
extern int far sprintf(char far *buffer, char far *format, ...);
extern int far pascal _lopen(char far *path, int mode);
extern long far pascal _lread(int handle, void far *buffer, unsigned count);
extern int far pascal _lclose(int handle);
extern void far Punt(char far *message, ...);
extern void far DosPunt(char far *message);
extern void far *mem_malloc(unsigned int size, char far *tag);

void far OpenIndex(int p1, int p2, int idx)
{
    char name[100];
    int handle;
    int recordIndex = idx;
    unsigned size;
    void far *buf;

    sprintf(name, "index%d.%d", p1, p2);
    handle = _lopen(name, 2);
    openDBData[recordIndex].handle = handle;
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
