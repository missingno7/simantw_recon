/*
 * Bounce: choose a new direction for something that reached the edge of
 * the 128 x 64 map at (x, y).  Corners pick one of three directions
 * (SRand1(3) plus a base of 3, 1, 5 or 7 for the top-left, bottom-left,
 * top-right and bottom-right corners); edges pick one of five (SRand1(5)
 * plus 1, 3, 5 or 7 for the left, top, right and bottom edges); anywhere
 * else returns 0.  The compiler merges the shared SRand1-plus-base tails
 * of the corner and edge returns.
 */
extern int far SRand1(int range);

int far Bounce(int x, int y)
{
    if (x == 0) {
        if (y == 0)
            return SRand1(3) + 3;
        if (y == 0x3f)
            return SRand1(3) + 1;
        return SRand1(5) + 1;
    }
    if (y == 0) {
        if (x == 0x7f)
            return SRand1(3) + 5;
        return SRand1(5) + 3;
    }
    if (x == 0x7f) {
        if (y == 0x3f)
            return SRand1(3) + 7;
        return SRand1(5) + 5;
    }
    if (y == 0x3f)
        return SRand1(5) + 7;
    return 0;
}
