extern int near db_numOfHandles;
extern int near db_cacheTable;
extern void far Punt(char far *message, ...);
extern int far ch_LookUpId(int object, int type, int cacheTable);
extern void far mem_SetType(unsigned int handle, unsigned int type);

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
