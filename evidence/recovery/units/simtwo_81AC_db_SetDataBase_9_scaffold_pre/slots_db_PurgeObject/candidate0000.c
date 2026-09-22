extern int near db_numOfHandles;
extern int near db_cacheTable;
extern void far Punt(char far *message, ...);
extern int far ch_LookUpId(int object, int type, int cacheTable);
extern void far ch_DeleteEntry(int object, int type, int cacheTable);
extern void far mem_Free(int handle);

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
