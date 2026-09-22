/* Candidate translation unit simtwo_858A_DBDelete_2_scaffold: composed from preserved exact-body sources
 * in MAPSYM order. Internal evidence id, not a historical filename.
 * Members: _DBDelete, _DBReplace
 * SCAFFOLDED: unclaimed members _DBAdd are stand-ins in POOLSTUB_TEXT (pool order only, never compared). */

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
extern void far DBAdd(int handle, int arg4, int arg5, int arg6, int object, int type, int arg3);


void far pool_stub_DBAdd(void);
void far DBReplace(int handle, int arg4, int arg5, int arg6, int object, int type, int arg3);

#pragma alloc_text(POOLSTUB_TEXT, pool_stub_DBAdd)
#pragma alloc_text(RUN2_TEXT, DBReplace)

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _DBAdd.
 * It only reproduces the object's selector-pool allocation order for the
 * words C688; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_DBAdd(void)
{
    volatile int t;

    t = *(int far *)openDBData;
}

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

