extern unsigned char far ExitMapB[64][64];
extern unsigned char far ExitMapR[64][64];
extern char far Dx8[];
extern char far Dy8[];
extern int far SRand2(void);
#define EXITMAPB(x,y) ExitMapB[x][y]
#define EXITMAPR(x,y) ExitMapR[x][y]

int far GetEnterDirB(int x, int y, int dir)
{
    int back;
    int bestValue;
    int best;
    int i;
    int nx;
    int ny;
    int value;

    back = dir ^ 4;
    best = -1;
    bestValue = EXITMAPB(x, y);
    for (i = 0; i < 8; i++) {
        if (back == i)
            continue;
        ny = Dy8[i] + y;
        nx = Dx8[i] + x;
        if (nx < 0 || nx > 63 || ny < 0 || ny > 63)
            continue;
        value = EXITMAPB(nx, ny);
        if (value == 0)
            continue;
        if (bestValue < value)
            continue;
        if (bestValue <= value && SRand2() == 0)
            continue;
        bestValue = value;
        best = i;
    }
    return best;
}

int far GetEnterDirR(int x, int y, int dir)
{
    int bestValue;
    int back;
    int best;
    int i;
    int nx;
    int ny;
    int value;

    back = dir ^ 4;
    best = -1;
    bestValue = EXITMAPR(x, y);
    for (i = 0; i < 8; i++) {
        if (back == i)
            continue;
        ny = Dy8[i] + y;
        nx = Dx8[i] + x;
        if (nx < 0 || nx > 63 || ny < 0 || ny > 63)
            continue;
        value = EXITMAPR(nx, ny);
        if (value == 0)
            continue;
        if (bestValue < value)
            continue;
        if (bestValue <= value && SRand2() == 0)
            continue;
        bestValue = value;
        best = i;
    }
    return best;
}
