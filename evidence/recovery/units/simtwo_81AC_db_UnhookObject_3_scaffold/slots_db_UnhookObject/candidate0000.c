extern int near db_numOfHandles;
extern int near db_cacheTable;
extern void far Punt(char far *message);
extern void far ch_RemoveEntry(int object, int type, int cacheTable);

char near dbClosedMessage[] = "Unhook attempt with database closed";

void db_UnhookObject(int object, int type)
{
    if (db_numOfHandles < 0)
        Punt(dbClosedMessage);
    ch_RemoveEntry(object, type, db_cacheTable);
}
