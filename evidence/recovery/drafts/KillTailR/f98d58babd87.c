/*
 * KillTailR clears the tail's local occupancy byte, reads its direction byte
 * and 8-bit map row from the far Dx8 table, and clears the corresponding
 * 64-wide LifeR entry.  The row is deliberately reduced to its low byte
 * before the six-bit row stride is applied.
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
