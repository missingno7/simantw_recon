extern int near edata[];

unsigned long GetSRandSeed(void)
{
    return (unsigned long)(unsigned int)edata[201];
}
