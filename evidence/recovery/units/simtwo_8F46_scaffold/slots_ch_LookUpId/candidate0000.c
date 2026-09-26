/*
 * Hypothesis: cache lookup first delegates to the optional hook. Otherwise it
 * hashes (id,type) into the locked cache table, scans backward with wraparound,
 * remembers a free slot in chFoundIndex, and uses the parallel handle vector.
 * The observed counter updates distinguish successful probes from misses.
 */
typedef int (far *LookupHook)(int id, int type);
extern LookupHook near cacheHook;
extern void far *mem_Lock(unsigned int handle);
extern int far mem_Unlock(unsigned int handle);
extern int far mem_Freed(unsigned int handle);
extern void far mem_Freshen(unsigned int handle);

struct CacheEntry {
    int id;
    int type;
};

struct CacheTable {
    int count;
    int used;
    struct CacheEntry entries[1];
};

static int near chFoundIndex = 0;
static long near chLookupHits;
static long near chLookupMisses;
static long near chLookupHitProbes;
static long near chLookupMissProbes;

int far ch_LookUpId(int id, int type, unsigned int tableHandle)
{
    struct CacheTable far *table;
    int far *handles;
    int index;
    int bucket;
    int probes;
    int handle;
    int result;

    if (cacheHook != 0) {
        result = cacheHook(id, type);
        if (result != 0)
            return result;
    }

    table = (struct CacheTable far *)mem_Lock(tableHandle);
    chFoundIndex = 0;
    bucket = (7 * type + (signed char)(id >> 8) + id) % table->count;
    handles = (int far *)((long)table + ((long)table->count + 1L) * 4L);
    probes = 0;
    result = 0;

    if (bucket >= 0) {
        index = bucket;
        do {
            if (table->entries[index].id == id &&
                table->entries[index].type == type) {
                chFoundIndex = index;
                handle = handles[index];
                if (handle != 0 && mem_Freed(handle)) {
                    mem_Freshen(handle);
                    result = handle;
                }
                break;
            }
            if (table->entries[index].id == -1 && chFoundIndex == 0)
                chFoundIndex = index;
            probes++;
            index--;
            if (index < 0)
                index = table->count - 1;
        } while (probes < table->count);
    }

    if (result != 0) {
        chLookupHits++;
        chLookupHitProbes += probes;
    } else {
        chLookupMisses++;
        chLookupMissProbes += probes;
    }
    mem_Unlock(tableHandle);
    return result;
}
