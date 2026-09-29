/* Full lookup and stale-handle sweep hypothesis for simtwo cache table. */
typedef int (far *LookupHook)(int id, int type);
typedef void (far *Hook)(void);
extern Hook near cacheHook;
extern void far *mem_Lock(unsigned int handle);
extern int far mem_Unlock(unsigned int handle);
extern int mem_Freed(unsigned int handle);

extern int mem_LockLevel(unsigned handle);

extern void far mem_Free(int handle);

extern unsigned int mem_Freshen(unsigned int handle);

extern void far WinPrintf(char far *format, ...);


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

volatile int ch_LookUpId(int id, int type, int tableHandle)
{
    struct CacheTable far *table;
    int far *handles;
    int bucket;
    int index;
    int probes;
    int handle;
    int found;
    int count;
    struct CacheSlot far *slot;
    register int lookupId;

    probes = 0;
    lookupId = id;
    if (cacheHook != 0) {
        handle = ((LookupHook)cacheHook)(lookupId, type);
        if (handle != 0)
            return handle;
    }

    table = (struct CacheTable far *)mem_Lock(tableHandle);
    count = table->count;
    bucket = (7 * type + (signed char)(lookupId >> 8) + lookupId) % count;
    handles = (int far *)((char far *)table + ((count + 1) * 4));
    chFoundIndex = 0;
    if (bucket < 0)
        index = count - 1;
    else
        index = bucket;
    handle = 0;
    found = 0;

    while (index >= 0) {
        if (table->slots[index].id == lookupId && table->slots[index].extra == type) {
            found = 1;
            break;
        }
        if (chFoundIndex == 0 && table->slots[index].id == -1)
            chFoundIndex = index;
        probes++;
        index--;
    }
    if (!found && bucket >= 0) {
        index = count - 1;
        while (index > bucket) {
            if (table->slots[index].id == lookupId && table->slots[index].extra == type) {
                found = 1;
                break;
            }
            if (chFoundIndex == 0 && table->slots[index].id == -1)
                chFoundIndex = index;
            probes++;
            index--;
        }
    }

    if (found) {
        chFoundIndex = index;
        handle = handles[index];
        chLookupHitProbes += probes;
        chLookupHits++;
        if (mem_Freed(handle))
            goto sweep_stale_entries;
        mem_Freshen(handle);
        mem_Unlock(tableHandle);
        return handle;
    }
    goto lookup_miss;

sweep_stale_entries:
    table = (struct CacheTable far *)mem_Lock(tableHandle);
    handles = (int far *)((char far *)table + ((table->count + 1) * 4));
    slot = table->slots;
    count = table->count;
    do {
        int staleHandle;
        staleHandle = *handles;
        if (slot->id != -1 && staleHandle != 0 &&
            mem_Freed(staleHandle) && mem_LockLevel(staleHandle) == 0) {
            WinPrintf("[(%u)(%u)]", slot->id, slot->extra);
            mem_Free(staleHandle);
            *handles = 0;
            slot->id = -1;
            table->used--;
        }
        slot++;
        handles++;
    } while (--count);
    WinPrintf("\n");
    mem_Unlock(tableHandle);

lookup_miss:
    chLookupMissProbes += probes;
    chLookupMisses++;
    mem_Unlock(tableHandle);
    return 0;
}
