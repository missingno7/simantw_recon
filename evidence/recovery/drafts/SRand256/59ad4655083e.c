/* Update the private generator word from its old high bit and return low 8 bits. */
static unsigned int near randSeed;
unsigned long far SRand256(void)
{
    unsigned int result;
    randSeed = (randSeed << 1) ^ ((randSeed & 0x8000) ? 0x1bf5 : 0);
    result = randSeed & 0xff;
    return (unsigned long)result;
}
