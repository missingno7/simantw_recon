/* local two-word union holding the first tick result; test ENTER reservation independently from the private seed binding. */

extern unsigned long far TickCount(void);
extern int far SRand128(void);
extern void far srand(unsigned int seed);
extern int far rand(void);
extern int near rrandSeed;
void SeedRRand(void) {
    union { unsigned long whole; unsigned int part[2]; } tick;
    int count;
    tick.whole = TickCount();
    rrandSeed = tick.part[0] ^ 0x3751;
    count = SRand128();
    srand((unsigned int)TickCount());
    if (count > 0) { int left=count; do { rand(); --left; } while (left != 0); }
}
