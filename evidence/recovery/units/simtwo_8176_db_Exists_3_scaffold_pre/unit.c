/* Candidate translation unit simtwo_8176_db_Exists_3_scaffold_pre: composed from preserved exact-body sources
 * in MAPSYM order. Internal evidence id, not a historical filename.
 * Members: _db_Exists, _db_SetDataBase, _db_LoadObject
 * SCAFFOLDED: claimed members in 2 code runs; no pool stand-ins were needed. */

extern int far sprintf(char far *buffer, char far *format, ...);
extern int far access(char far *path, int mode);
extern int near db_numOfHandles;
extern int near db_cacheTable;
extern int far db_handles[];
extern void far Punt(char far *message, ...);
extern int far ch_CreateTable(int size);
extern int far OpenDB(char far *name);
extern int far ch_LookUpId(int object, int type, int cacheTable);
extern int far ch_AddEntry(int object, int type, int cacheTable, int handle);
extern void far WinPrintf(char far *format, ...);
extern void far mem_SetType(int handle, int type);
extern int far DBRecall(int position, int object, int kind, int far *out);
static int near db_closed = 1;


unsigned int far db_LoadObject(int object, int kind, int lock);

#pragma alloc_text(RUN2_TEXT, db_LoadObject)

int db_Exists(char far *name)
{
    char path[100];

    sprintf(path, "%s.dat", name);
    if (access(path, 0) != -1)
        return 1;
    return 0;
}

int far db_SetDataBase(char far *name)
{
    char path[32];
    int handle;

    sprintf(path, "%s.dat", name);
    if (access(path, 0) == 0) {
        db_closed = 0;
        if (db_cacheTable == 0)
            db_cacheTable = ch_CreateTable(0);
        db_handles[db_numOfHandles] = OpenDB(name);
        handle = db_handles[db_numOfHandles++];
        if (handle < 0)
            Punt("Cannot open database %s", name);
        return handle;
    }
    return -1;
}

unsigned int far db_LoadObject(int object, int kind, int lock)
{
    struct { int value; } resultSlot;
    int handle;
    int i;
    int dummy;

    if (db_numOfHandles <= 0)
        Punt("Load attempt with database closed");
    handle = ch_LookUpId(object, kind, db_cacheTable);
    if (!handle) {
        for (i = 0; i < db_numOfHandles; i++) {
            if ((resultSlot.value = DBRecall(db_handles[i], object, kind, &dummy)) != 0) {
                if (!ch_AddEntry(object, kind, db_cacheTable, resultSlot.value))
                    Punt("LoadObject: can't add to cache");
                return resultSlot.value;
            }
        }
        WinPrintf("LoadObject: object not found(%d)(%d)", object, kind);
        return 0;
    }
    mem_SetType(handle, lock);
    return handle;
}

