/* One shared SIMONE random state with the observed 16-bit shift-register
 * recurrence.  The state is file-scope BSS used by every seed accessor. */
static unsigned int seed;

extern unsigned long far TickCount(void);
extern int far SRand128(void);
extern void far srand(unsigned int value);
extern int far rand(void);

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

unsigned long GetRRandSeed(void)
{
    return *(unsigned long far *)0x046c0000L;
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

int RRand(int limit)
{
    int value;
    value = rand();
    if (value < 0) value = -value;
    return value % limit;
}

int SRand1(int range)
{
    int result;
    if (seed & 0x8000)
        seed = (seed << 1) ^ 0x1bf5;
    else
        seed <<= 1;
    result = seed % range;
    return result;
}

int SRand2(void)
{
    int result;
    if (seed & 0x8000)
        seed = (seed << 1) ^ 0x1bf5;
    else
        seed <<= 1;
    result = seed & 1;
    return result;
}

int SRand4(void)
{
    int result;
    if (seed & 0x8000)
        seed = (seed << 1) ^ 0x1bf5;
    else
        seed <<= 1;
    result = seed & 3;
    return result;
}

int SRand8(void)
{
    int result;
    if (seed & 0x8000)
        seed = (seed << 1) ^ 0x1bf5;
    else
        seed <<= 1;
    result = seed & 7;
    return result;
}

int SRand16(void)
{
    int result;
    if (seed & 0x8000)
        seed = (seed << 1) ^ 0x1bf5;
    else
        seed <<= 1;
    result = seed & 0x0f;
    return result;
}

int SRand32(void)
{
    int result;
    if (seed & 0x8000)
        seed = (seed << 1) ^ 0x1bf5;
    else
        seed <<= 1;
    result = seed & 0x1f;
    return result;
}

int SRand64(void)
{
    int result;
    if (seed & 0x8000)
        seed = (seed << 1) ^ 0x1bf5;
    else
        seed <<= 1;
    result = seed & 0x3f;
    return result;
}

int SRand128(void)
{
    int result;
    if (seed & 0x8000)
        seed = (seed << 1) ^ 0x1bf5;
    else
        seed <<= 1;
    result = seed & 0x7f;
    return result;
}

int SRand256(void)
{
    int result;
    if (seed & 0x8000)
        seed = (seed << 1) ^ 0x1bf5;
    else
        seed <<= 1;
    result = seed & 0xff;
    return result;
}
