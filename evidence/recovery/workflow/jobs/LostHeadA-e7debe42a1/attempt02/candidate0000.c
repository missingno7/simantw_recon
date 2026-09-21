extern signed char far Dx8[];
extern signed char far Dy8[];
extern unsigned char near LifeA[];
extern int far FindInAList(int x, int y);

int near LostHeadA(int y, int x, int life)
{
    int index;
    int column;
    int row;

    index = life & 7;
    column = x + Dy8[index];
    row = y + Dx8[index];
    if (LifeA[(row << 6) + column] - life == -8)
        return 0;
    if (FindInAList(row, column) >= 0)
        return 0;
    return 1;
}
