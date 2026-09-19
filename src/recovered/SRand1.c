/* Byte-matched reconstruction; historical declaration spelling is uncertain. */
#define SRandSeed (*(unsigned int near *)0xCBF2)

int SRand1(int divisor)
{
    int result;
    SRandSeed <<= 1;
    if (SRandSeed & 0x8000) SRandSeed ^= 0x1bf5;
    result = SRandSeed % divisor;
    return result;
}
