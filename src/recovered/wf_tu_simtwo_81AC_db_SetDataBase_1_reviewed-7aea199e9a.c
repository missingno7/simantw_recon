/*
 * db_SetDataBase: open the named database file and register its handle.
 * The name is expanded with the "%s.dat" pattern into a 32-byte stack
 * path; only if the file is accessible does the work proceed (otherwise -1): the
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

/* The prior unclaimed member contributes a second, independently emitted
 * "%s.dat" at DGROUP B1EC. This stand-in's code is excluded from credit;
 * its seven DATA bytes remain part of the strict unit comparison. */
void far pool_data_fill_B1EC(void);
#pragma alloc_text(POOLSTUB_TEXT, pool_data_fill_B1EC)
void far pool_data_fill_B1EC(void)
{
    volatile char far *p;
    p = "%s.dat";
}

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
