/* DropWater scans one MapB/MapR column across all 64 rows; it replaces 0x4e with SRand1(8), subtracts 0x2f from every other tile, then invalidates planes 2 and 3. Separate old-value and result temporaries preserve the observed update sequence. */
extern unsigned char near MapB[64][64];
extern unsigned char near MapR[64][64];

extern int far SRand1(int range);
extern void far ZapEuMapAt(int plane, int x, int y);

void far DropWater(int y)
{
    int x;
    int v;
    int t;

    for (x = 0; x < 64; x++) {
        v = MapB[x][y];
        if (v == 0x4e)
            t = SRand1(8);
        else
            t = v - 0x2f;
        v = t;
        MapB[x][y] = v;

        v = MapR[x][y];
        if (v == 0x4e)
            t = SRand1(8);
        else
            t = v - 0x2f;
        v = t;
        MapR[x][y] = v;

        ZapEuMapAt(2, x, y);
        ZapEuMapAt(3, x, y);
    }
}
