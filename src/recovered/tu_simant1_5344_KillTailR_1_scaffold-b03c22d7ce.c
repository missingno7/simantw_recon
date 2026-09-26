/* Candidate translation unit simant1_5344_KillTailR_1_scaffold: composed from preserved exact-body sources
 * in MAPSYM order. Internal evidence id, not a historical filename.
 * Members: _KillTailR
 * SCAFFOLDED: claimed members in 1 code runs; no pool stand-ins were needed. */

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

