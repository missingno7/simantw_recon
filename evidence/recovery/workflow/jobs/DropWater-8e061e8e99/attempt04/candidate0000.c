extern unsigned char near MapB[64][64];
extern unsigned char near MapR[64][64];

extern int far SRand1(int range);
extern void far ZapEuMapAt(int plane, int x, int y);

void far DropWater(int y)
{
    int x;
    int v;

    for (x = 0; x < 64; x++) {
        v = MapB[x][y];
        v = (v == 0x4e) ? SRand1(8) : v - 0x2f;
        MapB[x][y] = v;

        v = MapR[x][y];
        v = (v == 0x4e) ? SRand1(8) : v - 0x2f;
        MapR[x][y] = v;

        ZapEuMapAt(2, x, y);
        ZapEuMapAt(3, x, y);
    }
}
