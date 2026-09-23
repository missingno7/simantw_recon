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
    int far *handles;`r`n    unsigned long handleAddress;
    struct CacheEntry far *oldEntry;
    int far *oldHandle;
    unsigned long age;
    unsigned long oldestAge;
    int count;

    table = (int far *)mem_Lock(handle);
    oldestAge = 0;
    count = table[0];
    entry = (struct CacheEntry far *)((char far *)table + 4);
    handleAddress = (unsigned long)table + (unsigned long)(count + 1) * 4L;`r`n    handles = (int far *)handleAddress;

    if (table[1] != 0) {
        for (; count != 0; count--, entry++, handles++) {
            if (entry->id == 0xffff)
                continue;
            age = (unsigned long)mem_Age(*handles);
            if (age <= oldestAge)
                continue;
            if (mem_Type(*handles) != 3)
                continue;
            if (mem_LockLevel(*handles) != 0)
                continue;
            oldestAge = age;
            oldHandle = handles;
            oldEntry = entry;
        }
        if (oldestAge == 0)
            Punt("no memory over 0 in age!");
        mem_Free(*oldHandle);
        WinPrintf("ch_DumpOldest(%u)(%u)\n", oldEntry->id, oldEntry->type);
        oldEntry->id = 0xffff;
        *oldHandle = 0;
        --table[1];
    }
    mem_Unlock(handle);
    return table[1];
}


