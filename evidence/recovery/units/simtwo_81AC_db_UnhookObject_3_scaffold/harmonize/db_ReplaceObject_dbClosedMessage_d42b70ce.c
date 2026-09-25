extern int near db_numOfHandles;
extern int near db_cacheTable;
extern int far db_handles[];
char far dbClosedMessage[] = "Unhook attempt with database closed";
extern void far Punt(char far *message);
extern void far DBDelete(int handle, int object, int type);
extern void far ch_RemoveEntry(int object, int type, int cacheTable);
extern void far DBAdd(int handle, int arg4, int arg5, int arg6,
                      int object, int type, int arg3);

void db_ReplaceObject(int object, int type, int arg3, int arg4,
                      int arg5, int arg6)
{
    DBDelete(db_handles[0], object, type);
    if (db_numOfHandles < 0)
        Punt(dbClosedMessage);
    ch_RemoveEntry(object, type, db_cacheTable);
    DBAdd(db_handles[0], arg4, arg5, arg6, object, type, arg3);
}
