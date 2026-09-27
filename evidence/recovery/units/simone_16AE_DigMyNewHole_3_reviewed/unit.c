/* Shared private direction stencil: all four users load offsets at DGROUP:230c. */
static unsigned char HoleValues[8] = {0x19,0x1a,0x1c,0x1f,0x1e,0x1d,0x1b,0x18};

/* Return 1 for an open terrain tile or a clear 3x3 location; create the hole on success. */
extern int far TERRAINset;
extern unsigned char near MapA[];
extern int far IsClear3x3(int plane, int x, int y);
extern void far CreateNewHole(int x, int y);

int far DigMyNewHole(int x, int y)
{
    int result;

    result = 0;
    if (x >= 1 && x <= 127 && y >= 1 && y <= 63) {
        if (TERRAINset) {
            if (MapA[(x << 6) + y] < 0xc8)
                result = 1;
        } else {
            result = IsClear3x3(1, x, y);
        }
        if (result == 1)
            CreateNewHole(x, y);
    }
    return result;
}

/*
 * Hypothesis: direction codes 0, 2, 3, 0x5e..0x61, 0x66, and 0x68
 * describe the legal house-hole cases.  The middle range is translated
 * into the corresponding hole code by adding 0x22; every other code is
 * rejected with zero.
 */
int CanBeHouseHole(int direction)
{
    if (direction == 0)
        return 0x86;

    if (direction == 2)
        return 0x8a;
    if (direction == 3)
        return 0x8a;

    if (direction >= 0x5e) {
        if (direction < 0x62)
            return direction + 0x22;
        if (direction == 0x66)
            return 0x85;
        if (direction == 0x68)
            return 0x84;
    }

    return 0;
}

/* HoleBorder scans the eight signed neighbor vectors, skips out-of-range positions and existing values at or above 0x50, and writes the corresponding hole-edge tile code into MapA. HoleValues is the private eight-byte direction table at DGROUP:230c. */
extern signed char far Dx8[];
extern signed char far Dy8[];
extern unsigned char near MapA[];

void far HoleBorder(int x, int y)
{
    register int row;
    register int i;
    register int column;
    register unsigned char near *tile;
    signed char far *dx = Dx8;
    signed char far *dy = Dy8;

    for (i = 0; i < 8; ++i) {
        row = dy[i] + y;
        column = dx[i] + x;
        if (column < 0 || column > 0x7f || row < 0 || row > 0x3f)
            continue;
        tile = MapA + (column << 6) + row;
        if (*tile >= 0x50)
            continue;
        *tile = HoleValues[i];
    }
}
