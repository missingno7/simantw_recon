/*
 * SGRand samples the same seed twice through the module-local SRand1 helper
 * and returns the smaller sample.  The target keeps the argument in DI and
 * compares the two generated signed-word results before returning.
 */
extern int near SRand1(int seed);

int SGRand(register int seed)
{
    int value;

    value = seed;
    seed = SRand1(value);
    value = SRand1(value);
    return value <= seed ? value : seed;
}
