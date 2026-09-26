static unsigned int seed;
extern unsigned long far TickCount(void);
extern int far SRand128(void);
extern void far srand(unsigned int value);
extern int far rand(void);

void SeedSRand(void)
{
    seed = (unsigned int)TickCount() ^ 0x3751;
}
