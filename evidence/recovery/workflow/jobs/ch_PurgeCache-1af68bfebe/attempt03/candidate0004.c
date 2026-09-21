/*
 * ch_PurgeCache: free every handle held by a cache table, then the table.
 * The locked table (verified far mem_Lock) has the slot count at +0, the
 * used count at +2 and four-byte slot records from +4 whose first word is
 * the id (-1 when empty); a word array of handles follows the records at
 * (count + 1) * 4 bytes from the table start.  The original forms that
 * far address with a 32-bit add in which the byte offset is the left
 * operand, zero-extended (sub dx,dx), and the far pointer the right one
 * (add ax,di; adc dx,bx).  Every occupied slot's handle is freed, the loop
 * counter is a memory local, and finally the table handle is unlocked and
 * freed.  The count is assigned inside the guard condition, so its value
 * is tested from AX while SI keeps the copy.
 */
struct CacheSlot {
    int id;
    int extra;
};

struct CacheTable {
    int count;
    int used;
    struct CacheSlot slots[1];
};

extern void far *mem_Lock(unsigned int handle);
extern int far mem_Unlock(unsigned int handle);
extern void far mem_Free(int handle);

void far ch_PurgeCache(int cacheTable)
{
    struct CacheSlot far *slot;
    int far *handles;
    int count;
    int n;
    int i;
    struct CacheTable far *table;

    table = (struct CacheTable far *)mem_Lock(cacheTable);
    n = *(int far *)table;
    slot = table->slots;
    if (n > 0) {
        handles = (int far *)((unsigned)((n + 1) * 4) + (long)table);
        count = n;
        do {
            if (slot->id != -1)
                mem_Free(*handles);
            slot++;
            handles++;
        } while (--count);
    }
    mem_Unlock(cacheTable);
    mem_Free(cacheTable);
}
