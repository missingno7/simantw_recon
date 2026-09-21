/*
 * ch_DeleteEntry: remove an object from a cache table.  ch_LookUpId (same
 * code group, far) reports whether the (object, type) pair is present and
 * leaves the matching slot index in the private near word chFoundIndex
 * (unnamed DGROUP word at 0xb594, initialised zero bytes following a string literal).  The table handle is
 * locked (verified far mem_Lock): the header holds the slot count at +0 and
 * the used count at +2, followed by four-byte slot records whose first word
 * is the id, set to -1 here.  A word array follows the slot records at
 * (count + 1) * 4 bytes from the table start; the original forms that
 * address with 32-bit arithmetic on the far pointer (add/adc into ES),
 * i.e. a long cast with a zero-extended (unsigned) byte offset, and zeroes
 * the slot's word.  The used count is
 * decremented, the handle unlocked, and 1 returned; a missing entry
 * returns 0.
 */
struct CacheSlot {
    int id;
    int extra;
};

struct CacheTable {
    unsigned int count;
    int used;
    struct CacheSlot slots[1];
};

extern int far ch_LookUpId(int object, int type, int cacheTable);
extern void far *mem_Lock(unsigned int handle);
extern int far mem_Unlock(unsigned int handle);

static int near chFoundIndex = 0;

int far ch_DeleteEntry(int object, int type, int cacheTable)
{
    struct CacheTable far *table;
    int far *ages;

    if (ch_LookUpId(object, type, cacheTable) == 0)
        return 0;
    table = (struct CacheTable far *)mem_Lock(cacheTable);
    table->slots[chFoundIndex].id = -1;
    ages = (int far *)((long)table + (unsigned)((table->count + 1) * 4));
    ages[chFoundIndex] = 0;
    table->used--;
    mem_Unlock(cacheTable);
    return 1;
}
