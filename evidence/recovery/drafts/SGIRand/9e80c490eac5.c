extern int far SRand1(int value);

int SGIRand(int value)
{
    int first[1];
    int second;

    first[0] = SRand1(value);
    second = SRand1(value);
    return second >= first[0] ? second : first[0];
}
