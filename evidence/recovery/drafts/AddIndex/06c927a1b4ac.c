/*
 * AddIndex (SIMTWO_MODULE, unit simtwo:9A86, same IndexArray/lastTop/
 * mem_malloc/mem_free/Punt/FindIndex objects as _DeleteIndex and
 * _DeleteCurrentIndex; mem_malloc(size, tag) per that call-site evidence).
 *
 * AddIndex(recIndex, p2, p3, p4, payload): Punts (and returns 0) if
 * FindIndex(recIndex, p2, p3) already finds a match -- duplicates are not
 * allowed. Otherwise it packs (payload, p2, p3, p4) into one 8-byte entry
 * (a far pointer, a word, then two bytes -- matches the local frame slots
 * [bp-0x12..bp-0xe]=payload, [bp-0xe]=p2, [bp-0xc]=p3 byte, [bp-0xb]=p4
 * byte), bumps IndexArray[recIndex].count, and allocates a new buffer sized
 * for the new count. If this is the first entry (count==1) it just frees
 * any stale old buffer and copies the entry in. Otherwise it byte-copies
 * entries [0,lastTop) unchanged, struct-copies the new entry in at position
 * lastTop, byte-copies the old entries at/after lastTop up by one slot, and
 * frees the old buffer. Finally it stores the new pointer through a cached
 * &IndexArray[recIndex].data and returns 1.
 */

struct IndexRec {
    void far *data;
    int count;
    char pad[124 - 6];
};

struct IndexEntry {
    void far *payload;
    int p2;
    unsigned char p3;
    unsigned char p4;
};

extern struct IndexRec far IndexArray[];
extern int far lastTop;
extern int far FindIndex(int recIndex, int p2, int p3);
extern void far Punt(char far *message);
extern void far *mem_malloc(unsigned int size, char far *tag);
extern void mem_free(void far *block);
extern void far *memcpy(void far *dst, const void far *src, unsigned int count);

int far AddIndex(int recIndex, int p2, int p3, int p4, void far *payload)
{
    void far *far *pdata;
    void far *oldBuf;
    void far *newBuf;
    struct IndexEntry entry;
    unsigned char far *nb;
    unsigned char far *ob;
    int n;
    int cnt1;
    int cnt2;
    int k;

    pdata = &IndexArray[recIndex].data;
    oldBuf = IndexArray[recIndex].data;

    if (FindIndex(recIndex, p2, p3) != 0) {
        Punt("AddIndex: duplicate index");
        return 0;
    }

    entry.payload = payload;
    entry.p2 = p2;
    entry.p3 = (unsigned char)p3;
    entry.p4 = (unsigned char)p4;

    IndexArray[recIndex].count++;
    n = IndexArray[recIndex].count;

    newBuf = mem_malloc(n * 8, "AddIndex");
    if (newBuf == 0)
        Punt("AddIndex: out of memory");

    if (IndexArray[recIndex].count == 1) {
        if (oldBuf != 0)
            mem_free(oldBuf);
        *(struct IndexEntry far *)newBuf = entry;
    } else {
        oldBuf = IndexArray[recIndex].data;

        nb = newBuf;
        ob = oldBuf;
        cnt1 = lastTop * 8;
        memcpy(nb, ob, cnt1);

        *(struct IndexEntry far *)(nb + lastTop * 8) = entry;

        cnt2 = (n - lastTop - 1) * 8;
        memcpy(nb + (lastTop + 1) * 8, ob + lastTop * 8, cnt2);

        mem_free(oldBuf);
    }

    *pdata = newBuf;
    return 1;
}
