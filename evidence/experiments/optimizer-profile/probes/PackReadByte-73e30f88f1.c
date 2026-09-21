/*
 * Return one byte from the active packed-input block.  A zero remaining
 * count refills the block through the private far reader, which receives the
 * current far source pointer and the configured block size.  A nonzero
 * reader result asks for another refill; zero means that the current block
 * is ready.  The end marker is returned unchanged.  Otherwise consume one
 * byte, advance only the pointer offset, and leave the segment word intact.
 */
extern unsigned int near PackReadCount;
extern unsigned int near PackReadBlockSize;
extern unsigned char far * near PackReadBuffer;
extern unsigned char far * near PackReadSource;
extern unsigned int (far * near PackReadBlock)(unsigned char far *source,
                                               unsigned int count);

unsigned int far PackReadByte(void)
{
    if (PackReadCount == 0) {
        PackReadBuffer = PackReadSource;
        PackReadCount = PackReadBlock(PackReadBuffer, PackReadBlockSize);
        if (PackReadCount == 0xffff)
            goto empty;
    }

    if (PackReadCount != 0) {
        --PackReadCount;
        return *PackReadBuffer++;
    }

empty:
    PackReadCount = 0;
    return 0xffff;
}
