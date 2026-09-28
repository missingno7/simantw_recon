extern int far SRand1(int seed);
int SGRand(register int seed)
{
    int first;
    int result;
    volatile int spare;
    if (seed < seed) spare = seed;
    first = SRand1(seed);
    result = SRand1(seed);
    return result <= first ? result : first;
}
