/*
 * Jam the R-team scent map at the evenized x coordinate and half-scaled y
 * coordinate.  A stronger existing scent is preserved; weaker scent is
 * replaced by the requested byte value.
 */
extern unsigned char far Dx8[];

void near JamScentRT(int x, int y, int scent)
{
    if (Dx8[((x & -2) << 4) + (y >> 1) + 0x7ad2] < scent)
        Dx8[((x & -2) << 4) + (y >> 1) + 0x7ad2] = scent;
}
