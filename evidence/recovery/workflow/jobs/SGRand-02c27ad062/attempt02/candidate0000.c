/*
 * SGRand samples the same seed twice through the module-local SRand1 helper
 * and returns the larger sample.  The target keeps the argument in DI and
 * compares the two generated signed-word results before returning.
 */
extern int near SRand1(int seed);

int SGRand(int seed)
{
    int first;

    first = SRand1(seed);
    seed = SRand1(seed);
    if (seed <= first)
        seed = first;
    return seed;
}
