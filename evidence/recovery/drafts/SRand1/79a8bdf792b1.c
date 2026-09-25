/* Semantic hypothesis: capture shift overflow, apply the LFSR polynomial,
 * commit the updated seed, then return the unsigned remainder. */
extern unsigned int near edata[];

int SRand1(unsigned int range)
{
    unsigned int oldValue;
    unsigned int value;
    int result;

    oldValue = edata[201];
    value = oldValue << 1;
    if (value < oldValue)
        value ^= 0x1bf5;
    edata[201] = value;
    result = value % range;
    return result;
}
