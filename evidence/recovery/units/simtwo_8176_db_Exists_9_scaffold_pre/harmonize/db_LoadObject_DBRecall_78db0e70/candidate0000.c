/* R2 v1: force the recall value into a one-word aggregate home. */
extern int near db_numOfHandles;
extern int near db_cacheTable;
extern void far Punt(char far *message, ...);
extern int far ch_LookUpId(int object, int type, int cacheTable);
extern int far ch_AddEntry(int object, int type, int cacheTable, int handle);
extern void far WinPrintf(char far *format, ...);
extern void far mem_SetType(int handle, int type);
extern int far db_handles[];
extern int far DBRecall(int handle, char far *name, int far *size);

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
                    Punt("Cache table full, can't load object");
                return resultSlot.value;
            }
        }
        WinPrintf("Memory full or object missing - cannot load object:id=%d, type=%d\n", object, kind);
        return 0;
    }
    mem_SetType(handle, lock);
    return handle;
}
