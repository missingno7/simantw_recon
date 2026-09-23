/* Compute a prime-sized channel hash table and initialize its sentinel words. */
extern void far *mem_malloc(unsigned int size, char far *name);
extern void far mem_free(void far *memory);
extern unsigned int far mem_Alloc(unsigned long bytes, int kind, char far *name);
extern void far *mem_Lock(unsigned int handle);
extern int far mem_Unlock(unsigned int handle);

unsigned int far ch_CreateTable(unsigned int wanted)
{
    unsigned int far *primes;
    unsigned int handle;
    unsigned char far *table;
    unsigned int primeCount;
    unsigned int candidate;
    unsigned int divisorIndex;
    unsigned int lastPrime;
    unsigned int i;
    int prime;

    if (wanted == 0) {
        lastPrime = 150;
    } else {
        primes = (unsigned int far *)mem_malloc(0x320, "primes");
        lastPrime = 1;
        if (wanted > 1) {
            primeCount = 0;
            candidate = 2;
            while (primeCount < 400 && lastPrime < wanted) {
                prime = 1;
                divisorIndex = 0;
                while (divisorIndex < primeCount) {
                    if (candidate % primes[divisorIndex] == 0) {
                        prime = 0;
                        break;
                    }
                    ++divisorIndex;
                }
                if (prime) {
                    primes[primeCount] = candidate;
                    ++primeCount;
                    lastPrime = candidate;
                }
                ++candidate;
            }
        }
        mem_free(primes);
    }

    handle = mem_Alloc((unsigned long)lastPrime * 6L + 4L,
                       0, "cachetable");
    table = (unsigned char far *)mem_Lock(handle);
    for (i = 0; i < (lastPrime + 1) * 4; ++i)
        table[i] = 0xff;
    ((unsigned int far *)table)[0] = lastPrime;
    ((unsigned int far *)table)[1] = 0;
    mem_Unlock(handle);
    return handle;
}
