/*
 * TooFar rejects a point when either signed coordinate lies outside the
 * inclusive range -0x0f..0x0f.  A point inside that square is reported with
 * the historical 16-bit boolean convention.
 */
int TooFar(int x, int y)
{
    return x >= -0x0f && x <= 0x0f &&
           y >= -0x0f && y <= 0x0f;
}
