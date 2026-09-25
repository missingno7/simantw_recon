extern char far Dx8[];
extern char far Dy8[];
extern int far RedQueens;

extern void far DigTileR(int x, int y);
extern void far AddAntToRList(int x, int y, int type, int a, int b);

void far MakeRedQueen(int x, int y, int dir)
{
    int d;

    d = dir ^ 4;
    DigTileR(x, y);
    DigTileR(x + Dx8[d], y + Dy8[d]);
    DigTileR(x + 2 * Dx8[d], y + 2 * Dy8[d]);
    AddAntToRList(x, y, dir + 0xE0, 9, 0);
    AddAntToRList(x + Dx8[d], y + Dy8[d], dir + 0xE8, 9, 0);
    RedQueens++;
}
