/*
 * A nest coordinate pair is valid when x is non-negative and at most 0x3f,
 * while y is in the inclusive range 1..0x3f.  The routine returns a signed
 * 16-bit boolean after rejecting either coordinate outside those bounds.
 */
int InNestBounds(int x, int y)
{
    if (x < 0 || x > 0x3f)
        return 0;
    if (y < 1 || y > 0x3f)
        return 0;
    return 1;
}
