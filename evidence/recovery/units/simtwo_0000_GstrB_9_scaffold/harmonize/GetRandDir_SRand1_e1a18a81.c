/*
 * GetRandDir: pick a random heading for an ant at yard cell (x, y)
 * currently heading dir.  On the yard border the heading is chosen from
 * the directions that point back inside: corners allow three headings
 * (SRand1(3) + base), edges five (SRand1(5) + base), with bases 3 (top
 * left), 1 (left/bottom left), 5 (top right/top), 7 (bottom right/bottom)
 * and the result is folded to 0..7 as (r - 1) & 7.  Inside the yard the
 * new heading comes from the far TurnTab row of the current heading,
 * indexed by SRand8().
 */
extern char far TurnTab[][8];

extern int far SRand1(unsigned int range);
extern int far SRand8(void);

int far GetRandDir(int x, int y, int dir)
{
    int r;

    if (x == 0) {
        if (y == 0)
            r = SRand1(3) + 3;
        else if (y == 63)
            r = SRand1(3) + 1;
        else
            r = SRand1(5) + 1;
    } else if (y == 0) {
        if (x == 127)
            r = SRand1(3) + 5;
        else
            r = SRand1(5) + 3;
    } else if (x == 127) {
        if (y == 63)
            r = SRand1(3) + 7;
        else
            r = SRand1(5) + 5;
    } else if (y == 63)
        r = SRand1(5) + 7;
    else
        r = 0;
    if (r != 0)
        return (unsigned char)r - 1 & 7;
    return TurnTab[dir][SRand8()];
}
