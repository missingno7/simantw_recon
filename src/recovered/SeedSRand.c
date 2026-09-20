extern unsigned long far TickCount(void);
extern int near edata[];

void SeedSRand(void)
{
    edata[201] = (unsigned int)TickCount() ^ 0x3751;
}
