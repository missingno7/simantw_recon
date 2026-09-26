/*
 * DeleteIndex (SIMTWO_MODULE, unit simtwo:9A86: OpenIndex/CreateIndex/
 * CloseIndex/FindIndex/DeleteCurrentIndex/AddIndex/DeleteIndex share one
 * 124-byte-stride record array and the global cursor "lastTop").
 *
 * DeleteIndex(recIndex, b, c): validates (recIndex,b,c) through FindIndex
 * (near call within this unit; only its found/not-found status is used
 * here) and Punts if not found. It then removes the index entry that sits
 * right after the current cursor (lastTop+1) from IndexArray[recIndex]'s
 * dynamically-allocated array of 8-byte entries: decrement the record's
 * element count, allocate a new (smaller) buffer, byte-copy the entries
 * before and including lastTop unchanged, byte-copy the entries after the
 * deleted one down by one slot, free the old buffer and store the new one.
 * The private record struct's exact field layout is evidence-backed only
 * for a far data pointer at +0 and a count word at +4 (observed
 * es:[bx+0x7458]/es:[bx+0x745a] and es:[bx+0x745c] on the same 0x7C-stride
 * base); the remaining 118 bytes/record are unresolved padding.
 *
 * This call site pushes 3 words (ds, a near string offset, then the size)
 * before calling mem_malloc and cleans up 6 bytes after the call. The tag
 * pushes happen first (early, before the size is even computed) and the
 * size is pushed last right before the call, which for this codebase's
 * consistent right-to-left push order means the tag is the second
 * (rightmost) declared parameter and the size is the first: mem_malloc
 * here is (size, tag), unlike the plain 1-arg forwarding wrapper in
 * mem_malloc.c (cross-TU prototype identity is not proven; this is the
 * call site's own evidence).
 */

struct IndexRec {
    void far *data;
    int count;
    char pad[124 - 6];
};

extern struct IndexRec far IndexArray[];
extern int far lastTop;
extern void far *FindIndex(int recIndex, int b, int c);
extern void far Punt(char far *message);
extern void far *mem_malloc(unsigned int size, char far *tag);
extern void mem_free(void far *block);

int far DeleteIndex(int recIndex, int b, int c)
{
    unsigned off;
    char far *newBuf;
    char far *oldBuf;
    int n;
    int k;
    int cnt1;
    int cnt2;

    if (FindIndex(recIndex, b, c) == 0)
        Punt("DeleteIndex: index not found");

    off = recIndex * 0x7c;
    (*(int far *)((char far *)IndexArray + off + 4))--;
    n = *(int far *)((char far *)IndexArray + off + 4);

    newBuf = mem_malloc(n * 8, "DeleteIndex");
    if (newBuf == 0)
        Punt("DeleteIndex: out of memory");

    oldBuf = *(char far * far *)((char far *)IndexArray + off);

    for (k = 0; k < (lastTop + 1) * 8; k++)
        newBuf[k] = oldBuf[k];

    for (k = 0; k < (n - lastTop - 1) * 8; k++)
        newBuf[(lastTop + 1) * 8 + k] = oldBuf[(lastTop + 2) * 8 + k];

    mem_free(oldBuf);

    *(char far * far *)((char far *)IndexArray + off) = newBuf;
}
