/* Exact MAPSYM Scycle2 spelling; CMP 1 / SBB / INC motivates unsigned CurGameType. */
extern int far SpidBurpCnt;
extern int far RevSpider;
extern int far Scycle;
extern int far EatCnt;
extern int far Scycle2;
extern int far SpidRevenge;
extern int far SMode;
extern int far MeSMode;
extern int near SpidDir;
extern int near SpidX;
extern int near SpidY;
extern unsigned int far CurGameType;
extern int far SpidOn;
extern int far SCorpseBase;
extern int far Starg;
extern int far StargLife;
extern int far SuserX;
extern int far SuserY;

void InitSpider(void)
{
    SpidBurpCnt = 10;
    EatCnt = 0;
    SCorpseBase = 0;
    Scycle = 0;
    Scycle2 = 0;
    SpidRevenge = 0;
    SpidDir = 0;
    RevSpider = 0;
    SpidOn = (CurGameType != 0);
    SpidX = 0x400;
    SpidY = 0x200;
    SMode = 0;
    MeSMode = 0;
    Starg = -2;
    StargLife = -1;
    SuserX = 0x40;
    SuserY = 0x40;
}
