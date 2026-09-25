/* Semantic hypothesis: shift the 16-bit state, correct on left-shift
 * overflow, save it, and return its low bit. */
extern unsigned int near edata[];

int SRand2(void)
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
    return result;
}
