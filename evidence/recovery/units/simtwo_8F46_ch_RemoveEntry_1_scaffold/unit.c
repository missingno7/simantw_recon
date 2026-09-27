/* Candidate translation unit simtwo_8F46_ch_RemoveEntry_1_scaffold: composed from preserved exact-body sources
 * in MAPSYM order. Internal evidence id, not a historical filename.
 * Members: _ch_RemoveEntry
 * SCAFFOLDED: claimed members in 1 code runs; no pool stand-ins were needed. */

struct CacheSlot {
    int id;
    int extra;
};
struct CacheTable {
    unsigned int count;
    int used;
    struct CacheSlot slots[1];
};
extern int far ch_LookUpId(int object, int type, volatile int cacheTable);
extern void far *mem_Lock(unsigned int handle);
extern int far mem_Unlock(unsigned int handle);




static int near chFoundIndex = 0;
int far ch_RemoveEntry(int object, int type, volatile int cacheTable)
{
    struct CacheTable far *table;
    int far *ages;

    if (ch_LookUpId(object, type, cacheTable) != 0) {
    table = (struct CacheTable far *)mem_Lock(cacheTable);
    table->slots[chFoundIndex].id = -1;
    ages = (int far *)((unsigned long)table + (unsigned long)((table->count + 1) * 4U));
    ages[chFoundIndex] = 0;
    table->used--;
    mem_Unlock(cacheTable);
        return 1;
    }
    return 0;
}

