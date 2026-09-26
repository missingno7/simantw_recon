/*
 * Preserve the packed byte cursor across refill.  Keep the reader result in a
 * register value while copying it into the shared remaining-byte counter;
 * its nonzero result returns through the common count check at retry.
 */
extern unsigned int near PackReadCount;
extern unsigned int near PackReadBlockSize;
extern unsigned char far * near PackReadBuffer;
extern unsigned char far * near PackReadSource;
extern unsigned int (far * near PackReadBlock)(unsigned char far *source,
                                               unsigned int count);

unsigned int far PackReadByte(void)
{
    register unsigned int result;

retry:
    if (PackReadCount != 0) {
        --PackReadCount;
        return *PackReadBuffer++;
    }

    PackReadBuffer = PackReadSource;
    result = PackReadBlock(PackReadBuffer, PackReadBlockSize);
    PackReadCount = result;
    if (result == 0xffff)
        goto empty;
    if (result != 0)
        goto retry;

empty:
    PackReadCount = 0;
    return 0xffff;
}
