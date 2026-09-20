extern int SMode[];
extern int DeathCnt[];
extern int Scycle[];

void KillSpider(void)
{
    SMode[0] = 5;
    DeathCnt[0] = 500;
    Scycle[0] = 0;
}
