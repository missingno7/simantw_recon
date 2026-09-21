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
    register int valid;
    register int tile;

    valid = IsValidA(x, y);
    if (!valid)
        goto done;
    if (TERRAINset == 0) {
        if (MapA[(x << 6) + y] != 0x50)
            goto no_hole;
        goto hole;
    }
    tile = MapA[(x << 6) + y];
    if (tile < 0x80)
        goto no_hole;
    if (tile > 0x8f)
        goto no_hole;
    goto hole;

no_hole:
    return 0;
hole:
    return 1;
done:
    return valid;
}
