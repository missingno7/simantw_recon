/*
 * ExpIncSmell: experimental map-editor tool that raises or lowers the
 * pheromone level at map cell (x, y) on the A/ant planes (MapPlane <= 1
 * only; other planes do nothing).  Coordinates are halved into the
 * pheromone grid (rx = x >> 1, ry = y >> 1, 0..63 by 0..31).  Off-grid
 * coordinates read as smell -1 and skip the write entirely.  On-grid,
 * experiment sub-state 5 selects which of the five pheromone maps
 * (B-nest, B-trail, R-nest, R-trail, A) is read and later written; an
 * out-of-range sub-state leaves the read value uninitialised, matching
 * the historical uninitialised local.  Holding CONTROL lowers the
 * smell by 40, otherwise it rises by 70; the result is clamped to
 * 0..255 and, when the coordinate is on-grid, stored back into the
 * selected map.  The cell is then smoothed and a click plays.
 */
extern int near MapPlane;
extern unsigned char far ExpSubStates[];
extern unsigned char far PherMapBN[64][32];
extern unsigned char far PherMapBT[64][32];
extern unsigned char far PherMapRN[64][32];
extern unsigned char far PherMapRT[64][32];
extern unsigned char far PherMapA[64][32];

extern int far pascal GetAsyncKeyState(unsigned int key);
extern void far SmoothMany(int x, int y);
extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);

void far ExpIncSmell(int x, int y)
{
    int ry;
    int rx;
    int val;
    int valid;
    int writeVal;
    unsigned int b;

    if (MapPlane > 1)
        return;

    ry = y >> 1;
    rx = x >> 1;

    valid = (rx >= 0 && rx <= 0x3f && ry >= 0 && ry <= 0x1f);
    if (!valid) {
        val = -1;
        goto map_value_ready;
    }
    {
        switch ((char)ExpSubStates[5]) {
        case 0:
            b = PherMapBN[rx][ry];
            break;
        case 1:
            b = PherMapBT[rx][ry];
            break;
        case 2:
            b = PherMapRN[rx][ry];
            break;
        case 3:
            b = PherMapRT[rx][ry];
            break;
        case 4:
            b = PherMapA[rx][ry];
            break;
        }
        val = b;
    }
map_value_ready:

    if (GetAsyncKeyState(0x11) & 0x8000)
        val -= 0x28;
    else
        val += 0x46;

    if (val < 0)
        val = 0;
    if (val > 0xff)
        val = 0xff;

    writeVal = val;
    writeVal = val;
    valid = (rx >= 0 && rx <= 0x3f && ry >= 0 && ry <= 0x1f);
    if (valid) {
        if (writeVal > 0xff)
            writeVal = 0xff;
        switch ((char)ExpSubStates[5]) {
        case 0:
            PherMapBN[rx][ry] = (unsigned char)writeVal;
            break;
        case 1:
            PherMapBT[rx][ry] = (unsigned char)writeVal;
            break;
        case 2:
            PherMapRN[rx][ry] = (unsigned char)writeVal;
            break;
        case 3:
            PherMapRT[rx][ry] = (unsigned char)writeVal;
            break;
        case 4:
            PherMapA[rx][ry] = (unsigned char)writeVal;
            break;
        }
    }

    SmoothMany(rx, ry);
    myBeginSound(0x1b, 0, 0x7e);
}
