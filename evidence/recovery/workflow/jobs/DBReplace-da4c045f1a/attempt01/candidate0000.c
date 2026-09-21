/*
 * DBReplace: replace a record in an open database.  When FindIndex finds
 * the record's index entry (a far pointer whose first long is the
 * record's file offset) the old record is removed exactly as in DBDelete:  The database slot is the
 * far PACK openDBData entry for the handle (0x7c bytes each): its file is
 * positioned 0xe bytes into the record and the ten-byte record header is
 * read so that the header's size word plus ten gives the record length.
 * The current index entry is deleted, the slot's record count drops, its
 * free-byte long grows by the record length and its dirty flag is set.
 * The new record is then added with DBAdd.
 */
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
extern void far DBAdd(int handle, int arg4, int arg5, int arg6, int object, int type, int arg3);
extern long far pascal _llseek(int file, long offset, int origin);
extern int far pascal _lread(int file, void far *buffer, int bytes);

void far DBReplace(int handle, int arg4, int arg5, int arg6, int object, int type, int arg3)
{
    struct DBIndexEntry far *entry;
    int file;
    struct DBRecordHeader header;
    unsigned int length;

    entry = FindIndex(handle, object, type);
    if (entry != 0) {
        file = openDBData[handle].file;
        _llseek(file, entry->offset + 0xe, 0);
        _lread(file, &header, sizeof(header));
        length = header.size + sizeof(header);
        DeleteCurrentIndex(handle);
        openDBData[handle].count--;
        openDBData[handle].freeBytes += length;
        openDBData[handle].dirty = 1;
    }
    DBAdd(handle, arg4, arg5, arg6, object, type, arg3);
}
