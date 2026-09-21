extern unsigned char near MapB[64][64];
extern unsigned char near LifeB[];
extern unsigned char far ExitMapB[64][64];
extern int far dirtMatchCountB;
extern long far dirtMatchSumXB;
extern long far dirtMatchSumYB;

extern void far SmoothEdgesB(int x, int y);

void far FillDirtB(int x, int y)
{
    MapB[x][y] = '.';
    LifeB[(x << 6) + y] = 0;

    if (dirtMatchCountB > 1) {
        dirtMatchSumXB -= x;
        if (dirtMatchSumXB < 0)
            dirtMatchSumXB = 0;
        dirtMatchSumYB -= y;
        if (dirtMatchSumYB < 0)
            dirtMatchSumYB = 0;
        --dirtMatchCountB;
    }

    SmoothEdgesB(x, y - 1);
    SmoothEdgesB(x + 1, y);
    SmoothEdgesB(x, y + 1);
    SmoothEdgesB(x - 1, y);

    ExitMapB[x][y] = 0;
}
