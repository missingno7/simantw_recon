/* Candidate reconstruction from the closed seed accessor. */
#define SRandSeed (*(unsigned int near *)0xCBF2)

long GetSRandSeed(void)
{
    return SRandSeed;
}
