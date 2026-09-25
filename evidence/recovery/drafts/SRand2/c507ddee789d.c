/* Semantic hypothesis: return the low-bit recurrence result widened to an
 * unsigned long after committing the 16-bit state. */
extern unsigned int near edata[];

unsigned long SRand2(void)
{
    unsigned int oldValue;
    unsigned int value;
    int result;

    oldValue = edata[201];
    value = oldValue << 1;
    if (value < oldValue)
        value ^= 0x1bf5;
    edata[201] = value;
    result = value & 1;
    return (unsigned long)result;
}
