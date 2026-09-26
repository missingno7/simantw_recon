/* Reviewed cache-unit source for simtwo:8F46.
 *
 * The admitted _ch_DeleteEntry and _ch_SetCacheHooks bodies are retained.
 * The other nine public bodies remain unclaimed; their best drafts and notes
 * are recorded under contexts/ and this worker's REPORT.md.  Each has a
 * reserved-code stand-in below, in component order.  The stand-ins are not
 * recovered bodies.  The separate literal stand-in keeps the observed
 * private literal contribution in the compiler's DATA layout.
 *
 * Public DATA and shared private state follow the target from _cacheHook at
 * B580 through the final cache-owned literal byte at B7BD.  The separate literal
 * assignments preserve the NUL-terminated strings in contribution order.
 */
typedef void (far *Hook)(void);

Hook near cacheHook = 0;
Hook near releaseHook = 0;

static char near chCreateTableName[] = "cachetable\0";
static int near chFoundIndex = 0;
static long near chLookupHits = 0L;
static long near chLookupMisses = 0L;
static long near chLookupHitProbes = 0L;
static long near chLookupMissProbes = 0L;
static int near chAddEntryAge = 0;

struct CacheSlot {
    int id;
    int extra;
};

struct CacheTable {
    int count;
    int used;
    struct CacheSlot slots[1];
};

extern int far ch_LookUpId(int object, int type, int cacheTable);
extern void far *mem_Lock(unsigned int handle);
extern int far mem_Unlock(unsigned int handle);

void far pool_stub_ch_CreateTable(void);
void far pool_stub_ch_RemoveEntry(void);
void far pool_stub_ch_PurgeCache(void);
void far pool_stub_ch_LookUpHandle(void);
void far pool_stub_ch_LookUpId(void);
void far pool_stub_ch_AddEntry(void);
void far pool_stub_ch_CleanupTable(void);
void far pool_stub_ch_DumpOldest(void);
void far pool_stub_ch_GetPrime(void);
void far cache_private_literal_scaffold(void);
void ch_SetCacheHooks(Hook cache, Hook release);

#pragma alloc_text(POOLSTUB_TEXT, pool_stub_ch_CreateTable, pool_stub_ch_RemoveEntry, pool_stub_ch_PurgeCache, pool_stub_ch_LookUpHandle, pool_stub_ch_LookUpId, pool_stub_ch_AddEntry, pool_stub_ch_CleanupTable, pool_stub_ch_DumpOldest, pool_stub_ch_GetPrime, cache_private_literal_scaffold)
#pragma alloc_text(RUN2_TEXT, ch_SetCacheHooks)

/* SCAFFOLD, not recovered source: the public's selector slot list is empty,
 * so this reserved-code body carries no pool references and claims no code. */
void far pool_stub_ch_CreateTable(void) { volatile int t; t = 0; }
void far pool_stub_ch_RemoveEntry(void) { volatile int t; t = 0; }
void far pool_stub_ch_PurgeCache(void) { volatile int t; t = 0; }
void far pool_stub_ch_LookUpHandle(void) { volatile int t; t = 0; }
void far pool_stub_ch_LookUpId(void) { volatile int t; t = 0; }
void far pool_stub_ch_AddEntry(void) { volatile int t; t = 0; }
void far pool_stub_ch_CleanupTable(void) { volatile int t; t = 0; }
void far pool_stub_ch_DumpOldest(void) { volatile int t; t = 0; }
void far pool_stub_ch_GetPrime(void) { volatile int t; t = 0; }

/* SCAFFOLD, not recovered source: keep the cache module's private literals
 * and zero-initialized shared state in the observed DGROUP order. */
void far cache_private_literal_scaffold(void)
{
    volatile char far *literal;
    volatile int age;
    volatile long counters;

    age = chAddEntryAge;
    counters = chLookupHits + chLookupMisses + chLookupHitProbes + chLookupMissProbes;

    /* _ch_AddEntry's three private diagnostic strings. */
    literal = "ch_AddEntry(dump)(%d)(%d)(%d)\n";
    literal = "ch_AddEntry(purge)(%d)(%d)(%d)\n";
    literal = "Attemp to add ID already present in lookup table";

    /* Shared lookup diagnostics used by _ch_LookUpId, _ch_AddEntry and
     * _ch_CleanupTable, followed by the _ch_DumpOldest messages. */
    literal = "[(%u)(%u)]";
    literal = "\n";
    literal = "no memory over 0 in age!";
    literal = "ch_DumpOldest(%u)(%u)\n";
    literal = "primes";

    /* Remaining initialized private strings in the same target contribution.
     * Their direct call-site owner is unresolved by the 11 public packets. */
    literal = "%s.ndx";
    literal = "Index file missing";
    literal = "Not enough memory to read index file in.";
    literal = "%s.ndx";
    literal = "Can't create index file";
    literal = "index";
    literal = "%s.ndx";
    literal = "Index file missing";
    literal = "Error-attempt to delete index with there weren't any";
    literal = "record";
    literal = "Not enough memory to delete indices";
    literal = "ID # already present in file";
    literal = "record";
    literal = "Not enough memory for new indices";
    literal = "ID # not found.";
    literal = "record";
    literal = "Not enough memory for new indices\0";
}

int far ch_DeleteEntry(int object, int type, volatile int cacheTable)
{
    struct CacheTable far *table;
    int far *ages;
    long addr;

    if (ch_LookUpId(object, type, cacheTable) != 0) { } else return 0;
    table = (struct CacheTable far *)mem_Lock(cacheTable);
    table->slots[chFoundIndex].id = -1;
    addr = (long)table;
    addr += (unsigned)((table->count + 1) * 4);
    ages = (int far *)addr;
    ages[chFoundIndex] = 0;
    table->used--;
    mem_Unlock(cacheTable);
    return 1;
}

void ch_SetCacheHooks(Hook cache, Hook release)
{
    cacheHook = cache;
    releaseHook = release;
}

