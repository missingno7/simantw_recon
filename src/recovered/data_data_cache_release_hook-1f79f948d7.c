/* The cache module keeps its far release callback first, followed by the
 * fixed cache-table label and its NUL-separated diagnostic format strings.
 * The trailing far pointer names the shared PACK input window. */
typedef void (far *CacheReleaseHook)(void);
extern unsigned char __based(__segname("PACK")) pack_buf[];

struct CacheReleaseData {
    CacheReleaseHook releaseFunction;
    char cacheTableName[32];
    char diagnostics[534];
    void far * packBuffer;
};

struct CacheReleaseData releaseHook = {
    0,
    "cachetable",
    "ch_AddEntry(dump)(%d)(%d)(%d)\n\000ch_AddEntry(purge)(%d)(%d)(%d)\n\000A"
    "ttemp to add ID already present in lookup table\000[(%u)(%u)]\000\n\000no "
    "memory over 0 in age!\000ch_DumpOldest(%u)(%u)\n\000primes\000%s.ndx\000Index"
    " file missing\000Not enough memory to read index file in.\000%s.ndx\000Ca"
    "n't create index file\000index\000%s.ndx\000Index file missing\000Error-atte"
    "mpt to delete index with there weren't any\000record\000Not enough mem"
    "ory to delete indices\000ID # already present in file\000record\000Not en"
    "ough memory for new indices\000ID # not found.\000record\000Not enough me"
    "mory for new indices\000",
    (void far *)pack_buf
};
