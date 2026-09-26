/* Reviewed cache-unit source for simtwo:8F46.
 *
 * The public bodies retained here are the admitted _ch_DeleteEntry and
 * _ch_SetCacheHooks sources.  The other nine publics remain unclaimed: their
 * best drafts are recorded in contexts/ and the unit's two code runs preserve
 * the original gap without treating draft bodies as recovered source.
 *
 * The DGROUP declarations follow the target bytes from _cacheHook at B580 to
 * _pack_threshold at B7C2.  The four lookup counters and chFoundIndex are
 * shared file-scope state.  Literal arrays preserve the original private
 * NUL-terminated strings in their observed contribution order.  The last
 * based pointer retains the PACK selector relocation at B7C0.
 */
typedef void (far *Hook)(void);

Hook near cacheHook = 0;
Hook near releaseHook = 0;

extern unsigned char __based(__segname("PACK")) pack_buf[];

static char near chCreateTableName[] = "cachetable";
static int near chFoundIndex = 0;
static long near chLookupHits = 0L;
static long near chLookupMisses = 0L;
static long near chLookupHitProbes = 0L;
static long near chLookupMissProbes = 0L;
static int near chAddEntryAge = 0;

/* _ch_AddEntry private formats, including its shared lookup diagnostics. */
static char near chAddEntryDumpFormat[] = "ch_AddEntry(dump)(%d)(%d)(%d)\n";
static char near chAddEntryPurgeFormat[] = "ch_AddEntry(purge)(%d)(%d)(%d)\n";
static char near chAddEntryDuplicateMessage[] = "Attemp to add ID already present in lookup table";

/* Shared by _ch_LookUpId, _ch_AddEntry and _ch_CleanupTable. */
static char near chLookupPairFormat[] = "[(%u)(%u)]";
static char near chLookupNewline[] = "\n";

/* _ch_DumpOldest diagnostics and the prime-table label. */
static char near chDumpOldestMemoryMessage[] = "no memory over 0 in age!";
static char near chDumpOldestFormat[] = "ch_DumpOldest(%u)(%u)\n";
static char near chPrimeTableName[] = "primes";

/* Remaining initialized private strings in the same DATA contribution.
 * Their direct call-site owner is not resolved by the cache member packets. */
static char near chIndexFileSuffix1[] = "%s.ndx";
static char near chIndexMissing1[] = "Index file missing";
static char near chIndexReadFailure[] = "Not enough memory to read index file in.";
static char near chIndexFileSuffix2[] = "%s.ndx";
static char near chIndexCreateFailure[] = "Can't create index file";
static char near chIndexName[] = "index";
static char near chIndexFileSuffix3[] = "%s.ndx";
static char near chIndexMissing2[] = "Index file missing";
static char near chIndexDeleteFailure[] = "Error-attempt to delete index with there weren't any";
static char near chRecordName1[] = "record";
static char near chRecordDeleteFailure[] = "Not enough memory to delete indices";
static char near chRecordDuplicate[] = "ID # already present in file";
static char near chRecordName2[] = "record";
static char near chRecordAllocateFailure1[] = "Not enough memory for new indices";
static char near chRecordMissing[] = "ID # not found.";
static char near chRecordName3[] = "record";
static char near chRecordAllocateFailure2[] = "Not enough memory for new indices";

static void far * near cachePackBuffer = (void far *)pack_buf;

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

void ch_SetCacheHooks(Hook cache, Hook release);

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
