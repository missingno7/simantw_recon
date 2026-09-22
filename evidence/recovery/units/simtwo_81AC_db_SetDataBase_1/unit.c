/* Candidate translation unit simtwo_81AC_db_SetDataBase_1: composed from preserved exact-body sources
 * in MAPSYM order. Internal evidence id, not a historical filename.
 * Members: _db_SetDataBase */

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

