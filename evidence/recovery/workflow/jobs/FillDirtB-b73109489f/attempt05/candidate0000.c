extern unsigned char near MapB[64][64];
extern unsigned char near LifeB[];
extern unsigned char far ExitMapB[64][64];
extern volatile int far match_position[];

extern void far SmoothEdgesB(int x, int y);

#define CNT   (match_position[0x3964])
#define SUMX  (*(long volatile far *)&match_position[0x4082])
#define SUMY  (*(long volatile far *)&match_position[0x408d])

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
