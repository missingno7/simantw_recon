/* Compute a prime-sized channel hash table and initialize its sentinel words. */
extern void far *mem_malloc(unsigned int size, char far *name);
extern void far mem_free(void far *memory);
typedef void (far *CacheReleaseHook)(void);
struct CacheReleaseData {
    CacheReleaseHook releaseFunction;
    char cacheTableName[32];
    char diagnostics[534];
    void far *packBuffer;
};
extern struct CacheReleaseData near releaseHook;

extern unsigned int far mem_Alloc(unsigned long bytes, int kind, char far *name);
extern void far *mem_Lock(unsigned int handle);
extern int far mem_Unlock(unsigned int handle);

volatile int ch_CreateTable(int wanted)
{
    int far *primes;
    unsigned int handle;
    unsigned char far *table;
    int primeCount;
    int lastPrime;
    int candidate;
    int divisorIndex;
    int i;

    if (wanted == 0) {
        lastPrime = 150;
        goto allocate_table;
    }

    lastPrime = 1;
    candidate = 2;
    primeCount = 0;
    primes = (int far *)mem_malloc(0x320, releaseHook.diagnostics + 173);
    if (wanted > 1) {
            while (primeCount < 400) {
                divisorIndex = 0;
                while (divisorIndex < primeCount) {
                    if (candidate % primes[divisorIndex] == 0)
                        goto next_candidate;
                    ++divisorIndex;
                }
                primes[primeCount] = candidate;
                ++primeCount;
                lastPrime = candidate;
next_candidate:
                ++candidate;
                if (lastPrime >= wanted)
                    break;
            }
    }
    mem_free(primes);

allocate_table:
    handle = mem_Alloc((unsigned long)(lastPrime * 6 + 4), 0, releaseHook.cacheTableName);
    table = (unsigned char far *)mem_Lock(handle);
    for (i = 0; i < ((unsigned int)lastPrime + 1) * 4; ++i)
        table[i] = 0xff;
    ((int far *)table)[0] = lastPrime;
    ((int far *)table)[1] = 0;
    mem_Unlock(handle);
    return handle;
}
