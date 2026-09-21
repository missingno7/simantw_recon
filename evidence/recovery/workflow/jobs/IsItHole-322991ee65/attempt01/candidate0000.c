/*
 * Hypothesis: a valid A-map coordinate is a hole when the terrain mode is
 * off and its tile is exactly 0x50, or when terrain mode is on and its tile
 * lies in the inclusive 0x80..0x8f band.  The selector load for TERRAINset
 * and the near MapA binding follow the packet's segment-register evidence.
 */
extern int far IsValidA(int x, int y);
extern unsigned int far TERRAINset;
extern unsigned char near MapA[];

int far IsItHole(int x, int y)
{
    unsigned char tile;

    if (!IsValidA(x, y))
        return 0;
    if (!TERRAINset) {
        if (MapA[(x << 6) + y] != 0x50)
            return 0;
        return 1;
    }
    tile = MapA[(x << 6) + y];
    if (tile < 0x80 || tile > 0x8f)
        return 0;
    return 1;
}
