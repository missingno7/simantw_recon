static unsigned int seed;

unsigned long GetSRandSeed(void)
{
    return (unsigned long)(unsigned int)seed;
}
