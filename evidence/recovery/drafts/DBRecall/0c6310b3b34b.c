/*
 * DBRecall: fetch a record from an open database, decompressing it if the
 * index entry says it is packed.  FindIndex(handle,object,type) locates
 * the index entry (the same DBIndexEntry offset field DBDelete/DBReplace
 * use); a miss zeroes *size and returns 0.  The database slot gives the
 * file handle; the file is seeked to entry->offset+0xe and the ten-byte
 * record header (DBRecordHeader: id,type,flags,size,extra) is read, its
 * size word driving mem_Alloc("rrecall:%c%d",...) for a raw read buffer.
 * If the index entry's flag byte (offset 7, matching the flags DBAdd
 * writes into the index) has bit 0 clear, the (still-empty) buffer is
 * returned as-is.  With bit 0 set and bit 2 also set, the record is
 * already a plain literal: the read buffer's data slides right two bytes
 * (memmove) to make room for a 0xffff no-compression marker written at
 * its head and the reported size grows by two.  With bit 0 set and bit 2
 * clear, the buffer's leading word is the true uncompressed size; a
 * second mem_Alloc("recall:%c%d",...) reserves that, UnpackInit primes
 * the decompressor over the packed bytes (skipping the 2-byte size
 * prefix), Unpack decompresses into the new buffer (a WinPrintf warning
 * fires if the result doesn't match the expected size), and the raw read
 * buffer is unlocked and freed in favour of the unpacked one.  Either
 * way the final buffer is unlocked, *size is set and its handle
 * returned.
 */
struct DBIndexEntry {
    long offset;
    unsigned char pad[3];
    unsigned char flags;
};

struct DBRecordHeader {
    int id;
    int type;
    int flags;
    int size;
    int extra;
};

struct OpenDB {
    int count;
    long freeBytes;
    unsigned char pad1[6];
    int file;
    int dirty;
    unsigned char pad2[0x7c - 0x10];
};

extern struct OpenDB far openDBData[];

extern struct DBIndexEntry far *FindIndex(int handle, int object, int type);
extern long far pascal _llseek(int file, long offset, int origin);
extern int far pascal _lread();
extern int far sprintf(char far *buffer, char far *format, ...);
extern unsigned int far mem_Alloc(unsigned long bytes, int kind, char far *name);
extern void far Punt(char far *message, ...);
extern void far *mem_Lock(unsigned int handle);
extern int far mem_Unlock(unsigned int handle);
extern void far mem_Free(int handle);
extern void far memmove(void far *dst, void far *src, unsigned n);
extern void near UnpackInit(void far *packed, unsigned length);
extern int near Unpack(void far *dest);
extern void far WinPrintf(char far *format, ...);

int far DBRecall(int handle, int object, int type, int far *size)
{
    struct DBIndexEntry far * volatile entry;
    struct DBRecordHeader header;
    int file;
    int length;
    char buf[0x20];
    unsigned bufHandle;
    void far *buf2;
    int expected;
    int unpackHandle;

    *size = 0;
    entry = FindIndex(handle, object, type);
    if (entry == 0)
        return 0;

    file = openDBData[handle].file;
    _llseek(file, entry->offset + 0xe, 0);
    _lread(file, &header, 0xa);
    length = header.size;

    sprintf(buf, "rrecall:%c%d", type + 0x61, object);
    bufHandle = mem_Alloc((unsigned long)(length + 3), 0, buf);
    if (bufHandle == 0)
        Punt("Couldn't allocate a buffer for DBRecall");

    buf2 = mem_Lock(bufHandle);
    _lread(buf2, length);

    if (entry->flags & 1) {
        if (entry->flags & 4) {
            memmove((char far *)buf2 + 2, buf2, length);
            *(unsigned far *)buf2 = 0xffff;
            length += 2;

        } else {
            expected = *(int far *)buf2;
            sprintf(buf, "recall:%c%d", type + 0x61, object);
            unpackHandle = mem_Alloc((unsigned long)expected, 0, buf);
            UnpackInit((char far *)buf2 + 2, length - 2);
            if (Unpack(mem_Lock(unpackHandle)) != expected)
                WinPrintf("\a\aDBRecall Unpack error!!! - object=%d, type=%d",
                          object, type);
            mem_Unlock(bufHandle);
            mem_Free(bufHandle);
            bufHandle = unpackHandle;
            length = expected;
        }
    } else {

    }

    mem_Unlock(bufHandle);
    *size = length;
    return bufHandle;
}
