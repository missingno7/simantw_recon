/* Candidate translation unit simone_1506_SetSRandSeed_6_scaffold: composed from preserved exact-body sources
 * in MAPSYM order. Internal evidence id, not a historical filename.
 * Members: _SetSRandSeed, _GetSRandSeed, _SetRRandSeed, _SeedSRand, _SeedRRand, _RRand
 * SCAFFOLDED: claimed members in 2 code runs; no pool stand-ins were needed. */

extern unsigned long far TickCount(void);
extern int far SRand128(void);
extern void far srand(unsigned int value);
extern int far rand(void);


void SeedSRand(void);
void SeedRRand(void);
int RRand(int limit);

#pragma alloc_text(RUN2_TEXT, SeedSRand, SeedRRand, RRand)

static unsigned int seed;
void SetSRandSeed(int value)
{
    seed = value;
}

unsigned long GetSRandSeed(void)
{
    return (unsigned long)(unsigned int)seed;
}

void SetRRandSeed(void)
{
}

void SeedSRand(void)
{
    seed = (unsigned int)TickCount() ^ 0x3751;
}

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

int RRand(int limit) { int v=rand(); if(v<0) v=-v; return v%limit; }

