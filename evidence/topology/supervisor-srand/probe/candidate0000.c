/* Expert research: unsigned widened multiplication preserves SHL carry.
 * A volatile result expresses the observed stack store/reload. This is a
 * hypothesis, not established source or ABI; full object matching decides.
 */
static unsigned int near seed;
int SRand2(void)
{
    unsigned long value;
    volatile int result;
    value = (unsigned long)seed * 2;
    if (value & 0x10000UL)
        value ^= 0x1bf5;
    seed = (unsigned int)value;
    result = seed & 1;
    return result;
}
