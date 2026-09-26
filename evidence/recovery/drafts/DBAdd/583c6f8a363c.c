/*
 * DBAdd: append a record to an open database, packing the caller's data
 * when it helps.  A "packbuf" allocation (mem_malloc, size = arg6+2,
 * carrying arg6 itself as the id) reserves a 2-byte header plus room for
 * the raw data; PackMemoryToMemory compresses the caller's far data
 * (arg4/arg5, reinterpreted together as one far pointer) into the
 * allocation starting 2 bytes in.  Unless the caller's flags word
 * (arg3, reused as a plain local afterward) has bit 8 set, and the
 * packed size fits in a plain unsigned word and beats the raw size, the
 * packed buffer (tagged with the allocated pointer written into its own
 * first word) is used and arg3 gets bit 0 set; otherwise the caller's
 * raw far pointer and length (arg6) are used unpacked.  The database
 * slot (the far PACK openDBData entry for handle, 0x7c bytes each) gives
 * the file handle and the running free-byte offset; the file is seeked
 * to free-byte+0xe and the ten-byte record header (magic 0x5678/0x1234,
 * the chosen length, a zero word) is written there, followed by the
 * chosen data, and the slot's free-byte long advances by length+0xa.
 * AddIndex records the new record's offset for (handle, object, type,
 * arg3) and the slot's dirty flag is set.  The packbuf allocation is
 * freed before returning.
 */
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

extern struct OpenDB far openDBData[];

extern void far *mem_malloc(unsigned size, char far *tag);
extern void far mem_free(void far *block);
extern long far PackMemoryToMemory(unsigned size, void far *src, void far *dest);
extern void far AddIndex(int handle, int object, int type, int flags, long offset);
extern long far pascal _llseek(int file, long offset, int origin);
extern int far pascal _lwrite(int file, void far *buffer, unsigned count);

void far DBAdd(int handle, int arg4, int arg5, int arg6, int object, int type,
              int arg3)
{
    void far *data;
    void far *packed;
    long packedSize;
    void far *chosen;
    int chosenLen;
    int file;
    long freeBytes;
    unsigned header[5];

    data = *(void far **)&arg4;
    packedSize = PackMemoryToMemory((unsigned)arg6, data, (void far *)((char far *)(packed = mem_malloc((unsigned)(arg6 + 2), "packbuf")) + 2));

    if ((arg3 & 8) == 0 && packedSize >= 0 && packedSize < arg6) {
        *(int far *)packed = arg6;
        chosen = packed;
        chosenLen = (int)packedSize + 2;
        arg3 |= 1;
    } else {
        chosen = data;
        chosenLen = arg6;
        arg3 &= ~1;
    }

    file = openDBData[handle].file;
    ++openDBData[handle].count;

    header[0] = 0x5678;
    header[1] = 0x1234;
    header[2] = 0;
    header[3] = (unsigned)chosenLen;
    header[4] = 0;

    freeBytes = openDBData[handle].freeBytes;
    _llseek(file, freeBytes + 0xe, 0);
    _lwrite(file, header, 0xa);
    _lwrite(file, chosen, chosenLen);

    openDBData[handle].freeBytes = freeBytes + chosenLen + 0xa;

    AddIndex(handle, object, type, arg3, freeBytes);

    openDBData[handle].dirty = 1;

    mem_free(packed);
}
