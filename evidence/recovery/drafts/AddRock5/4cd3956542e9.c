/* Validate the 5 by 5 mask before placing its nonzero bytes. */
extern unsigned char near MapA[128][64];
extern unsigned char far Dx8[];
void far AddRock5(int x, int y, int id)
{
    volatile int id5;
    volatile int r5;
    int ypos;
    int row;
    int col;
    int base;

    id5 = id * 5;
    row = 0;
    ypos = x * 64;
    r5 = id5 * 5;
    for (; row < 5; row++) {
        base = r5 + row;
        base += 0x870a;
        for (col = 0; col < 5; col++) {
            if (Dx8[base] != 0) {
                if (MapA[0][y + ypos + col] > 0x10)
                    return;
            }
            base += 5;
        }
        ypos += 0x40;
    }

    row = 0;
    ypos = x * 64;
    r5 = id5 * 5;
    for (; row < 5; row++) {
        base = r5 + row;
        base += 0x870a;
        for (col = 0; col < 5; col++) {
            int v = Dx8[base];
            if (v != 0)
                MapA[0][y + ypos + col] = v;
            base += 5;
        }
        ypos += 0x40;
    }
}
