/* Semantic hypothesis: loop-clause initialization keeps the outer index in its register home. */
/* Scan the complete mask for blocked destinations before copying its nonzero bytes. */
extern unsigned char near MapA[128][64];
extern unsigned char far Dx8;
#define AT(off) ((&Dx8)[off])

void far AddRock5(int x, int y, int id)
{
    int id5;
    int r5;
    int ypos;
    int row;
    int col;
    unsigned char far *p;

    id5 = id * 5;
    ypos = x * 64;
    r5 = id5 * 5;
    for (row = 0; row < 5; row++) {
        p = &AT(r5 + row + 0x870a);
        for (col = 0; col < 5; col++) {
            if (*p != 0 && MapA[0][y + ypos + col] > 0x10)
                return;
            p += 5;
        }
        ypos += 0x40;
    }

    ypos = x * 64;
    r5 = id5 * 5;
    for (row = 0; row < 5; row++) {
        p = &AT(r5 + row + 0x870a);
        for (col = 0; col < 5; col++) {
            int value;
            value = *p;
            if (value != 0)
                MapA[0][y + ypos + col] = value;
            p += 5;
        }
        ypos += 0x40;
    }
}
