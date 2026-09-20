extern int far SRand1(int limit);

int SGIRand(int limit)
{
    volatile int scratch;
    int first = SRand1(limit);
    int second = SRand1(limit);
    if (second < first)
        return first;
    return second;
}
