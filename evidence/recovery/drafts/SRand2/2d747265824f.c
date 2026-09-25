/* Semantic hypothesis: use the shift carry to select the polynomial and
 * preserve the returned low bit in an observable stack local. */
extern unsigned int near edata[];

int SRand2(void)
{
    unsigned int oldValue;
    unsigned int value;
    volatile int result;

    oldValue = edata[201];
    value = oldValue << 1;
    if (value < oldValue)
        value ^= 0x1bf5;
    edata[201] = value;
    result = value & 1;
    return result;
}
