/* Candidate translation unit simone_12E4: composed from preserved exact-body sources
 * in MAPSYM order. Internal evidence id, not a historical filename.
 * Members: _GetEnterDirB, _GetEnterDirR */

extern unsigned char far ExitMapB[64][64];
extern char far Dx8[];
extern char far Dy8[];
extern int far SRand2(void);
extern unsigned char far ExitMapR[64][64];

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
    bestValue = ExitMapB[x][y];
    for (i = 0; i < 8; i++) {
        if (back == i)
            continue;
        ny = Dy8[i] + y;
        nx = Dx8[i] + x;
        if (nx < 0 || nx > 63 || ny < 0 || ny > 63)
            continue;
        value = ExitMapB[nx][ny];
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
    int back;
    int bestValue;
    int best;
    int i;
    int nx;
    int ny;
    int value;

    back = dir ^ 4;
    best = -1;
    bestValue = ExitMapR[x][y];
    for (i = 0; i < 8; i++) {
        if (back == i)
            continue;
        ny = Dy8[i] + y;
        nx = Dx8[i] + x;
        if (nx < 0 || nx > 63 || ny < 0 || ny > 63)
            continue;
        value = ExitMapR[nx][ny];
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

