/* First readable pass over the periodic population/map accounting. */
extern int __based(__segname("PACK")) YardCycle;
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) YMapPopB[192];
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) YMapPopR[192];
extern int near ColonyTotalBlack;
extern int near ColonyTotalRed;

void far SimColonies(void)
{
    int x;
    int y;
    int cell;
    int blackCount;
    int redCount;

    if (YardCycle & 0x1f)
        return;

    blackCount = 0;
    redCount = 0;
    for (x = 0; x < 12; x++) {
        for (y = 0; y < 16; y++) {
            cell = (x << 4) + y;
            if (YMapPopB[cell] != 0)
                blackCount++;
            if (YMapPopR[cell] != 0)
                redCount++;
        }
    }

    ColonyTotalBlack = blackCount;
    ColonyTotalRed = redCount;
}
