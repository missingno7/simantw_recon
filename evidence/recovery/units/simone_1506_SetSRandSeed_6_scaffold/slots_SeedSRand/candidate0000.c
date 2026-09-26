static unsigned int seed;
extern unsigned long far TickCount(void);

void SeedSRand(void)
{
    seed = (unsigned int)TickCount() ^ 0x3751;
}
