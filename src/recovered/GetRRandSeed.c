/* Candidate reconstruction of the fixed far-memory random seed accessor. */
unsigned long GetRRandSeed(void)
{
    return *(unsigned long far *)0x046c0000L;
}
