/* GetForageDir: follow the strongest neighboring pheromone gradient. */
extern unsigned char far PherMapBT[];
extern char far Dx8[];
extern char far Dy8[];
extern char far TurnTab[][8];
extern int far SRand1(int range);
extern int far SRand8(void);

int far GetForageDir(int x, int y, int dir, int attribute)
{
    int mapOffset;
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
    mapOffset = xCell * 32 + yCell;
    if (plane)
        current = PherMapBT[mapOffset + 0x1000];
    else
        current = PherMapBT[mapOffset];

    bestDir = SRand8();
    best = 0;
    for (i = 0; i < 8; ++i) {
        nx = xCell + Dx8[i];
        nx &= 0x3f;
        ny = yCell + Dy8[i];
        ny &= 0x1f;
        if (plane)
            value = PherMapBT[nx * 32 + ny + 0x1000];
        else
            value = PherMapBT[nx * 32 + ny];
        if (value > best) {
            best = value;
            bestDir = i;
        }
    }
    if (best <= 0)
        return TurnTab[dir][SRand8()];
    if (current > best)
        return -1;
    return TurnTab[dir][bestDir];
}
