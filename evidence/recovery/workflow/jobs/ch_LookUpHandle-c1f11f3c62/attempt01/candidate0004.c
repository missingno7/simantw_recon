/*
 * ch_LookUpHandle: find a key in a locked lookup table.  The table starts
 * with its entry count; the two-word entries follow at offset 4 and the
 * key words follow the entries (the address is formed with carry into the
 * segment).  Each used entry (first word not -1) whose key matches
 * returns its two words through the far result pointers and 1; otherwise
 * 0.  The table handle is unlocked either way.
 */
struct ChEntry {
    int a;
    int b;
};

struct ChTable {
    int count;
    int pad;
    struct ChEntry entries[1];
};

extern void far *mem_Lock(unsigned int handle);
extern int far mem_Unlock(unsigned int handle);

int far ch_LookUpHandle(int key, unsigned int table, int far *outA, int far *outB)
{
    struct ChTable far *t;
    struct ChEntry far *entry;
    int far *keys;
    int count;
    int i;

    t = mem_Lock(table);
    count = t->count;
    entry = t->entries;
    keys = (int far *)((char huge *)t + (long)(count + 1) * 4);
    for (i = 0; i < count; i++, entry++, keys++) {
        if (entry->a != -1 && *keys == key) {
            *outA = entry->a;
            *outB = entry->b;
            mem_Unlock(table);
            return 1;
        }
    }
    mem_Unlock(table);
    return 0;
}
