/* Candidate translation unit simtwo_858A_DBDelete_1: composed from preserved exact-body sources
 * in MAPSYM order. Internal evidence id, not a historical filename.
 * Members: _DBDelete */

struct DBIndexEntry {
    long offset;
};
struct DBRecordHeader {
    int id;
    int type;
    int flags;
    int size;
    int extra;
};
struct OpenDB {
    unsigned char header[0x6c];
    int count;
    int pad[2];
    long freeBytes;
    int file;
    int dirty;
    int tail;
};
extern struct OpenDB far openDBData[];
extern struct DBIndexEntry far *FindIndex(int handle, int a, int b);
extern void far DeleteCurrentIndex(int handle);
extern long far pascal _llseek(int file, long offset, int origin);
extern int far pascal _lread(int file, void far *buffer, int bytes);

int far DBDelete(int handle, int a, int b)
{
    struct DBIndexEntry far *entry;
    int file;
    struct DBRecordHeader header;
    unsigned int length;

    entry = FindIndex(handle, a, b);
    if (entry == 0)
        return 0;
    file = openDBData[handle].file;
    _llseek(file, entry->offset + 0xe, 0);
    _lread(file, &header, sizeof(header));
    length = header.size + sizeof(header);
    DeleteCurrentIndex(handle);
    openDBData[handle].count--;
    openDBData[handle].freeBytes += length;
    openDBData[handle].dirty = 1;
    return 1;
}

