/*
 * Jam the B-team scent map at the evenized x coordinate and half-scaled y
 * coordinate.  A stronger existing scent is preserved; weaker scent is
 * replaced by the requested byte value.
 */
extern unsigned char far Dx8[];

void near JamScentBN(int x, int y, int scent)
{
    if (Dx8[((x & -2) << 4) + (y >> 1) + 0x62d2] < scent)
        Dx8[((x & -2) << 4) + (y >> 1) + 0x62d2] = scent;
}
