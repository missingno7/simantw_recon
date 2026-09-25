/* Semantic hypothesis: validate every occupied rock-mask cell before placing any of them. */
/* A blocked MapA cell aborts the operation; the second pass copies nonzero mask bytes. */
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
    row = 0;
    ypos = x * 64;
    r5 = id5 * 5;
    for (; row < 5; row++) {
        p = &AT(r5 + row + 0x870a);
        for (col = 0; col < 5; col++) {
            if (*p != 0) {
                if (MapA[0][y + ypos + col] > 0x10)
                    return;
            }
            p += 5;
        }
        ypos += 0x40;
    }

    row = 0;
    ypos = x * 64;
    r5 = id5 * 5;
    for (; row < 5; row++) {
        p = &AT(r5 + row + 0x870a);
        for (col = 0; col < 5; col++) {
            int v = *p;
            if (v != 0)
                MapA[0][y + ypos + col] = v;
            p += 5;
        }
        ypos += 0x40;
    }
}
