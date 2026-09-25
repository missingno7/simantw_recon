/*
 * Hypothesis: fracCOS is the same signed fixed-point lookup as fracSIN,
 * with the input advanced by one quarter turn.  The index is folded into
 * the first quadrant, the exact axis returns 0x7fff, and the sign is taken
 * from the low byte after the quarter-turn adjustment.  FracSineTab is the
 * only table binding supported by the adjacent accepted recovery; the
 * unnamed selector operand in this packet is not promoted to a source
 * global without direct-data evidence.
 */
extern int far * far FracSineTab;

int fracCOS(int angle)
{
    int index;
    int value;

    index = angle - 0xc0;
    index &= 0x7f;
    if (index > 0x3f)
        index = 0x80 - index;

    if (index == 0x40)
        value = 0x7fff;
    else {
        index &= 0x3f;
        value = FracSineTab[index];
    }
    if (((angle + 0x40) & 0xff) > 0x7f)
        value = -value;

    return value;
}
