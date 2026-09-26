extern unsigned char near MapB[64][64];
extern unsigned char near MapR[64][64];

extern int far SRand1(int range);
extern void far ZapEuMapAt(int plane, int x, int y);

void far DropWater(int y)
{
    int col;
    int x;
    int oldValue;
    int newValue;
    col = y;

    for (x = 0; x < 64; x++) {
        oldValue = MapB[x][col];
        if (oldValue == 0x4e)
            newValue = SRand1(8);
        else
            newValue = oldValue - 0x2f;
        MapB[x][col] = newValue;

        oldValue = MapR[x][col];
        if (oldValue == 0x4e)
            newValue = SRand1(8);
        else
            newValue = oldValue - 0x2f;
        MapR[x][col] = newValue;

        ZapEuMapAt(2, x, col);
        ZapEuMapAt(3, x, col);
    }
}
