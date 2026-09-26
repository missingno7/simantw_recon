/*
 * KillTailB clears the tail's local occupancy byte, reads its direction byte
 * and 8-bit map row from the far Dx8 table, and clears the corresponding
 * 64-wide LifeB entry.  The low-byte mask is intentional: the historical
 * routine converts the stored word row into a row offset before indexing.
 */
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) BlistT[];
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) BlistY[];
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) BlistX[];
extern unsigned char near LifeB[];

void KillTailB(int tail)
{
    unsigned char direction;
    unsigned int row;

    BlistT[tail] = 0;
    direction = BlistY[tail];
    row = *(unsigned int far *)(BlistX + tail);
    row &= 0xff;
    row <<= 6;
    LifeB[row + direction] = 0;
}
