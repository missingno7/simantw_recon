/*
 * Open a database file using the first free one of four handles. Initialize
 * the openDBData names once, copy the name with a 0x4f-byte limit, remove a
 * path extension, and append .dat. A valid 14-byte header opens the existing
 * index; otherwise initialize an empty header and create the index.
 */
struct OpenDB {
    char name[0x50];
    void far *indexTable;
    int recordCount;
    unsigned char pad1[0x12];
    unsigned int magic;         /* 0x68 */
    unsigned int version;       /* 0x6a */
    int count;                  /* 0x6c */
    long freeBytes;             /* 0x6e */
    long wastedBytes;           /* 0x72 */
    int pad2;                   /* 0x76 */
    int file;                   /* 0x78 */
    int dirty;                  /* 0x7a */
};
extern struct OpenDB far openDBData[];
static int near openDBInitialized = 0;
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
    int i;
    int file;
    struct OpenDB far *db;

    if (openDBInitialized == 0) {
        for (i = 0; i < 4; ++i)
            openDBData[i].name[0] = 0;
        openDBInitialized = 1;
    }
    for (i = 0; i < 4 && openDBData[i].name[0] != 0; ++i)
        ;
    if (i == 4)
        Punt("Out of handles.");

    db = &openDBData[i];
    strncpy(db->name, name, 0x4f);
    db->name[0x4f] = 0;
    dot = db->name;
    if (*dot == '.') {
        while (*dot == '.')
            ++dot;
    }
    dot = strrchr(dot, '.');
    if (dot != 0 && strrchr(db->name, '\\') < dot)
        *dot = 0;

    sprintf(path, "%s.dat", db->name);
    file = _lopen(path, 2);
    db->file = file;
    if (file <= 0) {
        file = _lcreat(path, 0);
        db->file = file;
    }
    if (file <= 0) {
        if (errno == 0x18)
            Punt("Too many files open.  You need a statement 'FILES=12' in\nyour config.sys file.  Please refer to your dos manual\nfor more information.");
        Punt("%s\nDos error: %d: %s", "Cannot create data file.", errno, sys_errlist[errno]);
    }

    if (_lread(file, (char far *)db + 0x68, 0x0e) == 0x0e &&
        db->magic == 0x5678 && db->version == 0x1234) {
        OpenIndex(db, i);
        db->dirty = 0;
    } else {
        db->magic = 0x5678;
        db->version = 0x1234;
        db->freeBytes = 0;
        db->wastedBytes = 0;
        db->pad2 = 0;
        db->dirty = 1;
        CreateIndex(db, i);
    }
    return i;
}
