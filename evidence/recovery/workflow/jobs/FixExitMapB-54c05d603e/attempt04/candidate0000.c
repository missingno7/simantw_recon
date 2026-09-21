extern unsigned char near MapB[64][64];
extern unsigned char far Dx8;
#define AT(off) ((&Dx8)[off])
#define DX(off) (*(signed char far *)&AT(off))

void far FixExitMapB(int x, int y)
{
    int i;
    int nx;
    int ny;
    int value;
    int best;
    unsigned char far *p;

    if (y < 2) {
        p = &AT(0x3a4 + (x << 6) + y);
        if (MapB[x][y] == 0x18) {
            *p = 0xff;
            return;
        }
        p = &AT(0x3a4 + (x << 6) + y);
        *p = 0xfe;
        return;
    }
    best = 0;
    for (i = 0; i < 8; i++) {
        ny = DX(8 + i) + y;
        nx = DX(i) + x;
        if (nx < 0 || nx > 63 || ny < 0 || ny > 63)
            continue;
        value = AT(0x3a4 + (nx << 6) + ny);
        if (value > best)
            best = value;
    }
    if (best)
        AT(0x3a4 + (x << 6) + y) = best - 1;
    else
        AT(0x3a4 + (x << 6) + y) = 0;
}
