extern int near db_numOfHandles;
extern int near db_cacheTable;
extern int far db_handles[];
extern void far CloseDB(int handle);
extern void far ch_PurgeCache(int cacheTable);

void db_CloseDataBase(void)
{
    while (db_numOfHandles > 0) {
        --db_numOfHandles;
        CloseDB(db_handles[db_numOfHandles]);
    }
    ch_PurgeCache(db_cacheTable);
    db_cacheTable = 0;
}
