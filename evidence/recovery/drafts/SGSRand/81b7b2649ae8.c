/* Keep the first sample as a local while comparing against the second. */
extern int far SRand1(int value);
extern int far SRand2(void);
int far SGSRand(int value)
{
    int first, second;
    first = SRand1(value);
    second = SRand1(value);
    if (first < second)
        second = first;
    if (SRand2() != 0)
        second = -second;
    return second;
}
