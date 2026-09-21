extern char far Dx8[];
extern char far Dy8[];
extern int far BlkQueens;

extern void far DigTileB(int x, int y);
extern void far AddAntToBList(int x, int y, int type, int a, int b);

void far MakeBlkQueen(int x, int y, int dir)
{
    int d;

    d = dir ^ 4;
    DigTileB(x, y);
    DigTileB(x + Dx8[d], y + Dy8[d]);
    DigTileB(x + 2 * Dx8[d], y + 2 * Dy8[d]);
    AddAntToBList(x, y, dir + 0x60, 9, 0);
    AddAntToBList(x + Dx8[d], y + Dy8[d], dir + 0x68, 9, 0);
    BlkQueens++;
}
