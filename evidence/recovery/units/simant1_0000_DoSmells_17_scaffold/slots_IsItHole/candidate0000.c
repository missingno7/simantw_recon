/*
 * IsItHole: a valid A-map coordinate is a nest hole when the terrain set is
 * the default (tile == 0x50) or, in the alternate terrain set, when the tile
 * lies in 0x80..0x8f.  Probe: the return-0 block is materialised inline at
 * the first simple `if (tile < 0x80) return 0;` and the TERRAINset branch is
 * written positively (`== 0x50` -> return 1, else return 0).
 */
extern int far IsValidA(int x, int y);
extern unsigned int far TERRAINset;
extern unsigned char near MapA[];

int far IsItHole(int x, int y)
{
    int tile;

    if (IsValidA(x, y) == 0)
        return 0;
    if (TERRAINset == 0) {
        if (MapA[(x << 6) + y] == 0x50)
            return 1;
        return 0;
    }
    tile = MapA[(x << 6) + y];
    if (tile < 0x80)
        return 0;
    if (tile > 0x8f)
        return 0;
    return 1;
}
