/*
 * ch_CleanupTable: lock the cache table, then walk its "count" entries
 * (an array of {id,type} word pairs starting at table+4, paired with a
 * parallel array of memory handles immediately after those entries) from
 * the top down.  A slot already marked empty (id==-1) or holding handle 0
 * is skipped.  A handle that is not yet freed, or still locked, is left
 * alone.  Otherwise the leak is reported as "[(%u)(%u)]" with the id/type,
 * the handle is released, the handle slot zeroed, the id slot marked -1,
 * and the table's active count (table+2) decremented.  After the sweep, a
 * trailing newline is printed, the table handle is unlocked, and the
 * table's remaining active count is returned.
 */
struct CleanupEntry {
    int id;
    int type;
};

extern void far *mem_Lock(unsigned int handle);
extern int far mem_Unlock(unsigned int handle);
extern int mem_Freed(unsigned int handle);

extern int mem_LockLevel(unsigned handle);

extern void far mem_Free(int handle);
extern void far WinPrintf(char far *format, ...);

int far ch_CleanupTable(unsigned int handle)
{
    int far *table;
    struct CleanupEntry far *entry;
    int far *handles;
    int count;
    int h;

    table = (int far *)mem_Lock(handle);
    count = table[0];
    if (count > 0) {
        handles = (int far *)((unsigned long)table + (unsigned int)((count + 1) * 4));
        entry = (struct CleanupEntry far *)((char far *)table + 4);
        do {
            if (entry->id != -1) {
                h = *handles;
                if (h != 0 && mem_Freed(h) && mem_LockLevel(h) == 0) {
                    WinPrintf("[(%u)(%u)]", entry->id, entry->type);
                    mem_Free(h);
                    *handles = 0;
                    entry->id = -1;
                    --table[1];
                }
            }
            entry++;
            handles++;
        } while (--count);
    }
    WinPrintf("\n");
    mem_Unlock(handle);
    return table[1];
}
