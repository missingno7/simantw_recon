static unsigned int seed;
extern unsigned long far TickCount(void);
extern int far SRand128(void);
extern void far srand(unsigned int value);
extern int far rand(void);

unsigned long GetSRandSeed(void)
{
    return (unsigned long)(unsigned int)seed;
}
