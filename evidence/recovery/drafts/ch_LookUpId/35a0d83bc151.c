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
    int count;
    int i;

    if (cacheHook != 0) {
        handle = cacheHook(id, type);
        if (handle != 0)
            return handle;
    }

    table = (struct CacheTable far *)mem_Lock(tableHandle);
    count = table->count;
    bucket = (7 * type + (short)((id & 0xff00) | ((id >> 8) & 0x00ff)) + id) % count;
    handles = (int far *)((char far *)table + ((count + 1) * 4));
    chFoundIndex = 0;
    probes = 0;
    index = bucket;
    handle = 0;

    while (probes < count) {
        if (table->slots[index].id == id && table->slots[index].extra == type) {
            chFoundIndex = index;
            handle = handles[index];
            chLookupHitProbes += probes;
            chLookupHits++;
            if (mem_Freed(handle)) {
                sweepTable = (struct CacheTable far *)mem_Lock(tableHandle);
                handles = (int far *)((char far *)sweepTable + ((sweepTable->count + 1) * 4));
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
                break;
            }
            mem_Freshen(handle);
            mem_Unlock(tableHandle);
            return handle;
        }
        if (chFoundIndex == 0 && table->slots[index].id == -1)
            chFoundIndex = index;
        probes++;
        index--;
        if (index < 0)
            index = count - 1;
    }

    chLookupMissProbes += probes;
    chLookupMisses++;
    mem_Unlock(tableHandle);
    return 0;
}
