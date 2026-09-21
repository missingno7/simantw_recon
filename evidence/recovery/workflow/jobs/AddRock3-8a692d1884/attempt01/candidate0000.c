extern unsigned char near MapA[128][64];
extern unsigned char far Dx8;
#define AT(off) ((&Dx8)[off])

void far AddRock3(int x, int y, int id)
{
    int row;
    int col;
    int ypos;

    ypos = x << 6;
    for (row = 0; row < 3; row++) {
        for (col = 0; col < 3; col++) {
            if (AT(id * 9 + row + col * 3 + 0x87a0) != 0) {
                if (MapA[0][y + ypos + col] > 0x10)
                    return;
            }
        }
        ypos += 0x40;
    }

    ypos = x << 6;
    for (row = 0; row < 3; row++) {
        for (col = 0; col < 3; col++) {
            unsigned char v = AT(id * 9 + row + col * 3 + 0x87a0);
            if (v != 0)
                MapA[0][y + ypos + col] = v;
        }
        ypos += 0x40;
    }
}
