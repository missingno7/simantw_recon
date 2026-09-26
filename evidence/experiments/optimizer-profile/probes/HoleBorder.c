/* HoleBorder scans the eight signed neighbor vectors, skips out-of-range positions and existing values at or above 0x50, and writes the corresponding hole-edge tile code into MapA. HoleValues is the private eight-byte direction table at DGROUP:230c. */
extern signed char far Dx8[];
extern signed char far Dy8[];
extern unsigned char near MapA[];
static unsigned char HoleValues[8] = {0x19,0x1a,0x1c,0x1f,0x1e,0x1d,0x1b,0x18};

void far HoleBorder(int x, int y)
{
    register int row;
    register int i;
    register int column;
    register unsigned char near *tile;

    for (i = 0; i < 8; ++i) {
        row = Dy8[i] + y;
        column = Dx8[i] + x;
        if (column < 0 || column > 0x7f || row < 0 || row > 0x3f)
            continue;
        tile = MapA + (column << 6) + row;
        if (*tile >= 0x50)
            continue;
        *tile = HoleValues[i];
    }
}
