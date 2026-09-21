/*
 * GetEnterDirB: choose the direction for a B-colony ant to enter the map
 * at (x, y) arriving from direction dir.  The reverse direction (dir ^ 4)
 * is never taken.  Every other of the eight neighbours inside the 64x64
 * far ExitMapB (SIMANT_DATA_GROUP byte map) with a nonzero exit value is
 * a candidate; the lowest value wins, starting from the value of the
 * current cell, and an equal value replaces the current choice only when
 * SRand2 says so.  Returns the chosen direction or -1.
 */
extern unsigned char far ExitMapB[64][64];
#define EXITMAP(x, y) ExitMapB[x][y]
extern char far Dx8[];
extern char far Dy8[];
extern int far SRand2(void);

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
    bestValue = EXITMAP(x, y);
    for (i = 0; i < 8; i++) {
        if (back == i)
            continue;
        ny = Dy8[i] + y;
        nx = Dx8[i] + x;
        if (nx < 0 || nx > 63 || ny < 0 || ny > 63)
            continue;
        value = EXITMAP(nx, ny);
        if (value == 0)
            continue;
        if (bestValue < value)
            continue;
        if (bestValue == value && SRand2() == 0)
            continue;
        bestValue = value;
        best = i;
    }
    return best;
}
