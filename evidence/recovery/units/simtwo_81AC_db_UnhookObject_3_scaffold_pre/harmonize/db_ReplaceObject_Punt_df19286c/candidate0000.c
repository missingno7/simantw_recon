/*
 * Hypothesis: this is the replacement twin of db_SaveObject.  The first
 * two arguments identify the object and type; the remaining four words are
 * passed through in the same order used by the verified DBAdd wrapper.
 * The old record is deleted through the first selected database handle,
 * then the cache entry is removed and the replacement is added.  The
 * database-closed diagnostic is the shared DGROUP string used by the
 * neighboring verified wrappers.
 */
extern int near db_numOfHandles;
extern int near db_cacheTable;
extern int far db_handles[];
extern void far DBDelete(int handle, int object, int type);
extern void far Punt(char far *message);
extern void far ch_RemoveEntry(int object, int type, int cacheTable);
extern void far DBAdd(int handle, int arg4, int arg5, int arg6,
                      int object, int type, int arg3);

void db_ReplaceObject(int object, int type, int arg3, int arg4,
                      int arg5, int arg6)
{
    DBDelete(db_handles[0], object, type);
    if (db_numOfHandles < 0)
        Punt("Unhook attempt with database closed");
    ch_RemoveEntry(object, type, db_cacheTable);
    DBAdd(db_handles[0], arg4, arg5, arg6, object, type, arg3);
}
