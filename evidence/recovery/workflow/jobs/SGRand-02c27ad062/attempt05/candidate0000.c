/*
 * SGRand samples the same seed twice through the module-local SRand1 helper
 * and returns the smaller sample.  The target keeps the argument in DI and
 * compares the two generated signed-word results before returning.
 */
extern int near SRand1(int seed);

int SGRand(register int seed)
{
    int first;

    first = SRand1(seed);
    seed = SRand1(seed);
    return seed <= first ? seed : first;
}
