/* Byte-matched reconstruction; historical declaration spelling is uncertain. */
#define SRandSeed (*(unsigned int near *)0xCBF2)

long SRand256(void)
{
    int result;
    SRandSeed <<= 1;
    if (SRandSeed & 0x8000) SRandSeed ^= 0x1bf5;
    result = SRandSeed & 255;
    return result;
}
