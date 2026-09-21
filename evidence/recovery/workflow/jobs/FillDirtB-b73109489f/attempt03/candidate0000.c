extern unsigned char near MapB[64][64];
extern unsigned char near LifeB[];
extern unsigned char far ExitMapB[64][64];
extern int far match_position[];

extern void far SmoothEdgesB(int x, int y);

#define CNT  (*(int  far *)((char far *)match_position + 0x72c8))
#define SUMX (*(long far *)((char far *)match_position + 0x8104))
#define SUMY (*(long far *)((char far *)match_position + 0x811a))

void far FillDirtB(int x, int y)
{
    MapB[x][y] = '.';
    LifeB[(x << 6) + y] = 0;

    if (CNT > 1) {
        SUMX -= x;
        if (SUMX < 0)
            SUMX = 0;
        SUMY -= y;
        if (SUMY < 0)
            SUMY = 0;
        --CNT;
    }

    SmoothEdgesB(x, y - 1);
    SmoothEdgesB(x + 1, y);
    SmoothEdgesB(x, y + 1);
    SmoothEdgesB(x - 1, y);

    ExitMapB[x][y] = 0;
}
