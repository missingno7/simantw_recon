extern unsigned char near MapB[64][64];
extern unsigned char near MapR[64][64];

extern int far SRand1(int range);
extern void far ZapEuMapAt(int plane, int x, int y);

void far DropWater(int y)
{
    int x;
    int bv;
    int rv;

    for (x = 0; x < 64; x++) {
        bv = MapB[x][y];
        if (bv == 0x4e)
            bv = SRand1(8);
        else
            bv -= 0x2f;
        MapB[x][y] = bv;

        rv = MapR[x][y];
        if (rv == 0x4e)
            rv = SRand1(8);
        else
            rv -= 0x2f;
        MapR[x][y] = rv;

        ZapEuMapAt(2, x, y);
        ZapEuMapAt(3, x, y);
    }
}
