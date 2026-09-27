/*
 * NetBIOS posts a completion pair through the saved interrupt registers.
 * The pair is appended to the ten-entry NCB ring and the head wraps to zero.
 */
extern unsigned int far ncbHead;
extern unsigned int far ncbSegment[];
extern unsigned int far ncbOffset[];

void interrupt far NetBIOSPost(unsigned int segment,
                               unsigned int savedDS,
                               unsigned int savedDI,
                               unsigned int savedSI,
                               unsigned int savedBP,
                               unsigned int savedSP,
                               unsigned int offset)
{
    unsigned int slot;

    slot = ncbHead;
    ncbSegment[slot] = segment;
    ncbOffset[slot] = offset;
    ++ncbHead;
    if (ncbHead == 10)
        ncbHead = 0;
}
