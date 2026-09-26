/* Read the two half-open rectangle bounds from MAPSYM PACK words. */
extern volatile int near MapPlane;
extern int near editWidth;
extern int near editHeight;
extern int far match_position[];

int TileIsVisible(int plane, int x, int y)
{
    if (plane != MapPlane)
        goto no;
    if (match_position[0x3e97] > x)
        goto no;
    if (match_position[0x3e97] + editWidth <= x)
        goto no;
    if (match_position[0x3e98] > y)
        goto no;
    if (match_position[0x3e98] + editHeight <= y)
        goto no;
    return 1;
no:
    return 0;
}
