/*
 * db_SetDataBase: open the named database file and register its handle.
 * The name is expanded with the "%s.dat" pattern into a 32-byte stack
 * path; if the file is not accessible the result is -1.  Otherwise the
 * private "database closed" flag (initialised to 1 in this TU) is cleared,
 * the shared cache table is created on first use, the file is opened with
 * OpenDB and its handle stored in the next db_handles slot.  The stored
 * handle is re-read while the handle count advances; a negative handle
 * punts with the "Cannot open database %s" message.  The handle is
 * returned.
 */
extern int near db_numOfHandles;
extern int near db_cacheTable;
extern int far db_handles[];
static int near db_closed = 1;

extern int far sprintf(char far *buffer, char far *format, ...);
extern int far access(char far *path, int mode);
extern void far Punt(char far *message, ...);
extern int far ch_CreateTable(int size);
extern int far OpenDB(char far *name);

int far db_SetDataBase(char far *name)
{
    char path[32];
    int handle;

    sprintf(path, "%s.dat", name);
    if (access(path, 0) != 0)
        return -1;
    db_closed = 0;
    if (db_cacheTable == 0)
        db_cacheTable = ch_CreateTable(0);
    db_handles[db_numOfHandles] = OpenDB(name);
    handle = db_handles[db_numOfHandles++];
    if (handle < 0)
        Punt("Cannot open database %s", name);
    return handle;
}
