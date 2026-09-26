/*
 * DeleteCurrentIndex (SIMTWO_MODULE, unit simtwo:9A86, same IndexArray/
 * lastTop/mem_malloc/mem_free/Punt objects as _DeleteIndex).
 *
 * DeleteCurrentIndex(recIndex): captures IndexArray[recIndex].data early
 * (used at the very end for mem_free regardless of which path is taken),
 * decrements the record's element count. If the new count is negative it
 * Punts (a bug in the original: the JNE test right after does not
 * distinguish sign, so this falls straight through into the "else"/nonzero
 * path rather than returning). If the new count is exactly 0 the new data
 * pointer becomes a NULL far pointer (nothing to copy). Otherwise it
 * re-fetches the data pointer, allocates a new (smaller) buffer, byte-copies
 * entries [0,lastTop) unchanged, byte-copies entries (lastTop,n] down by one
 * slot (deleting the entry AT the cursor lastTop, unlike _DeleteIndex which
 * deletes at lastTop+1), then stores the new pointer and frees the old one.
 */

struct IndexRec {
    void far *data;
    int count;
    char pad[124 - 6];
};

extern int __based(__segname("PACK")) match_position[];
extern int __based(__segname("PACK")) lastTop;
extern void far Punt(char far *message);
extern void far *mem_malloc(unsigned int size, char far *tag);
extern void mem_free(void far *block);

void far DeleteCurrentIndex(int recIndex)
{
    struct IndexRec __based(__segname("PACK")) *records;
    char far *oldBuf; char far *newBuf; int n; int k;
    records = (struct IndexRec __based(__segname("PACK")) *)&match_position[0x3A2C];
    oldBuf = records[recIndex].data; records[recIndex].count--; n = records[recIndex].count;
    if (n < 0) Punt("DeleteCurrentIndex: count underflow");
    if (n == 0) newBuf = 0;
    else {
        oldBuf = records[recIndex].data; newBuf = mem_malloc(n * 8, "DeleteCurrentIndex");
        if (!newBuf) Punt("DeleteCurrentIndex: out of memory");
        { unsigned int far *src = (unsigned int far *)oldBuf; unsigned int far *dst = (unsigned int far *)newBuf;
          for (k = 0; k < lastTop * 4; ++k) *dst++ = *src++; }
        for (k = 0; k < (n-lastTop)*4; ++k)
            ((unsigned int far *)newBuf)[lastTop*4+k] = ((unsigned int far *)oldBuf)[(lastTop+1)*4+k];
    }
    records[recIndex].data = newBuf; mem_free(oldBuf);
}
