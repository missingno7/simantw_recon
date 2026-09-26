/*
 * Open a named database in the first free one of four slots. The shared
 * one-time flag clears slot names; the requested name is copied and any
 * extension after the last path separator is removed before adding .dat.
 * Read the 14-byte file header and open its index when the two magic words
 * match; otherwise initialize an empty header and create a fresh index.
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
extern struct OpenDB __based(__segname("PACK")) openDBData[];
typedef struct OpenDB __based(__segname("PACK")) *DBPACK;
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
    char far *slash;
    int i;
    int file;
    int nread;
    struct OpenDB far *db;
    if (openDBInitialized != 0) goto slots_ready;
    openDBInitialized = 1;
    for (i = 0; i < 4; ++i)
        openDBData[i].name[0] = 0;
slots_ready:
    for (i = 0; i < 4; ++i) {
        if (openDBData[i].name[0] == 0)
            break;
    }
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
    if (dot != 0) {
        slash = strrchr(db->name, '\\');
        if (dot >= slash)
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
            Punt("Too many files open.  You need a statement 'FILES=12' in`nyour config.sys file.  Please refer to your dos manual`nfor more information.");
        Punt("%s`nDos error: %d: %s", "Cannot create data file.", errno, sys_errlist[errno]);
    }

    nread = _lread(file, (char far *)db + 0x68, 0x0e);
    if (nread == 0x0e && db->magic == 0x5678 && db->version == 0x1234) {
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
    }    return i;
}




