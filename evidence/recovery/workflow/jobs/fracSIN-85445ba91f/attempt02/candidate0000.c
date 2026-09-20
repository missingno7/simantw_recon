/*
 * Hypothesis: fracSIN uses the locked, far sine table shared by fracCOS.
 * The input is folded into the first 64 entries of a 128-step quadrant;
 * the exact negative-axis point returns the fixed-point maximum.  The
 * original routine then applies the sign selected by the input's low byte.
 */
extern int far *fracSinTable;

int fracSIN(int angle)
{
    int index;
    int value;

    index = angle & 0x7f;
    if (index > 0x3f)
        index = 0x80 - index;

    if (index == 0x40)
        value = 0x7fff;
    else {
        index &= 0x3f;
        value = fracSinTable[index];
    }
    if ((unsigned char)angle > 0x7f)
        value = -value;

done:
    return value;
}
