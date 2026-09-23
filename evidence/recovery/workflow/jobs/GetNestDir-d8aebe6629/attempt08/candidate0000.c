/* Choose a heading toward the nest using edge rules and neighboring pheromone. */
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) PherMapBN[64][32];
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) PherMapRN[64][32];
extern char far Dx8[];
extern char far Dy8[];
extern char far TurnTab[][8];
extern int far SRand1(int range);
extern int far SRand2(void);
extern int far SRand4(void);
extern int far SRand8(void);
extern int far GetDir(int x1, int y1, int x2, int y2);
extern int far LastNewHoleB[];
extern int far LastNewHoleR[];

int far GetNestDir(int x, int y, int dir, int attribute)
{
    int r;
    int xCell;
    int yCell;
    int plane;
    int best;
    int bestDir;
    int i;
    int nx;
    int ny;
    int value;
    int current;
    int nestDir;
    xCell = x >> 1;
    yCell = y >> 1;
    plane = attribute >> 7;

    if (x == 0) {
        if (y == 0)
            r = SRand1(3) + 3;
        else if (y == 63)
            r = SRand1(3) + 1;
        else
            r = SRand1(5) + 1;
    } else if (y == 0) {
        if (x == 127)
            r = SRand1(3) + 5;
        else
            r = SRand1(5) + 3;
    } else if (x == 127) {
        if (y == 63)
            r = SRand1(3) + 7;
        else
            r = SRand1(5) + 5;
    } else if (y == 63) {
        r = SRand1(5) + 7;
    } else {
        r = 0;
    }
    if (r != 0)
        return (unsigned char)r - 1 & 7;

    if (plane == 0)
        current = PherMapBN[xCell][yCell];
    else
        current = PherMapRN[xCell][yCell];
    if (current == 0)
        goto nestFallback;
    best = 0;
    bestDir = 0;
    for (i = 0; i < 8; ++i) {
        nx = (xCell + Dx8[i]) & 0x3f;
        ny = (yCell + Dy8[i]) & 0x1f;
        if (plane)
            value = PherMapRN[nx][ny];
        else
            value = PherMapBN[nx][ny];
        if (value > best) {
            best = value;
            bestDir = i;
        }
    }
    if (SRand2())
        return TurnTab[dir][bestDir];
    return TurnTab[dir][(bestDir + 1) & 7];

nestFallback:
    if (plane)
        nestDir = GetDir(x, y, LastNewHoleR[0], LastNewHoleR[1]);
    else
        nestDir = GetDir(x, y, LastNewHoleB[0], LastNewHoleB[1]);
    if (nestDir != 0 && SRand4())
        return TurnTab[dir][nestDir - 1];
    return TurnTab[dir][SRand8()];
}







