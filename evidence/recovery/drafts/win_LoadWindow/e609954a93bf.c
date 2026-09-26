/* Semantic reconstruction: load and lock the resource for the signed high-byte
 * window bucket, then populate its record pointers and synchronize its header. */
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

void far win_LoadWindow(int incomingObject)
{
    register int objectNumber;
    int bucketNumber;
    unsigned int handle;
    struct WindowBucket far *bucket;
    struct WindowRecord far *record;
    struct WindowResource far *resource;
    int count;
    int i;
    int mode;
    struct WindowWords { unsigned short word[4]; };

    objectNumber = incomingObject;
    bucketNumber = (signed char)(objectNumber >> 8);
    handle = db_LoadObject(bucketNumber, 0, 1);
    if (!handle)
        Punt("Cannot load window", objectNumber);
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
    resource = (struct WindowResource far *)bucket->records[0];
    record = bucket->records[0];
    mode = match_position[((unsigned char)bucketNumber << 2) + 0x3f81];
    {
        struct WindowWords far *shared;
        struct WindowWords far *saved;
        shared = (struct WindowWords far *)((char far *)bucket->records[0] + 8);
        saved = (struct WindowWords far *)&match_position[((unsigned char)bucketNumber << 2) + 0x3f81];
        if (mode != (int)0x8000) *saved = *shared;
        else *shared = *saved;
    }
    for (i = 0; i < count; ++i) {
        struct WindowRecord far *current;
        current = bucket->records[i];
        current->words[0] = bucket->records[0]->words[0];
        switch (current->header[0x21]) {
        case 4:
            {
                unsigned char far *bytes;
                int j;
                bytes = (unsigned char far *)current + 0x2a;
                for (j = 14; j != 0; --j) bytes[j - 1] = 0;
            }
            break;
        case 16: case 17: case 18:
            *((unsigned short far *)((char far *)current + 0x2a)) = 0;
            current->words[0] = 0;
            break;
        }
    }

    win_UnlockWin(objectNumber);
}

