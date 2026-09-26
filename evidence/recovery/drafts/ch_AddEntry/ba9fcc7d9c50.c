/* Cache an object's handle and type in the selected table.  The table has a
   count/capacity header followed by four-byte handle and object records;
   releaseHook is the named DGROUP array containing the age counter used by
   the cache's periodic stale-entry sweep. */
struct CacheEntry {
    unsigned int handle;
    unsigned int object;
};

struct CacheTable {
    unsigned int capacity;
    unsigned int count;
    struct CacheEntry entry[1];
};

extern int near releaseHook[];
extern void far *mem_Lock(unsigned int handle);
extern int far mem_Unlock(unsigned int handle);
extern int far mem_Freed(unsigned int handle);
extern int far mem_LockLevel(unsigned int handle);
extern void far mem_Free(unsigned int handle);
extern void far mem_Flush(void);
extern int far ch_LookUpId(int object, int type, int cacheTable);
extern void far ch_DumpOldest(int cacheTable);
extern void far WinPrintf(char far *format, ...);
extern void far Punt(char far *message, ...);

/* Add an entry after invalid handles are reclaimed.  If the table is full,
   retire the oldest cache entry before installing this object. */
int far ch_AddEntry(int object, int type, unsigned int cacheHandle)
{
    struct CacheTable far *table;
    struct CacheEntry far *entry;
    unsigned int i;
    unsigned int oldCount;
    int found;

    table = (struct CacheTable far *)mem_Lock(cacheHandle);
    oldCount = table->count;
    ++releaseHook[9];

    if (table->count == table->capacity || releaseHook[9] > 30) {
        WinPrintf("cache entry sweep: %u", table->count);
        releaseHook[9] = 0;
        mem_Unlock(cacheHandle);
        table = (struct CacheTable far *)mem_Lock(cacheHandle);
        i = 0;
        entry = table->entry;
        while (i < table->capacity) {
            if (entry->object != 0xffff && entry->handle != 0 &&
                !mem_Freed(entry->handle) && mem_LockLevel(entry->handle) == 0) {
                WinPrintf("release cached object %u", entry->object);
                mem_Free(entry->handle);
                entry->handle = 0;
                entry->object = 0xffff;
                --table->count;
            }
            ++entry;
            ++i;
        }
        found = ch_LookUpId(object, type, cacheHandle);
        if (table->count == oldCount && found == 0)
            Punt("cache table has no free entry");
        if (table->count == table->capacity)
            ch_DumpOldest(cacheHandle);
    }

    found = ch_LookUpId(object, type, cacheHandle);
    if (found == 0) {
        WinPrintf("unable to cache object %u", object);
        mem_Unlock(cacheHandle);
        return 0;
    }

    table = (struct CacheTable far *)mem_Lock(cacheHandle);
    entry = table->entry + table->count;
    entry->handle = object;
    entry->object = type;
    ++table->count;
    mem_Unlock(cacheHandle);
    return 1;
}
