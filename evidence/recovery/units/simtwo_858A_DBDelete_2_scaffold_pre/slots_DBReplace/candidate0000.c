/*
 * DBReplace: replace a record in an open database.  When FindIndex finds
 * the record's index entry (a far pointer whose first long is the
 * record's file offset) the old record is removed exactly as in DBDelete:  The database slot is the
 * far PACK openDBData entry for the handle (0x7c bytes each): its file is
 * positioned 0xe bytes into the record and the ten-byte record header is
 * read so that the header's size word plus ten gives the record length.
 * The current index entry is deleted, the slot's record count drops, its
 * wasted-byte long grows by the record length and its dirty flag is set.
 * The new record is then added with DBAdd.
 *
 * Binding (openDBData record layout, reconciled with DBAdd/DBRecall/DBPack):
 * the PACK array _openDBData starts at 0x7408 with a name/header field;
 * count @0x6c, freeBytes @0x6e, wastedBytes @0x72, file @0x78, dirty @0x7a.
 * Deleting a record therefore grows wastedBytes (es:[+0x747a/0x747c]), and
 * the file handle / dirty flag live at 0x7480 / 0x7482.
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
    char name[0x50];            /* database name / header string */
    void far *indexTable;       /* 0x50 */
    int recordCount;            /* 0x54 */
    unsigned char pad1[0x6c - 0x56];
    int count;                  /* 0x6c: live record count */
    long freeBytes;             /* 0x6e: append position */
    long wastedBytes;           /* 0x72: bytes of deleted records */
    int pad2;                   /* 0x76: not touched by the DB routines */
    int file;                   /* 0x78: DOS file handle */
    int dirty;                  /* 0x7a */
};                              /* 0x7c bytes per slot */

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
        openDBData[handle].wastedBytes += length;
        openDBData[handle].dirty = 1;
    }
    DBAdd(handle, arg4, arg5, arg6, object, type, arg3);
}
