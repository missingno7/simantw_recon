/* Keep the second sample as the return accumulator; far helper calls are LINK-lowered. */
extern int far SRand1(int seed);
int SGRand(register int seed)
{
    int first;
    int result;
    first = SRand1(seed);
    result = SRand1(seed);
    if (result > first) result = first;
    return result;
}
