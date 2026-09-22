extern unsigned char near MapB[64][64];
extern unsigned char near LifeB[];
extern unsigned char far ExitMapB[64][64];
extern int far TilesDugB;
extern long far TileTotXB;
extern long far TileTotYB;

extern void far SmoothEdgesB(int x, int y);

#define CNT TilesDugB

void far FillDirtB(int x, int y)
{
    MapB[x][y] = '.';
    LifeB[(x << 6) + y] = 0;

    if (CNT > 1) {
        TileTotXB -= x;
        if (TileTotXB < 0)
            TileTotXB = 0;
        TileTotYB -= y;
        if (TileTotYB < 0)
            TileTotYB = 0;
        --CNT;
    }

    SmoothEdgesB(x, y - 1);
    SmoothEdgesB(x + 1, y);
    SmoothEdgesB(x, y + 1);
    SmoothEdgesB(x - 1, y);

    ExitMapB[x][y] = 0;
}
