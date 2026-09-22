/* Candidate translation unit simtwo_81AC_db_SetDataBase_9_scaffold_pre: composed from preserved exact-body sources
 * in MAPSYM order. Internal evidence id, not a historical filename.
 * Members: _db_SetDataBase, _db_PurgeObject, _db_PurgeHandle, _db_ReleaseHandle, _db_ReleaseObject, _db_UnhookObject, _db_CloseDataBase, _db_ReplaceObject, _db_SaveObject
 * SCAFFOLDED: claimed members in 2 code runs; no pool stand-ins were needed. */

extern int near db_numOfHandles;
extern int near db_cacheTable;
extern int far db_handles[];
extern int far sprintf(char far *buffer, char far *format, ...);
extern int far access(char far *path, int mode);
extern void far Punt(char far *message);
extern int far ch_CreateTable(int size);
extern int far OpenDB(char far *name);
extern int far ch_LookUpId(int object, int type, int cacheTable);
extern void far ch_DeleteEntry(int object, int type, int cacheTable);
extern void far mem_Free(int handle);
extern int far ch_LookUpHandle(int handle, int cacheTable,
                               int far *object, int far *type);
extern void far WinPrintf(char far *format, ...);
extern void far mem_SetType(unsigned int handle, unsigned int type);
extern void far ch_RemoveEntry(int object, int type, int cacheTable);
extern void far CloseDB(int handle);
extern void far ch_PurgeCache(int cacheTable);
extern void far DBDelete(int handle, int object, int type);
extern void far DBAdd(int handle, int arg4, int arg5, int arg6,
                      int object, int type, int arg3);
static int near db_closed = 1;


void db_PurgeObject(int object, int type);
void db_PurgeHandle(int handle);
void db_ReleaseHandle(unsigned int handle);
void db_ReleaseObject(unsigned int object, int type);
void db_UnhookObject(int object, int type);
void db_CloseDataBase(void);
void db_ReplaceObject(int object, int type, int arg3, int arg4, int arg5, int arg6);
void db_SaveObject(int object, int type, int arg3, int arg4, int arg5, int arg6);

#pragma alloc_text(RUN2_TEXT, db_PurgeObject, db_PurgeHandle, db_ReleaseHandle, db_ReleaseObject)
#pragma alloc_text(RUN2_TEXT, db_UnhookObject, db_CloseDataBase, db_ReplaceObject, db_SaveObject)

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

void db_PurgeObject(int object, int type)
{
    int handle;

    if (db_numOfHandles < 0)
        Punt("Purge attempt with database closed");
    handle = ch_LookUpId(object, type, db_cacheTable);
    if (handle) {
        ch_DeleteEntry(object, type, db_cacheTable);
        mem_Free(handle);
        return;
    }
    Punt("PurgeObject: object not found(%d)(%d)", object, type);
}

void db_PurgeHandle(int handle)
{
    int object;
    int type;

    if (db_numOfHandles < 0)
        Punt("Purge attempt with database closed");
    if (ch_LookUpHandle(handle, db_cacheTable, &object, &type)) {
        ch_DeleteEntry(object, type, db_cacheTable);
        mem_Free(handle);
    } else {
        WinPrintf("\a\nPurge handle - handle not found!! handle=%p", handle);
    }
}

void db_ReleaseHandle(unsigned int handle)
{
    mem_SetType(handle, 3);
}

void db_ReleaseObject(unsigned int object, int type)
{
    int handle;

    if (object < 30000) {
        if (db_numOfHandles < 0)
            Punt("Purge attempt with database closed");
        handle = ch_LookUpId(object, type, db_cacheTable);
        if (handle)
            mem_SetType(handle, 3);
        else
            Punt("Release %d %d not in cache! ", object, type);
    }
}

void db_UnhookObject(int object, int type)
{
    if (db_numOfHandles < 0)
        Punt("Unhook attempt with database closed");
    ch_RemoveEntry(object, type, db_cacheTable);
}

void db_CloseDataBase(void)
{
    while (db_numOfHandles > 0) {
        --db_numOfHandles;
        CloseDB(db_handles[db_numOfHandles]);
    }
    ch_PurgeCache(db_cacheTable);
    db_cacheTable = 0;
}

void db_ReplaceObject(int object, int type, int arg3, int arg4,
                      int arg5, int arg6)
{
    DBDelete(db_handles[0], object, type);
    if (db_numOfHandles < 0)
        Punt("Unhook attempt with database closed");
    ch_RemoveEntry(object, type, db_cacheTable);
    DBAdd(db_handles[0], arg4, arg5, arg6, object, type, arg3);
}

void db_SaveObject(int object, int type, int arg3, int arg4,
                   int arg5, int arg6)
{
    if (db_numOfHandles < 0)
        Punt("Unhook attempt with database closed");
    ch_RemoveEntry(object, type, db_cacheTable);
    DBAdd(db_handles[0], arg4, arg5, arg6, object, type, arg3);
}

