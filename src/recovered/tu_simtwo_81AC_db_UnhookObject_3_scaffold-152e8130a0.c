/* Candidate translation unit simtwo_81AC_db_UnhookObject_3_scaffold: composed from preserved exact-body sources
 * in MAPSYM order. Internal evidence id, not a historical filename.
 * Members: _db_UnhookObject, _db_ReplaceObject, _db_SaveObject
 * SCAFFOLDED: unclaimed members _db_SetDataBase are stand-ins in POOLSTUB_TEXT (pool order only, never compared). */

extern int near db_numOfHandles;
extern int near db_cacheTable;
extern void far Punt(char far *message);
extern void far ch_RemoveEntry(int object, int type, int cacheTable);
char near dbClosedMessage[] = "Unhook attempt with database closed";
extern int far db_handles[];
extern void far DBDelete(int handle, int object, int type);
extern void far DBAdd(int handle, int arg4, int arg5, int arg6,
                      int object, int type, int arg3);


void far pool_stub_db_SetDataBase(void);
void db_ReplaceObject(int object, int type, int arg3, int arg4, int arg5, int arg6);
void db_SaveObject(int object, int type, int arg3, int arg4, int arg5, int arg6);

#pragma alloc_text(POOLSTUB_TEXT, pool_stub_db_SetDataBase)
#pragma alloc_text(RUN2_TEXT, db_ReplaceObject, db_SaveObject)

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _db_SetDataBase.
 * It only reproduces the object's selector-pool allocation order for the
 * words C686; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_db_SetDataBase(void)
{
    volatile int t;

    t = db_handles[0];
}

void db_UnhookObject(int object, int type)
{
    if (db_numOfHandles < 0)
        Punt(dbClosedMessage);
    ch_RemoveEntry(object, type, db_cacheTable);
}

void db_ReplaceObject(int object, int type, int arg3, int arg4,
                      int arg5, int arg6)
{
    DBDelete(db_handles[0], object, type);
    if (db_numOfHandles < 0)
        Punt(dbClosedMessage);
    ch_RemoveEntry(object, type, db_cacheTable);
    DBAdd(db_handles[0], arg4, arg5, arg6, object, type, arg3);
}

void db_SaveObject(int object, int type, int arg3, int arg4,
                   int arg5, int arg6)
{
    if (db_numOfHandles < 0)
        Punt(dbClosedMessage);
    ch_RemoveEntry(object, type, db_cacheTable);
    DBAdd(db_handles[0], arg4, arg5, arg6, object, type, arg3);
}

