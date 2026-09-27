/*
 * A grass tile is recognized only when the first coordinate/category value
 * is at least two and the second value is in the inclusive tile-code band
 * 0x1c..0x1f.  The target returns a 16-bit boolean.
 */
int IsThisGrass(int category, int tile)
{
    if (category < 2)
        return 0;
    if (tile < 0x1c || tile > 0x1f)
        return 0;
    return 1;
}
