/*
 * SGSRand draws two values from SRand1, keeps the smaller one, then uses
 * SRand2 as a sign bit.  The explicit comparison preserves the historical
 * min-selection branch before the final conditional negation.
 */
extern int near SRand1(int value);
extern int near SRand2(void);

int SGSRand(int value)
{
    int first;

    first = SRand1(value);
    value = SRand1(value);
    if (value > first)
        value = first;
    if (SRand2())
        value = -value;
    return value;
}
