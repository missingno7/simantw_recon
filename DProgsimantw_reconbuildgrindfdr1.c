extern unsigned char near MapR[64][64];
extern unsigned char near LifeR[];
extern unsigned char far ExitMapR[64][64];
extern int far TilesDugR;
extern long far TileTotXR;
extern long far TileTotYR;

extern void far SmoothEdgesR(int x, int y);

#define CNT TilesDugR

void far FillDirtR(int x, int y)
{
    MapR[x][y] = '.';
    LifeR[(x << 6) + y] = 0;

    if (CNT > 1) {
        TileTotXR -= x;
        if (TileTotXR < 0)
            TileTotXR = 0;
        TileTotYR -= y;
        if (TileTotYR < 0)
            TileTotYR = 0;
        --CNT;
    }

    SmoothEdgesR(x, y - 1);
    SmoothEdgesR(x + 1, y);
    SmoothEdgesR(x, y + 1);
    SmoothEdgesR(x - 1, y);

    ExitMapR[x][y] = 0;
}
