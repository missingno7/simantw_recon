/* Candidate translation unit simtwo_8F46_ch_DeleteEntry_2_scaffold: composed from preserved exact-body sources
 * in MAPSYM order. Internal evidence id, not a historical filename.
 * Members: _ch_DeleteEntry, _ch_SetCacheHooks
 * SCAFFOLDED: claimed members in 2 code runs; no pool stand-ins were needed. */

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
typedef void (far *Hook)(void);
extern Hook near cacheHook;
extern Hook near releaseHook;


void ch_SetCacheHooks(Hook cache, Hook release);

#pragma alloc_text(RUN2_TEXT, ch_SetCacheHooks)

static int near chFoundIndex = 0;
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

