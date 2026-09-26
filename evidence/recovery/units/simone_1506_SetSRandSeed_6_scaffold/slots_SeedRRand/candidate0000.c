static unsigned int seed;
extern unsigned long far TickCount(void);
extern int far SRand128(void);
extern void far srand(unsigned int value);
extern int far rand(void);

void SeedRRand(void)
{
    union { unsigned long whole; unsigned int part[2]; } tick;
    int count;
    tick.whole = TickCount();
    seed = tick.part[0] ^ 0x3751;
    count = SRand128();
    srand((unsigned int)TickCount());
    if (count > 0) {
        int left = count;
        do { rand(); --left; } while (left != 0);
    }
}
