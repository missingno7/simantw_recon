/* Candidate translation unit simant1_0000_LostHeadA_1: composed from preserved exact-body sources
 * in MAPSYM order. Internal evidence id, not a historical filename.
 * Members: _LostHeadA */

extern signed char far Dx8[];
extern signed char far Dy8[];
extern unsigned char near LifeA[];
extern int far FindInAList(int x, int y);

int near LostHeadA(int y, int x, int life)
{
    int index;
    int row;
    int column;

    index = life & 7;
    column = y + Dy8[index];
    row = x + Dx8[index];
    if (LifeA[(column << 6) + row] - life == -8)
        return 0;
    if (FindInAList(column, row) >= 0)
        return 0;
    return 1;
}

