/*
 * MakeKitchenWall: initialize a kitchen-wall region of the near maps and
 * then place inner wall/floor tiles, before creating two outlets and
 * setting the drop direction.
 */
extern unsigned char near MapA[128][64];
extern unsigned char near MapB[64][64];

extern void far MakeOutletV(int x, int y);
extern int near _DROPdir;

void far MakeKitchenWall(void)
{
    int x, y;
    int n;
    int i, j;

    for (x = 41; x <= 41 + 11; x++) {
        for (y = 0; y < 12; y++)
            MapA[x][y] = 0x6262;
    }

    for (x = 41; x <= 41 + 6; x++) {
        for (y = 0; y < 20; y++)
            MapA[x][y] = 0;
    }

    n = 0;
    do {
        for (y = 0; y < 128; y++)
            MapA[n][y] = 0x68;
        n += 8;
    } while (n < 24);

    for (i = 0; i < 0x2000; i += 0x200) {
        for (j = 0; j < 24; j++) {
            if (MapA[0][i + j] == 0x62)
                MapA[0][i + j] = 0x66;
            else
                MapA[0][i + j] = 0x67;
        }
    }

    for (x = 41; x < 0x48ff / 64; x++) {
        if (MapA[x][0] == 0x62)
            MapA[x][0] = 0x68;
        else
            MapA[x][0] = 0x69;
    }

    MakeOutletV(0x24, 2);
    MakeOutletV(0x54, 2);

    _DROPdir = 2;
}
