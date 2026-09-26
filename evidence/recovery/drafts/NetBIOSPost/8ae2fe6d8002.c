/*
 * NetBIOS posts a completion pair through the saved interrupt registers.
 * The pair is appended to the ten-entry NCB ring and the head wraps to zero.
 */
extern unsigned int far ncbHead;
extern unsigned int far ncbSegment[];
extern unsigned int far ncbOffset[];

void interrupt far NetBIOSPost(unsigned int segment, unsigned int offset)
{
    unsigned int slot;

    slot = ncbHead;
    ncbSegment[slot] = segment;
    ncbOffset[slot] = offset;
    ++slot;
    if (slot == 10)
        slot = 0;
    ncbHead = slot;
}
