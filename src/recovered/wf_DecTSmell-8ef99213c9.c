/*
 * Hypothesis: x and y identify a half-resolution scent cell.  The third
 * argument selects the red-team table at Dx8+0x7ad2; zero selects the
 * black-team table at Dx8+0x6ad2.  A nonzero cell is decremented once.
 */
extern unsigned char far Dx8[];

void near DecTSmell(int x, int y, int redTeam)
{
    int xHalf = x >> 1;
    int yHalf = y >> 1;

    if (redTeam) {
        if (Dx8[(xHalf << 5) + yHalf + 0x7ad2] != 0)
            --Dx8[(xHalf << 5) + yHalf + 0x7ad2];
    } else {
        if (Dx8[(xHalf << 5) + yHalf + 0x6ad2] != 0)
            --Dx8[(xHalf << 5) + yHalf + 0x6ad2];
    }
}
