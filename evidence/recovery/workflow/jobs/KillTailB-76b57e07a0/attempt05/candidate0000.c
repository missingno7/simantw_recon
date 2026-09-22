/* KillTailB clears a black ant's B-list "attribute" byte (Dx8+0x3d18),
 * reads its cached "direction" byte (Dx8+0x392c) and its 16-bit "row" word
 * (Dx8+0x3736, masked to the low byte -- the field itself is a byte but
 * /Oeglw loads it as a word before masking, the same idiom the admitted
 * simant1:2D4E unit shows for these identical 0x3d18/0x392c/0x3736 fields
 * in DoAntSimB), then clears LifeB[row*64 + direction] (LifeB is the
 * 128x64 map indexed by row then column/direction).
 *
 * KillTailR is the same shape with every Dx8 field offset shifted by the
 * constant 0x9CE (2510 bytes) that separates the black/red B-list tables:
 * attribute 0x46e6, direction 0x42fa, row 0x4104, against LifeR instead of
 * LifeB. */

extern unsigned char far Dx8[];
extern unsigned char near LifeB[128][64];

#define LifeB ((unsigned char near *)LifeB)
void far KillTailB(int tail)
{
    unsigned int row;
    unsigned char direction;
    unsigned char zero = 0;

    Dx8[tail + 0x3d18] = zero;
    direction = Dx8[tail + 0x392c];
    row = *(unsigned int far *)(Dx8 + tail + 0x3736);
    row &= 0xff;
    LifeB[(row << 6) + direction] = zero;
}
#undef LifeB
