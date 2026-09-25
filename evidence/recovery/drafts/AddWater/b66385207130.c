extern unsigned char near MapB[64][64];
extern unsigned char near MapR[64][64];

extern void far DrownBList(int y);
extern void far DrownRList(int y);
extern void far ZapEuMapAt(int plane, int x, int y);

void far AddWater(int y)
{
    int x;
    int v;
    int t;

    DrownBList(y);
    DrownRList(y);

    for (x = 0; x < 64; x++) {
        v = MapB[x][y];
        if (v < 0x20)
            t = 0x4e;
        else
            t = v + 0x2f;
        v = t;
        MapB[x][y] = v;

        v = MapR[x][y];
        if (v < 0x20)
            t = 0x4e;
        else
            t = v + 0x2f;
        v = t;
        MapR[x][y] = v;

        ZapEuMapAt(2, x, y);
        ZapEuMapAt(3, x, y);
    }
}
