/* KillTailR clears a red ant's R-list "attribute" byte (Dx8+0x46e6), reads
 * its cached "direction" byte (Dx8+0x42fa) and its 16-bit "row" word
 * (Dx8+0x4104, masked to the low byte -- the field itself is a byte but
 * /Oeglw loads it as a word before masking), then clears
 * LifeR[row*64 + direction] (LifeR is the 128x64 map indexed by row then
 * column/direction).
 *
 * KillTailB is the same shape with every Dx8 field offset shifted back by
 * the constant 0x9CE (2510 bytes) that separates the red/black B-list
 * tables: attribute 0x3d18, direction 0x392c, row 0x3736, against LifeB
 * instead of LifeR. */

extern unsigned char far Dx8[];
extern unsigned char near LifeR[128][64];

#define LifeR ((unsigned char near *)LifeR)
void far KillTailR(int tail)
{
    unsigned int row;
    unsigned char direction;

    Dx8[tail + 0x46e6] = 0;
    direction = Dx8[tail + 0x42fa];
    row = *(unsigned int far *)(Dx8 + tail + 0x4104);
    row &= 0xff;
    LifeR[(row << 6) + direction] = 0;
}
#undef LifeR
