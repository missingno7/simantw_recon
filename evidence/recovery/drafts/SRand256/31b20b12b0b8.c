/* Preserve the old high bit, advance the private state, and return its low byte. */
static unsigned int near randSeed;
unsigned long far SRand256(void)
{
    unsigned int oldSeed;
    unsigned int result;
    oldSeed = randSeed;
    randSeed <<= 1;
    if (oldSeed & 0x8000) randSeed ^= 0x1bf5;
    result = randSeed & 0xff;
    return (unsigned long)result;
}
