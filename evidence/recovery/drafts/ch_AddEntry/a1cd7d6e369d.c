/* Cache an object's type in the selected table.  The table has a
   count/capacity header followed by four-byte object records and a parallel
   handle vector;
   releaseHook is the named DGROUP array containing the age counter used by
   the cache's periodic stale-entry sweep. */
struct CacheEntry {
    unsigned int object;
    unsigned int type;
};

struct CacheTable {
    unsigned int capacity;
    unsigned int count;
    struct CacheEntry entry[1];
};

typedef void (far *CacheHook)(void);
struct CacheReleaseData {
    CacheHook releaseFunction;
    char cacheNameHead[12];
    unsigned int slot;
    char cacheNameTail[16];
    int age;
    char diagnostics[534];
    void far *packBuffer;
};

extern struct CacheReleaseData near releaseHook;
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
int far ch_AddEntry(int object, int type, unsigned int cacheHandle,
                    unsigned int valueHandle)
{
    struct CacheTable far *table;
    struct CacheEntry far *entry;
    unsigned int far *handles;
    unsigned int i;
    unsigned int used;
    unsigned int oldCount;
    int found;

    table = (struct CacheTable far *)mem_Lock(cacheHandle);
    oldCount = table->capacity;
    used = table->count;
    ++releaseHook.age;

    if (used == oldCount || releaseHook.age > 30) {
        WinPrintf(releaseHook.diagnostics, object, type, used);
        releaseHook.age = 0;
        mem_Unlock(cacheHandle);
        table = (struct CacheTable far *)mem_Lock(cacheHandle);
        handles = (unsigned int far *)((unsigned char far *)table +
                                      (table->capacity + 1) * 4);
        i = 0;
        entry = table->entry;
        while (i < table->capacity) {
            if (entry->object != 0xffff && handles[i] != 0 &&
                mem_Freed(handles[i]) && mem_LockLevel(handles[i]) == 0) {
                WinPrintf(releaseHook.diagnostics + 0x1f,
                          entry->object, entry->type);
                mem_Free(handles[i]);
                handles[i] = 0;
                entry->object = 0xffff;
                --table->count;
            }
            ++entry;
            ++i;
        }
        mem_Unlock(cacheHandle);
        WinPrintf(releaseHook.diagnostics + 0x1f, object, type, oldCount);
        mem_Flush();
        table = (struct CacheTable far *)mem_Lock(cacheHandle);
        handles = (unsigned int far *)((unsigned char far *)table +
                                      (table->capacity + 1) * 4);
        i = 0;
        entry = table->entry;
        while (i < table->capacity) {
            if (entry->object != 0xffff && handles[i] != 0 &&
                mem_Freed(handles[i]) && mem_LockLevel(handles[i]) == 0) {
                WinPrintf(releaseHook.diagnostics + 0x3f,
                          entry->object, entry->type);
                mem_Free(handles[i]);
                handles[i] = 0;
                entry->object = 0xffff;
                --table->count;
            }
            ++entry;
            ++i;
        }
        mem_Unlock(cacheHandle);
        found = ch_LookUpId(object, type, cacheHandle);
        if (table->count == oldCount && found == 0)
            Punt(releaseHook.diagnostics + 0x70);
        if (table->count == table->capacity)
            ch_DumpOldest(cacheHandle);
    }

    found = ch_LookUpId(object, type, cacheHandle);
    if (found == 0) {
        WinPrintf(releaseHook.diagnostics + 0x7b, object);
        mem_Unlock(cacheHandle);
        return 0;
    }

    table = (struct CacheTable far *)mem_Lock(cacheHandle);
    entry = table->entry + releaseHook.slot;
    entry->object = object;
    entry->type = type;
    handles = (unsigned int far *)((unsigned char far *)table +
                                  (table->capacity + 1) * 4);
    handles[releaseHook.slot] = valueHandle;
    ++table->count;
    mem_Unlock(cacheHandle);
    return 1;
}
