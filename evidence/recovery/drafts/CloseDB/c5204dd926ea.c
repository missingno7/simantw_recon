struct OpenDB {
    char name[0x50];
    void far *indexTable;
    int recordCount;
    unsigned char pad[0x16];
    int count;
    long freeBytes;
    long wastedBytes;
    int pad2;
    int file;
    int dirty;
};
extern volatile int far match_position[];
extern volatile struct OpenDB __based(__segname("PACK")) openDBData[4];
extern long far pascal _llseek(int handle, long offset, int origin);
extern long far pascal _lwrite(int handle, void far *buffer, unsigned count);
extern int far pascal _lclose(int handle);
extern void far CloseIndex(int index);

volatile void CloseDB(int index)
{
    int record;
    int handle;

    record = index;
    record *= 0x7c;
    handle = *(volatile int far *)((char far *)match_position + record + 0x7480);
    if (*(volatile int far *)((char far *)match_position + record + 0x7482) != 0) {
        _llseek(handle, 0L, 0);
        _lwrite(handle, (void far *)((char far *)match_position + record + 0x7470), 0x0e);
        _lclose(handle);
        CloseIndex(index);
        openDBData[index].dirty = 0;
    }
}
