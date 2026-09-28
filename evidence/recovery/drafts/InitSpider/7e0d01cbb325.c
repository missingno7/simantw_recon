/* Initialize spider state in PACK, SIMANT_DATA_GROUP, and DGROUP at their
 * observed segment identities; Scycle2 follows the exact MAPSYM spelling. */
extern int __based(__segname("PACK")) SpidBurpCnt;
extern int __based(__segname("SIMANT_DATA_GROUP")) RevSpider;
extern int __based(__segname("PACK")) Scycle;
extern int __based(__segname("PACK")) Scycle2;
extern int __based(__segname("PACK")) EatCnt;
extern int __based(__segname("PACK")) SCorpseBase;
extern int __based(__segname("PACK")) SpidRevenge;
extern int near SpidDir;
extern int __based(__segname("PACK")) CurGameType;
extern int __based(__segname("PACK")) SpidOn;
extern int near SpidX;
extern int near SpidY;
extern int __based(__segname("PACK")) SMode;
extern int __based(__segname("PACK")) MeSMode;
extern int __based(__segname("PACK")) Starg;
extern int __based(__segname("PACK")) StargLife;
extern int __based(__segname("PACK")) SuserX;
extern int __based(__segname("PACK")) SuserY;

void far InitSpider(void)
{
    SpidBurpCnt = 10;
    EatCnt = 0;
    SCorpseBase = 0;
    Scycle = 0;
    Scycle2 = 0;
    SpidRevenge = 0;
    SpidDir = 0;
    RevSpider = 0;
    SpidOn = (CurGameType >= 1);
    SpidX = 0x400;
    SpidY = 0x200;
    SMode = 0;
    MeSMode = 0;
    Starg = -2;
    StargLife = -1;
    SuserX = 0x40;
    SuserY = 0x40;
}
