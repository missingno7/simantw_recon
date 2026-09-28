/* Semantic hypothesis: preserved candidate; validate state and carry operations from target bytes. */
extern int near SRand1(int value);

int SGIRand(int value)
{
    int first;

    first = SRand1(value);
    value = SRand1(value);
    return value >= first ? value : first;
}
