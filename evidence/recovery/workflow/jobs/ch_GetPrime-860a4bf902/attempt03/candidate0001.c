/*
 * ch_GetPrime: return the first prime at or above the limit (or the
 * largest found).  Candidates from 2 upwards are trial-divided by the
 * primes found so far, kept in a far "primes" buffer of up to 400 words
 * from mem_malloc; each new prime is recorded and becomes the result
 * until it reaches the limit or the buffer is full.  The buffer is freed.
 */
extern void far * far mem_malloc(unsigned int bytes, char far *name);
extern void far mem_free(void far *block);

int far ch_GetPrime(int limit)
{
    int i;
    int count;
    int far *primes;
    int candidate;
    int prime;

    prime = 1;
    candidate = 2;
    count = 0;
    primes = mem_malloc(0x320, "primes");
    while (prime < limit) {
        if (count >= 400)
            break;
        for (i = 0; i < count; i++)
            if (candidate % primes[i] == 0)
                goto next;
        prime = candidate;
        primes[count++] = candidate;
    next:
        candidate++;
    }
    mem_free(primes);
    return prime;
}
