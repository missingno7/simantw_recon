/*
 * DBPack: compact an open database by rewriting it to a temp file and
 * swapping it into place.  The slot's wasted-byte count (a long at
 * offset 0x22 within the 0x7c-byte PACK record, immediately after the
 * append-position freeBytes long at 0x1e) is reported via WinPrintf,
 * then "dbtmp.x00" is _lcreat'd for writing (Punt on failure).  A
 * "buf" pack buffer is mem_malloc'd 0xfde8 (a large fixed size) bytes
 * (Punt on failure) and its DOS handle stored in a 10-byte record header
 * written first via _lwrite.  The slot's index table (a far pointer at
 * offset 0) and record count (a word at offset 4) drive a loop over
 * every index entry: each entry's stored file offset is seeked to
 * (+0xe) and its ten-byte record header read; the record's declared
 * size is read again from the header, the whole record is _lread from
 * the original file and _lwrite'n into the temp file at the running
 * temp-file offset, that offset is written back into the (still live)
 * index entry in place, and the running offset and loop counter
 * advance.  On completion, the original database file and pack buffer
 * are closed/freed, "dbtmp.x00" is renamed over "%s.dat" (the
 * database's own stored name), reopened for read/write, and the slot's
 * file handle is updated, freeBytes reduced by the wasted-byte total,
 * wastedBytes reset to zero, and dirty set.
 */
struct OpenDB {
    char name[0x50];
    void far *indexTable;
    int recordCount;
    unsigned char pad1[0x6c - 0x56];
    int count;
    long freeBytes;
    long wastedBytes;
    int pad;
    int file;
    int dirty;
};

struct DBIndexEntry {
    long offset;
    unsigned char pad[4];
};

struct DBRecordHeader {
    int id;
    int type;
    int flags;
    int size;
    int extra;
};

struct DBFileHeader {
    int magic1;
    int magic2;
    int recordCount;
    int reserved[4];
};

extern struct OpenDB far openDBData[];

extern void far WinPrintf(char far *format, ...);
extern void far Punt(char far *message, ...);
extern int far sprintf(char far *buffer, char far *format, ...);
extern void far *mem_malloc(unsigned size, char far *tag);
extern void far mem_free(void far *block);
extern long far pascal _lcreat(char far *path, int attrib);
extern long far pascal _llseek(int file, long offset, int origin);
extern int far pascal _lread(int file, void far *buffer, unsigned count);
extern int far pascal _lwrite(int file, void far *buffer, unsigned count);
extern int far pascal _lclose(int file);
extern long far pascal _lopen(char far *path, int mode);
extern int far unlink(char far *path);
extern int far rename(char far *oldPath, char far *newPath);

int far DBPack(int handle)
{
    long wasted;
    long tmpFile;
    void far *buf;
    struct DBRecordHeader header;
    struct DBFileHeader fileHeader;
    struct DBIndexEntry far *index;
    struct DBIndexEntry far *indexEnd;
    int count;
    long tmpOffset;
    long recordOffset;
    int file;
    char nameBuf[20];

    wasted = openDBData[handle].wastedBytes;
    WinPrintf("\nPacking database - %ld bytes currently wasted", wasted);

    tmpFile = _lcreat("dbtmp.x00", 0);
    if ((int)tmpFile <= 0)
        Punt("Cannot open temp pack file");

    buf = mem_malloc(0xfde8, "buf");
    if (buf == 0)
        Punt("Cannot allocate pack buffer");

    fileHeader.magic1 = 0x5678;
    fileHeader.magic2 = 0x1234;
    fileHeader.recordCount = openDBData[handle].recordCount;
    _lwrite((int)tmpFile, &fileHeader, 0xe);

    file = openDBData[handle].file;
    index = (struct DBIndexEntry far *)openDBData[handle].indexTable;
    count = openDBData[handle].recordCount;
    tmpOffset = 0;
    while (count != 0) {
        recordOffset = index->offset;
        _llseek(file, recordOffset + 0xe, 0);
        _lread(file, &header, 0xa);
        _lread(file, buf, header.size);
        WinPrintf("\nmoving %6u bytes from %8ld to %8ld", header.size, recordOffset, tmpOffset);
        _lwrite((int)tmpFile, &header, 0xa);
        _lwrite((int)tmpFile, buf, header.size);
        index->offset = tmpOffset;
        tmpOffset += header.size + 0xa;
        ++index;
        --count;
    }

    sprintf(nameBuf, "%s.dat", openDBData[handle].name);
    _lclose(file);
    _lclose((int)tmpFile);
    unlink(nameBuf);
    mem_free(buf);
    rename("dbtmp.x00", nameBuf);

    tmpFile = _lopen(nameBuf, 2);
    openDBData[handle].file = (int)tmpFile;
    openDBData[handle].freeBytes -= wasted;
    openDBData[handle].wastedBytes = 0;
    openDBData[handle].dirty = 1;

    return 1;
}

/* Walk the computed one-past-end index entry with a pointer limit. */
