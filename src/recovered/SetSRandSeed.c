/* Candidate reconstruction from the closed seed mutator. */
#define SRandSeed (*(unsigned int near *)0xCBF2)

void SetSRandSeed(unsigned int seed)
{
    SRandSeed = seed;
}
