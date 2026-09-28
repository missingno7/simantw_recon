/*
 * SGRand samples the same seed twice through the module-local SRand1 helper
 * and returns the smaller sample.  The target keeps the argument in DI and
 * compares the two generated signed-word results before returning.
 */
extern int far SRand1(int seed);

int SGRand(int seed)
{
    int first;
    int second;
    int result;
    first = SRand1(seed);
    second = SRand1(seed);
    if (second <= first) result = second;
    else result = first;
    return result;
}
