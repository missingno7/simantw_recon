/* Lock the cache table, choose the oldest unlocked type-3 live handle, free it, clear its entry and handle slot, report it, and return the remaining active count. */
struct CacheEntry {
    unsigned int id;
    unsigned int type;
};

extern void far *mem_Lock(unsigned int handle);
extern int far mem_Unlock(unsigned int handle);
extern unsigned int far mem_Age(unsigned int handle);
extern int far mem_Type(unsigned int handle);
extern int far mem_LockLevel(unsigned int handle);
extern void far mem_Free(unsigned int handle);
extern void far Punt(char far *message, ...);
extern void far WinPrintf(char far *format, ...);

int far ch_DumpOldest(unsigned int handle)
{
    int far *table;
    struct CacheEntry far *entry;
    int far *handles;
    int far * volatile activeCount;
    struct CacheEntry far *oldEntry;
    int far *oldHandle;
    unsigned long age;
    unsigned long oldestAge;
    unsigned int count;

    table = (int far *)mem_Lock(handle);
    oldestAge = 0;
    count = table[0];
    handles = (int far *)((unsigned long)table + (unsigned int)((count + 1) << 2));
    activeCount = table + 1;

    if (table[1] != 0) {
        entry = (struct CacheEntry far *)((char far *)table + 4);
            for (;;) {
            if (entry->id == 65535) goto next_item;
            age = (unsigned long)mem_Age(*handles);
            if (age <= oldestAge) goto next_item;
            if (mem_Type(*handles) != 3) goto next_item;
            if (mem_LockLevel(*handles) != 0) goto next_item;
            oldestAge = age;
            oldHandle = handles;
            oldEntry = entry;
        next_item:
            handles++;
            entry++;
            if (count-- == 0) break;
        }
        if (oldestAge == 0)
            Punt("no memory over 0 in age!");
        mem_Free(*oldHandle);
        WinPrintf("ch_DumpOldest(%u)(%u)\n", oldEntry->id, oldEntry->type);
        oldEntry->id = 0xffff;
        *oldHandle = 0;
        --*activeCount;
    }
    mem_Unlock(handle);
    return *activeCount;
}







