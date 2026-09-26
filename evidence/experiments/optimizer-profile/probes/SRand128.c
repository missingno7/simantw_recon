/* Semantic hypothesis: advance the shared 16-bit LFSR and return its
 * low seven bits after saving the new state. */
extern unsigned int near edata[];

int SRand128(void)
{
    unsigned int oldValue;
    unsigned int value;
    volatile int result;

    oldValue = edata[201];
    value = oldValue << 1;
    if (value < oldValue)
        value ^= 0x1bf5;
    edata[201] = value;
    result = value & 0x7f;
    return result;
}
