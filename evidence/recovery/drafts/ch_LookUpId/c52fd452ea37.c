/* Full lookup and stale-handle sweep hypothesis for simtwo cache table. */
typedef int (far *LookupHook)(int id, int type);
extern LookupHook near cacheHook;
extern void far *mem_Lock(unsigned int handle);
extern int far mem_Unlock(unsigned int handle);
extern int far mem_Freed(unsigned int handle);
extern int far mem_LockLevel(unsigned int handle);
extern int far mem_Free(unsigned int handle);
extern int far mem_Freshen(unsigned int handle);
extern int far WinPrintf(const char far *format, ...);

struct CacheSlot {
    int id;
    int extra;
};

struct CacheTable {
    int count;
    int used;
    struct CacheSlot slots[1];
};

static int near chFoundIndex = 0;
static long near chLookupHits = 0L;
static long near chLookupMisses = 0L;
static long near chLookupHitProbes = 0L;
static long near chLookupMissProbes = 0L;

int far ch_LookUpId(int id, int type, unsigned int tableHandle)
{
    struct CacheTable far *table;
    struct CacheTable far *sweepTable;
    int far *handles;
    int bucket;
    int index;
    int probes;
    int handle;
    int found;
    int count;
    int i;

    if (cacheHook != 0) {
        handle = cacheHook(id, type);
        if (handle != 0)
            return handle;
    }

    table = (struct CacheTable far *)mem_Lock(tableHandle);
    count = table->count;
    bucket = (7 * type + (int)(signed char)(id >> 8) * 257 + id) % count;
    handles = (int far *)((unsigned long)table + ((unsigned long)(count + 1) * 4L));
    chFoundIndex = 0;
    probes = 0;
    found = 0;
    handle = 0;

    if (bucket >= 0) {
        index = bucket;
        while (index >= 0) {
            if (table->slots[index].id == id && table->slots[index].extra == type) {
                found = 1;
                break;
            }
            if (chFoundIndex == 0 && table->slots[index].id == -1)
                chFoundIndex = index;
            index--;
            probes++;
        }
        if (!found) {
            index = count - 1;
            while (index >= bucket) {
                if (table->slots[index].id == id && table->slots[index].extra == type) {
                    found = 1;
                    break;
                }
                if (chFoundIndex == 0 && table->slots[index].id == -1)
                    chFoundIndex = index;
                index--;
                probes++;
            }
        }
    } else {
        index = count - 1;
        while (index >= bucket) {
            if (table->slots[index].id == id && table->slots[index].extra == type) {
                found = 1;
                break;
            }
            if (chFoundIndex == 0 && table->slots[index].id == -1)
                chFoundIndex = index;
            index--;
            probes++;
        }
    }

    if (found) {
        chFoundIndex = index;
        chLookupHitProbes += probes;
        chLookupHits++;
        handle = handles[index];
        if (mem_Freed(handle)) {
            sweepTable = (struct CacheTable far *)mem_Lock(tableHandle);
            handles = (int far *)((unsigned long)sweepTable + ((unsigned long)(sweepTable->count + 1) * 4L));
            for (i = 0; i < sweepTable->count; i++) {
                int staleHandle;
                staleHandle = handles[i];
                if (sweepTable->slots[i].id != -1 && staleHandle != 0 &&
                    mem_Freed(staleHandle) && mem_LockLevel(staleHandle) == 0) {
                    WinPrintf("[(%u)(%u)]", sweepTable->slots[i].id,
                              sweepTable->slots[i].extra);
                    mem_Free(staleHandle);
                    handles[i] = 0;
                    sweepTable->slots[i].id = -1;
                    sweepTable->used--;
                }
            }
            WinPrintf("\n");
            mem_Unlock(tableHandle);
        } else {
            mem_Freshen(handle);
            mem_Unlock(tableHandle);
            return handle;
        }
    }

    chLookupMissProbes += probes;
    chLookupMisses++;
    mem_Unlock(tableHandle);
    return 0;
}
