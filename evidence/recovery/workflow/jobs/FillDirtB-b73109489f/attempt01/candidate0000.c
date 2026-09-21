extern unsigned char near MapB[64][64];
extern unsigned char near LifeB[];
extern unsigned char far ExitMapB[64][64];
extern int far match_position[];

extern void far SmoothEdgesB(int x, int y);

#define SumX (*(long far *)&match_position[0x4082])
#define SumY (*(long far *)&match_position[0x408d])

void far FillDirtB(int x, int y)
{
    MapB[x][y] = '.';
    LifeB[(x << 6) + y] = 0;

    if (match_position[0x3964] > 1) {
        SumX -= x;
        if (SumX < 0)
            SumX = 0;
        SumY -= y;
        if (SumY < 0)
            SumY = 0;
        --match_position[0x3964];
    }

    SmoothEdgesB(x, y - 1);
    SmoothEdgesB(x + 1, y);
    SmoothEdgesB(x, y + 1);
    SmoothEdgesB(x - 1, y);

    ExitMapB[x][y] = 0;
}
