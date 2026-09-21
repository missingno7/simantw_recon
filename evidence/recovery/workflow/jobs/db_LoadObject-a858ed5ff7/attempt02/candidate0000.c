extern int near db_numOfHandles;
extern int near db_cacheTable;
extern void far Punt(char far *message, ...);
extern int far ch_LookUpId(int object, int type, int cacheTable);
extern int far ch_AddEntry(int object, int type, int cacheTable, int handle);
extern void far WinPrintf(char far *format, ...);
extern void far mem_SetType(int handle, int type);
extern unsigned char far match_position;
#define AT(off) ((&match_position)[off])
#define MatchPos(i) (*(int near *)&AT((i) * 2))
extern int far DBRecall(int position, int object, int kind, int far *out);

unsigned int far db_LoadObject(int object, int kind, int lock)
{
    int handle;
    int i;
    int dummy;

    if (db_numOfHandles <= 0)
        Punt("Load attempt with database closed");
    handle = ch_LookUpId(object, kind, db_cacheTable);
    if (!handle) {
        for (i = 0; i < db_numOfHandles; i++) {
            handle = DBRecall(MatchPos(i), object, kind, &dummy);
            if (handle) {
                if (!ch_AddEntry(object, kind, db_cacheTable, handle))
                    Punt("LoadObject: can't add to cache(%d)(%d)", object, kind);
                return handle;
            }
        }
        WinPrintf("LoadObject: object not found(%d)(%d)", object, kind);
        return 0;
    }
    mem_SetType(handle, lock);
    return handle;
}
