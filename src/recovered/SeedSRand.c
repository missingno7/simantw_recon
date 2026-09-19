/* Candidate reconstruction from the TickCount-seeded LFSR initializer. */
#define SRandSeed (*(unsigned int near *)0xCBF2)
extern long far TickCount(void);

void SeedSRand(void)
{
    SRandSeed = TickCount() ^ 0x3751;
}
