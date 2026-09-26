/*
 * KillTailB clears BlistT[tail], reads the direction byte from BlistY and
 * the row word from BlistX, then clears the matching LifeB cell.  The
 * low-byte mask preserves the historical conversion to a 64-byte row.
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
