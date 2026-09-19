/* Byte-matched reconstruction; historical declaration spelling is uncertain. */
static unsigned int SRandSeed = 0;

long SRand2(void)
{
    int result;
    SRandSeed <<= 1;
    if (SRandSeed & 0x8000) SRandSeed ^= 0x1bf5;
    result = SRandSeed & 1;
    return result;
}
