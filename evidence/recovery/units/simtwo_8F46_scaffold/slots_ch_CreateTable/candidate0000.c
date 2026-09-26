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
    unsigned int tableSize;
    int divisorIndex;
    int i;

    if (wanted == 0) {
        tableSize = 150;
        goto allocate_table;
    }

    lastPrime = 1;
    candidate = 2;
    primes = (int far *)mem_malloc(0x320, "primes");
    if (wanted > 1) {
        primeCount = 0;
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
    tableSize = lastPrime;

allocate_table:
    handle = mem_Alloc((unsigned long)(tableSize * 6 + 4), 0, "cachetable");
    table = (unsigned char far *)mem_Lock(handle);
    for (i = 0; i < ((unsigned int)tableSize + 1) * 4; ++i)
        table[i] = 0xff;
    ((int far *)table)[0] = tableSize;
    ((int far *)table)[1] = 0;
    mem_Unlock(handle);
    return handle;
}
