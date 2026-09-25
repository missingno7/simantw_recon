/*
 * KillTailB clears the tail's local occupancy byte, reads its direction byte
 * and 8-bit map row from the far Dx8 table, and clears the corresponding
 * 64-wide LifeB entry.  The low-byte mask is intentional: the historical
 * routine converts the stored word row into a row offset before indexing.
 */
extern unsigned char far Dx8[];
extern unsigned char near LifeB[];

void KillTailB(int tail)
{
    unsigned char direction;
    unsigned int row;

    Dx8[tail + 0x3d18] = 0;
    direction = Dx8[tail + 0x392c];
    row = *(unsigned int far *)(Dx8 + tail + 0x3736);
    row &= 0xff;
    row <<= 6;
    LifeB[row + direction] = 0;
}
