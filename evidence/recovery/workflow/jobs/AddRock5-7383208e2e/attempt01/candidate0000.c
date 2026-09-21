extern unsigned char near MapA[128][64];
extern unsigned char far Dx8;
#define AT(off) ((&Dx8)[off])

void far AddRock5(int x, int y, int id)
{
    int r5;
    int ypos;
    int row;
    int col;

    r5 = id * 25;
    ypos = x * 64;

    for (row = 0; row < 5; row++) {
        for (col = 0; col < 5; col++) {
            if (AT(r5 + row + col * 5 + 0x870a) != 0) {
                if (MapA[0][y + ypos + col] > 0x10)
                    return;
            }
        }
        ypos += 0x40;
    }

    ypos = x * 64;
    for (row = 0; row < 5; row++) {
        for (col = 0; col < 5; col++) {
            unsigned char v = AT(r5 + row + col * 5 + 0x870a);
            if (v != 0)
                MapA[0][y + ypos + col] = v;
        }
        ypos += 0x40;
    }
}
