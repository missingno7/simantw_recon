/*
 * DBDelete: remove a record from an open database.  FindIndex locates the
 * record's index entry (a far pointer whose first long is the record's
 * file offset); a missing entry returns 0.  The database slot is the
 * far PACK openDBData entry for the handle (0x7c bytes each): its file is
 * positioned 0xe bytes into the record and the ten-byte record header is
 * read so that the header's size word plus ten gives the record length.
 * The current index entry is deleted, the slot's record count drops, its
 * free-byte long grows by the record length and its dirty flag is set;
 * the result is 1.
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
};

extern struct OpenDB far openDBData[];

extern struct DBIndexEntry far *FindIndex(int handle, int a, int b);
extern void far DeleteCurrentIndex(int handle);
extern long far pascal _llseek(int file, long offset, int origin);
extern int far pascal _lread(int file, void far *buffer, int bytes);

int far DBDelete(int handle, int a, int b)
{
    struct DBIndexEntry far *entry;
    struct OpenDB far *db;
    int file;
    struct DBRecordHeader header;
    unsigned int length;

    entry = FindIndex(handle, a, b);
    if (entry == 0)
        return 0;
    db = &openDBData[handle];
    file = db->file;
    _llseek(file, entry->offset + 0xe, 0);
    _lread(file, &header, sizeof(header));
    length = header.size + sizeof(header);
    DeleteCurrentIndex(handle);
    db->count--;
    db->freeBytes += length;
    db->dirty = 1;
    return 1;
}
