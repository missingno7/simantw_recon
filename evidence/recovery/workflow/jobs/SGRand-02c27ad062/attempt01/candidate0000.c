/*
 * SGRand samples the same seed twice through the module-local SRand1 helper
 * and returns the larger sample.  The target keeps the argument in DI and
 * compares the two generated signed-word results before returning.
 */
extern int near SRand1(int seed);

int SGRand(int seed)
{
    int first;
    int second;

    first = SRand1(seed);
    second = SRand1(seed);
    if (second <= first)
        return first;
    return second;
}
