/*
 * RIsItDirt accepts the ordinary dirt-code band 0x20..0x2f and the
 * high-valued dirt marker range beginning at 0x4f.  The target returns a
 * signed 16-bit boolean and keeps the two accepted regions explicit.
 */
int RIsItDirt(int value)
{
    if (value < 0x20)
        return 0;
    if (value <= 0x2f)
        return 1;
    if (value < 0x4f)
        return 0;
    return 1;
}
