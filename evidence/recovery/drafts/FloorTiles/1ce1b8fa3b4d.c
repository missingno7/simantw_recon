/*
 * FloorTiles: stamp the base checkerboard tile pattern into MapA (128
 * rows x 64 columns), lay four vertical pillar columns (0,16,32,48)
 * with a 16-row alternating tile, then walk every 16th row placing
 * corner glyphs depending on whether the existing cell is still a
 * checkerboard cell (<2) or a pillar cell (>=2).  Finally clears
 * DROPdir.
 */
extern volatile unsigned char near MapA[128][64];
extern int far DROPdir;

void far FloorTiles(void)
{
    int x, y;

    for (x = 0; x < 128; x++) {
        for (y = 0; y < 64; y++) {
            if ((((y >> 4) + (x >> 4)) & 1) != 0) {
                MapA[x][y] = 0;
            } else {
                MapA[x][y] = 1;
            }
        }
    }

    for (x = 0; x < 64; x += 16) {
        for (y = 0; y < 128; y++) {
            MapA[y][x] = ((((x + y) & 0x10) == 0) ? 0x61 : 0x60);
        }
    }

    for (x = 0; x < 128; x += 16) {
        for (y = 0; y < 64; y++) {
            if (MapA[x][y] < 2) {
                if ((x + y) & 0x10)
                    MapA[x][y] = 0x5e;
                else
                    MapA[x][y] = 0x5f;
            } else {
                if ((x + y) & 0x10)
                    MapA[x][y] = 0x5d;
                else
                    MapA[x][y] = 0x5c;
            }
        }
    }

    DROPdir = 0;
}
