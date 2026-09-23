extern unsigned char near MapB[64][64];
extern unsigned char far Dx8;
#define AT(off) ((&Dx8)[off])
#define DX(off) (*(signed char far *)&AT(off))

void far FixExitMapB(int x, int y)
{
    int i;
    int best;
    int nx;
    int ny;
    int value;

    if (y < 2) {
        if (MapB[x][y] == 0x18)
            AT(0x3a4 + (x << 6) + y) = 0xff;
        else
            AT(0x3a4 + (x << 6) + y) = 0xfe;
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
    if (best != 0)
        AT(0x3a4 + (x << 6) + y) = best - 1;
    else
        AT(0x3a4 + (x << 6) + y) = 0;
}

/*
 * FloodNestB updates the B-side nest cells in the shared map.  Each row
 * starts at offset three and spans the remaining 0x3d cells.  Values in the
 * flooding band 0x20..0x2d receive the flood increment; low values at or
 * below 0x13 become the full-water marker 0x50.
 */

void FloodNestB(void)
{
    int row;
    int cell;
    int value;
    unsigned char near *p;

    for (row = 0; row < 0x1000; row += 0x40) {
        for (cell = 3; cell < 0x40; ++cell) {
            p = ((unsigned char near *)MapB) + row + cell;
            value = *p;
            if (value >= 0x20 && value <= 0x2d)
                *p += 0x31;
            else if (*p <= 0x13)
                *p = 0x50;
        }
    }
}
