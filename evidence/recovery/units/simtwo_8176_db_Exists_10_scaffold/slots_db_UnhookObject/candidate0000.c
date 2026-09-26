extern int near db_numOfHandles;
extern int near db_cacheTable;
extern void far Punt(char far *message);
extern void far ch_RemoveEntry(int object, int type, int cacheTable);

void db_UnhookObject(int object, int type)
{
    if (db_numOfHandles < 0)
        Punt("Unhook attempt with database closed");
    ch_RemoveEntry(object, type, db_cacheTable);
}
