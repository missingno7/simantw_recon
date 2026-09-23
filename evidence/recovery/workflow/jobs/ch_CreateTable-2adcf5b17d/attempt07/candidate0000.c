/* Compute a prime-sized channel hash table and initialize its sentinel words. */
extern void far *mem_malloc(unsigned int size, char far *name);
extern void far mem_free(void far *memory);
extern unsigned int far mem_Alloc(unsigned long bytes, int kind, char far *name);
extern void far *mem_Lock(unsigned int handle);
extern int far mem_Unlock(unsigned int handle);

unsigned int far ch_CreateTable(register int wanted)
{
    int far *primes;
    unsigned int handle;
    unsigned char far *table;
    int primeCount;
    int lastPrime;
    int candidate;
    register int divisorIndex;
    register unsigned int size;
    int i;

    if (wanted == 0) {
        size = 150;
        goto allocate_table;
    } else {
        primes = (int far *)mem_malloc(0x320, "primes");
        lastPrime = 1;
        if (wanted > 1) {
            primeCount = 0;
            candidate = 2;
            while (primeCount < 400 && lastPrime < wanted) {
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
            }
        }
        mem_free(primes);
        size = lastPrime;
    }

allocate_table:
    handle = mem_Alloc((unsigned long)(size * 6 + 4), 0, "cachetable");
    table = (unsigned char far *)mem_Lock(handle);
    for (i = 0; i < ((unsigned int)size + 1) * 4; ++i)
        table[i] = 0xff;
    ((int far *)table)[0] = size;
    ((int far *)table)[1] = 0;
    mem_Unlock(handle);
    return handle;
}

