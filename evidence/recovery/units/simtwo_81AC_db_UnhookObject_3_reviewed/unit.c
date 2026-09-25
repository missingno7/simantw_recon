extern int near db_numOfHandles;
extern int near db_cacheTable;
extern int far db_handles[];
extern void far Punt(char far *message);
extern void far ch_RemoveEntry(int object, int type, int cacheTable);
extern void far DBDelete(int handle, int object, int type);
extern void far DBAdd(int handle, int arg4, int arg5, int arg6,
                      int object, int type, int arg3);

static char closedDatabaseMessage[] = "Unhook attempt with database closed";

void db_UnhookObject(int object, int type)
{
    if (db_numOfHandles < 0)
        Punt(closedDatabaseMessage);
    ch_RemoveEntry(object, type, db_cacheTable);
}

void db_ReplaceObject(int object, int type, int arg3, int arg4,
                      int arg5, int arg6)
{
    DBDelete(db_handles[0], object, type);
    if (db_numOfHandles < 0)
        Punt(closedDatabaseMessage);
    ch_RemoveEntry(object, type, db_cacheTable);
    DBAdd(db_handles[0], arg4, arg5, arg6, object, type, arg3);
}

void db_SaveObject(int object, int type, int arg3, int arg4,
                   int arg5, int arg6)
{
    if (db_numOfHandles < 0)
        Punt(closedDatabaseMessage);
    ch_RemoveEntry(object, type, db_cacheTable);
    DBAdd(db_handles[0], arg4, arg5, arg6, object, type, arg3);
}
