/* GetForageDir: follow the strongest neighboring pheromone gradient. */
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) PherMapBT[64][32];
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) PherMapRT[64][32];
extern char far Dx8[];
extern char far Dy8[];
extern char far TurnTab[][8];
extern int far SRand1(int range);
extern int far SRand8(void);

int far GetForageDir(int x, int y, int dir, int attribute)
{
    int xCell;
    int yCell;
    int plane;
    int best;
    int bestDir;
    int i;
    int nx;
    int ny;
    int current;
    int value;

    if (x == 0) {
        if (y == 0)
            return 3;
        if (y == 63)
            return 1;
        return SRand1(3) + 1;
    }
    if (y == 0) {
        if (x == 127)
            return 5;
        return SRand1(3) + 3;
    }
    if (x == 127) {
        if (y == 63)
            return 7;
        return SRand1(3) + 5;
    }
    if (y == 63)
        return (SRand1(3) - 1) & 7;

    xCell = x >> 1;
    yCell = y >> 1;
    plane = attribute & 0x80;
    if (plane)
        current = PherMapRT[xCell][yCell];
    else
        current = PherMapBT[xCell][yCell];

    best = 0;
    bestDir = SRand8();
    for (i = 0; i < 8; ++i) {
        nx = xCell + Dx8[i];
        nx &= 0x3f;
        ny = yCell + Dy8[i];
        ny &= 0x1f;
        if (plane)
            value = PherMapRT[nx][ny];
        else
            value = PherMapBT[nx][ny];
        if (value > best) {
            best = value;
            bestDir = i;
        }
    }
    if (best > 0) {
        if (current > best)
            return -1;
        return TurnTab[dir][bestDir];
    }
    return TurnTab[dir][SRand8()];
}
