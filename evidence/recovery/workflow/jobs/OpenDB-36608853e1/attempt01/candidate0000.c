/*
 * Open the .dat file for a database and initialize its four-handle slot.
 * The first call clears the slot names once. A free slot receives a bounded
 * copy of the requested database name; any filename extension after the last
 * path separator is removed, then ".dat" is appended into the stack path.
 * Existing files contribute their 14-byte header and an index is opened only
 * when both magic words match. New or invalid files receive an empty header
 * and a new index. Failure messages and the private one-time initialization
 * word are inferred from the observed calls and DGROUP references.
 */
struct OpenDB {
    char name[0x50];
    void far *indexTable;
    int recordCount;
    unsigned char pad1[0x16];
    int count;
    long freeBytes;
    long wastedBytes;
    int pad2;
    int file;
    int dirty;
};
extern struct OpenDB far openDBData[];
static int near openDBInitialized;
extern int near errno;
extern char far * far sys_errlist[];
extern int far sprintf(char far *buffer, char far *format, ...);
extern char far * far strncpy(char far *dst, const char far *src, unsigned count);
extern char far * far strrchr(const char far *s, int ch);
extern int far pascal _lopen(char far *path, int mode);
extern int far pascal _lcreat(char far *path, int attributes);
extern int far pascal _lread(int file, void far *buffer, unsigned count);
extern void far Punt(char far *message, ...);
extern void far CreateIndex(struct OpenDB far *db, int index);
extern void far OpenIndex(struct OpenDB far *db, int index);

int far OpenDB(char far *name)
{
    char path[110];
    char far *dot;
    char far *slash;
    unsigned int i;
    int file;
    int result;
    struct OpenDB far *db;

    if (openDBInitialized == 0) {
        for (i = 0; i < 4; ++i)
            openDBData[i].name[0] = 0;
        openDBInitialized = 1;
    }
    for (i = 0; i < 4 && openDBData[i].name[0] != 0; ++i)
        ;
    if (i == 4)
        Punt("Too many open databases");

    db = &openDBData[i];
    strncpy(db->name, name, 0x4f);
    db->name[0x4f] = 0;
    dot = strrchr(db->name, '.');
    if (dot != 0) {
        slash = strrchr(db->name, '\\');
        if (slash != 0 && dot < slash)
            dot = 0;
        if (dot != 0)
            *dot = 0;
    }
    sprintf(path, "%s.dat", db->name);
    file = _lopen(path, 2);
    db->file = file;
    if (file <= 0) {
        file = _lcreat(path, 0);
        db->file = file;
    }
    if (file <= 0) {
        if (errno == 0x18)
            Punt("Too many open files");
        Punt("Cannot open %s: %s (error %d)", path, sys_errlist[errno], errno);
    }

    result = _lread(file, (char far *)db + 0x68, 0x0e);
    if (result != 0x0e || db->count != 0x5678 || db->freeBytes != 0x1234L) {
        db->count = 0x5678;
        db->freeBytes = 0x1234L;
        db->wastedBytes = 0;
        db->recordCount = 0;
        db->indexTable = 0;
        db->dirty = 1;
        CreateIndex(db, i);
    } else {
        OpenIndex(db, i);
        db->dirty = 0;
    }
    return i;
}
