/* Open the path's index file and install its loaded table in openDBData. */
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
extern void far DosPunt(char far *message, ...);
extern void far *mem_malloc(unsigned int size, char far *tag);

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
