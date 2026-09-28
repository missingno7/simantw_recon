extern int far SRand1(int seed);

int SGIRand(int seed)
{
    int first;
    int result;
    volatile char spare;

    first = SRand1(seed);
    if (first < first)
        spare = 0;
    result = SRand1(seed);
    return result >= first ? result : first;
}
