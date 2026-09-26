/*
 * Seed the simulation's random stream from two tick-count samples.  The
 * first sample initializes the private seed with the historical xor constant;
 * SRand128 supplies the warm-up count, and rand consumes that many values
 * after the C runtime is reseeded from the second sample.
 */
extern unsigned long far TickCount(void);
extern int far SRand128(void);
extern void far srand(unsigned int seed);
extern int far rand(void);
extern int near rrandSeed;

void SeedRRand(void)
{
    int scratch[2];
    int count;

    rrandSeed = (int)TickCount() ^ 0x3751;
    count = SRand128();
    srand((unsigned int)TickCount());
    if (count > 0) {
        int remaining;
        remaining = count;
        do { rand(); } while (--remaining != 0);
    }
}
