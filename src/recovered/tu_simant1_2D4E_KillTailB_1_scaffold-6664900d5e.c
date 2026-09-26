/* Candidate translation unit simant1_2D4E_KillTailB_1_scaffold: composed from preserved exact-body sources
 * in MAPSYM order. Internal evidence id, not a historical filename.
 * Members: _KillTailB
 * SCAFFOLDED: claimed members in 1 code runs; no pool stand-ins were needed. */

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

