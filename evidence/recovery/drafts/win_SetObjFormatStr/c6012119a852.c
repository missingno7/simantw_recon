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
extern struct WinBucket far * near win_handles[];
extern void far win_LockWin(int objectNumber);
extern void far win_UnlockWin(int objectNumber);
extern void far Punt(char far *message, ...);
extern int far vsprintf(char far *buffer, char far *format, char far *args);
extern int far pascal LSTRLEN(char far *text);
extern char far * far pascal LSTRCPY(char far *destination, char far *source);
extern struct RallocRecord far * far Ralloc(long size, int tag, char far *label);
extern struct RallocRecord far * far RallocRealloc(struct RallocRecord far *record, long size, int tag);
void far win_SetObjFormatStr(int objectNumber, char far *format, char far *args)
{
    struct WinBucket far *bucket;
    struct FormatObject far *object;
    struct FormatObject far *formatObject;
    char buffer[0x74];
    int length;
    win_LockWin(objectNumber);
    bucket = win_handles[objectNumber >> 8];
    if (bucket->count <= (unsigned char)objectNumber)
        Punt("Attempt to get obj address outsize window");
    object = (struct FormatObject far *)bucket->objects[(unsigned char)objectNumber];
    formatObject = *(struct FormatObject far * far *)&object->record;
    vsprintf(buffer, formatObject->format, args);
    length = LSTRLEN(buffer) + 1;
    if (formatObject->record == 0) {
        formatObject->record = Ralloc((long)(length + 8), 1, "formatStr");
    } else if (LSTRLEN(formatObject->record->data) + 1 < length) {
        formatObject->record = RallocRealloc(formatObject->record, (long)(length + 4), 1);
    }
    LSTRCPY(formatObject->record->data, buffer);
    win_UnlockWin(objectNumber);
}
