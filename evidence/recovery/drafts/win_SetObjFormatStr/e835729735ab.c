/*
 * Format the object's text using its formatting record and copy into the
 * record's movable data area. Kernel ordinal bindings identify LSTRLEN and
 * LSTRCPY; the record layout and allocator signatures follow admitted code.
 */
struct RallocRecord {
    char far *data;
    unsigned int handle;
    long size;
    unsigned long tick;
    int tag;
};
struct WinBucket {
    unsigned char header[0x0c];
    int count;
    unsigned char rest[0x2c - 0x0e];
    unsigned char far *objects[256];
};
struct FormatObject {
    unsigned char reserved[0x2a];
    struct RallocRecord far *record;
    char format[1];
};
extern unsigned long near win_handles[];
extern void far win_LockWin(int objectNumber);
extern void far win_UnlockWin(int objectNumber);
extern void far Punt(char far *message, ...);
extern int far vsprintf(char far *buffer, char far *format, char far *args);
extern int far pascal LSTRLEN(char far *text);
extern char far * far pascal LSTRCPY(char far *destination, char far *source);
extern struct RallocRecord far * far Ralloc(long size, int tag, char far *label);
extern struct RallocRecord far * far RallocRealloc(struct RallocRecord far *record, long size, int tag);
void far win_SetObjFormatStr(int objectNumber, ...)
{
    struct WinBucket far *bucket;
    struct FormatObject far *object;
    struct RallocRecord far *record;
    char buffer[100];
    int length;
    int objectNumberCopy;
    win_LockWin(objectNumber);
    objectNumberCopy = objectNumber;
    bucket = (struct WinBucket far *)win_handles[objectNumberCopy >> 8];
    if (bucket->count <= (unsigned char)objectNumber)
        Punt("Attempt to get obj address outsize window");
    object = (struct FormatObject far *)bucket->objects[(unsigned char)objectNumberCopy];
    vsprintf(buffer, object->format, (char far *)(&objectNumber + 1));
    length = LSTRLEN(buffer) + 1;
    record = object->record;
    if (record != 0) {
        if (LSTRLEN(record->data) + 1 < length) {
            record = RallocRealloc(record, (long)(length + 4), 1);
            object->record = record;
        }
    } else {
        record = Ralloc((long)(length + 8), 1, "formatStr");
        object->record = record;
    }
    LSTRCPY(record->data, buffer);
    win_UnlockWin(objectNumber);
}
