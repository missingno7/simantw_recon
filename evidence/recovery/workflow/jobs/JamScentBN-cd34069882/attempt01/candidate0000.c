/*
 * Jam the B-team scent map at the evenized x coordinate and half-scaled y
 * coordinate.  A stronger existing scent is preserved; weaker scent is
 * replaced by the requested byte value.
 */
extern unsigned char far Dx8[];

void near JamScentBN(int x, int y, int scent)
{
    int offset;

    offset = (x & 0xfffe) << 4;
    offset += y >> 1;
    if (Dx8[offset + 0x62d2] < scent)
        Dx8[offset + 0x62d2] = scent;
}
