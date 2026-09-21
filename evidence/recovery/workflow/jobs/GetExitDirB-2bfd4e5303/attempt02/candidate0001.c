/*
 * GetExitDirB: choose the direction for a B-colony ant at (x, y) to leave
 * the map, avoiding the reverse of dir (dir ^ 4).  On the edge row 1 the
 * answer is 1 when the column's row-0 MapB cell is the nest entrance
 * (0x18), otherwise a random 3, 7, 11 or 15.  Elsewhere the eight
 * neighbours (far Dx8/Dy8 deltas) inside the 64x64 map are scored by the far
 * ExitMapB; the highest score wins and the result is
 * that direction plus one, or 0 when nothing scores above zero.
 */
extern unsigned char near MapB[64][64];
extern char far Dx8[];
extern char far Dy8[];
extern unsigned char far ExitMapB[64][64];
extern int far SRand2(void);

int far GetExitDirB(int x, int y, int dir)
{
    int back;
    int best;
    int bestValue;
    int i;
    int nx;
    int ny;
    int value;

    if (y == 1) {
        if (MapB[x][0] == 0x18)
            return 1;
        return SRand2() * 4 + 3;
    }
    back = dir ^ 4;
    best = 0;
    bestValue = 0;
    for (i = 0; i < 8; i++) {
        ny = Dy8[i] + y;
        nx = Dx8[i] + x;
        if (nx < 0 || nx > 63 || ny < 0 || ny > 63)
            continue;
        value = ExitMapB[(nx << 6) + ny];
        if (value > bestValue && back != i) {
            bestValue = value;
            best = i + 1;
        }
    }
    return best;
}
