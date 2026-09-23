/* Hypothesis: a packed object number loads and locks a window resource.  Its
   signed high-byte bucket owns a pointer table at +0x2c followed by variable
   records; each record's +0x22 word advances to the next record. */
struct WindowRecord {
    unsigned char header[0x22];
    unsigned int nextDelta;
    unsigned char tail[0x2c - 0x24];
    unsigned short words[4];
};
struct WindowBucket {
    unsigned char header[0x0c];
    int recordCount;
    unsigned char gap[0x2c - 0x0e];
    struct WindowRecord far *records[256];
};
struct WindowResource {
    unsigned char header[0x2c];
    struct WindowRecord far *firstRecord;
};
extern struct WindowBucket far * near win_handles[];
extern unsigned int far db_LoadObject(int object, int kind, int lock);
extern void far *mem_Lock(unsigned int handle);
extern void far Punt(char far *message, ...);
extern void far win_LockWin(int objectNumber);
extern void far win_UnlockWin(int objectNumber);
extern int far match_position[];

void far win_LoadWindow(register int objectNumber)
{
    register int objectNumber = inputObjectNumber;
    signed char bucketNumber;
    unsigned int handle;
    struct WindowBucket far *bucket;
    struct WindowRecord far *record;
    struct WindowResource far *resource;
    int count;
    int i;
    int mode;

    bucketNumber = (signed char)(objectNumber >> 8);
    handle = db_LoadObject(bucketNumber, 0, 1);
    if (!handle)
        Punt("CANNOT LOAD WINDOW %03x", objectNumber);
    win_handles[bucketNumber] = mem_Lock(handle);
    win_LockWin(objectNumber);
    bucket = win_handles[bucketNumber];
    count = bucket->recordCount;
    record = (struct WindowRecord far *)((char far *)bucket->records + count * 4);
    if (count > 0) {
        for (i = 0; i < count; ++i) {
            bucket->records[i] = record;
            record = (struct WindowRecord far *)((char far *)record + record->nextDelta);
        }
    }
    resource = (struct WindowResource far *)mem_Lock(handle);
    record = resource->firstRecord;
    mode = match_position[((unsigned char)bucketNumber << 2) + 0x3f81];
    if (mode != (int)0x8000) {
        for (i = 0; i < 4; ++i)
            bucket->records[0]->words[i] = record->words[i];
    } else {
        for (i = 0; i < 4; ++i)
            resource->firstRecord->words[i] = bucket->records[0]->words[i];
    }
    for (i = 0; i < count; ++i) {
        bucket->records[i]->words[0] = resource->firstRecord->words[0];
        if (bucket->records[i]->header[0x21] == 4) {
            bucket->records[i]->words[0] = 0;
            bucket->records[i]->words[1] = 0;
            bucket->records[i]->words[2] = 0;
            bucket->records[i]->words[3] = 0;
        }
    }
    win_UnlockWin(objectNumber);
}





