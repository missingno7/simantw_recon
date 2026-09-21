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
extern unsigned char near PherMapBN[64][32];
extern unsigned char near PherMapBT[64][32];
extern unsigned char near PherMapRN[64][32];
extern unsigned char near PherMapRT[64][32];
extern unsigned char near PherMapA[64][32];

extern int far pascal GetAsyncKeyState(unsigned int key);
extern void far SmoothMany(int x, int y);
extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);

void far ExpIncSmell(int x, int y)
{
    int ry;
    int rx;
    int val;
    int si;

    if (MapPlane > 1)
        return;

    ry = y >> 1;
    rx = x >> 1;

    if (rx >= 0 && rx <= 0x3f && ry >= 0 && ry <= 0x1f) {
        switch (ExpSubStates[5]) {
        case 0:
            val = PherMapBN[rx][ry];
            break;
        case 1:
            val = PherMapBT[rx][ry];
            break;
        case 2:
            val = PherMapRN[rx][ry];
            break;
        case 3:
            val = PherMapRT[rx][ry];
            break;
        case 4:
            val = PherMapA[rx][ry];
            break;
        }
        si = val;
    } else {
        si = -1;
    }

    if (GetAsyncKeyState(0x11) & 0x8000)
        si -= 0x28;
    else
        si += 0x46;

    if (si < 0)
        si = 0;
    if (si > 0xff)
        si = 0xff;

    if (rx >= 0 && rx <= 0x3f && ry >= 0 && ry <= 0x1f) {
        if (si > 0xff)
            si = 0xff;
        switch (ExpSubStates[5]) {
        case 0:
            PherMapBN[rx][ry] = (unsigned char)si;
            break;
        case 1:
            PherMapBT[rx][ry] = (unsigned char)si;
            break;
        case 2:
            PherMapRN[rx][ry] = (unsigned char)si;
            break;
        case 3:
            PherMapRT[rx][ry] = (unsigned char)si;
            break;
        case 4:
            PherMapA[rx][ry] = (unsigned char)si;
            break;
        }
    }

    SmoothMany(rx, ry);
    myBeginSound(0x1b, 0, 0x7e);
}
