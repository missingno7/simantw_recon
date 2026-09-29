
struct IndexHeader {
    int recordCount;
    int field2;
    long stat1;
    long stat2;
    long stat3;
    int field8;
    int field9;
};

struct OpenDB {
    char name[0x50];
    void far *indexTable;
    struct IndexHeader header;
    unsigned char pad1[4];
    int count;
    long freeBytes;
    long wastedBytes;
    int pad2;
    int file;
    int dirty;
};

struct IndexEntry {
    void far *payload;
    int value;
    unsigned char caste;
    unsigned char kind;
};

extern struct OpenDB far openDBData[];
extern int far lastTop;
extern struct IndexEntry far * far lastPos;

extern int far sprintf(char far *buffer, char far *format, ...);
extern int far pascal _lopen(char far *path, int mode);
extern int far pascal _lcreat(char far *path, int attrib);
extern long far pascal _lread(int handle, void far *buffer, unsigned count);
extern long far pascal _lwrite(int handle, void far *buffer, unsigned count);
extern int far pascal _lclose(int handle);
extern long far pascal _llseek(int handle, long offset, int origin);
extern int near errno;
extern void far DosPunt(char far *message, ...);
extern void far Punt(char far *message, ...);
extern void far *mem_malloc(unsigned int size, char far *tag);
extern void far mem_free(void far *block);
extern void far *_fmemcpy(void far *destination, const void far *source, unsigned int count);
extern void far *FindIndex(int recIndex, int p2, int p3);


/* Lower-bound search; lastTop and lastPos are the original PACK publics. */
void far *FindIndex(int idx, int value, int caste)
{
    int high;
    int maxIndex;
    int mid;

    lastTop = 0;
    high = openDBData[idx].header.recordCount - 1;
    maxIndex = high;
    if (high == -1)
        return 0;
    if (high >= 0) {
        do {
            mid = (lastTop + high) / 2;
            lastPos = (struct IndexEntry far *)((char far *)openDBData[idx].indexTable + mid * 8);
            if (lastPos->caste > caste ||
                (lastPos->caste == caste && lastPos->value >= value))
                high = mid - 1;
            else
                lastTop = mid + 1;
        } while (lastTop <= high);
    }
    if (lastTop > maxIndex)
        return 0;
    lastPos = (struct IndexEntry far *)((char far *)openDBData[idx].indexTable + lastTop * 8);
    if (lastPos->value == value && lastPos->caste == caste)
        return lastPos;
    return 0;
}
