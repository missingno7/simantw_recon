extern int near db_numOfHandles;
extern int near db_cacheTable;
extern void far Punt(char far *message, ...);
extern int far ch_LookUpHandle(int handle, int cacheTable,
                               int far *object, int far *type);
extern void far ch_DeleteEntry(int object, int type, int cacheTable);
extern void far mem_Free(int handle);
extern void far WinPrintf(char far *format, ...);

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
