/*
 * KillTailR clears RlistT[tail], reads the direction byte from RlistY and
 * the row word from RlistX, then clears the matching LifeR cell.  The
 * low-byte mask preserves the historical conversion to a 64-byte row.
 */
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) RlistT[];
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) RlistY[];
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) RlistX[];
extern unsigned char near LifeR[];

void KillTailR(int tail)
{
    unsigned char direction;
    unsigned int row;

    RlistT[tail] = 0;
    direction = RlistY[tail];
    row = *(unsigned int far *)(RlistX + tail);
    row &= 0xff;
    row <<= 6;
    LifeR[row + direction] = 0;
}
