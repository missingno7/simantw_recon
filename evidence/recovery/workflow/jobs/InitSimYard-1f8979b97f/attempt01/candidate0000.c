/*
 * InitSimYard: reset every piece of per-yard simulation state to its
 * starting value. Straight-line initializer, no branches; the boy and
 * dog start at fixed map coordinates, most counters/positions go to 0,
 * a few frame/population counters start at 1, and BoyMsgOffset/
 * YardCycle are reset to the -1 sentinel. This is the first function
 * in the unit to touch each of these far PACK objects, so its
 * reference order fixes the whole unit's CONST selector pool.
 */
extern unsigned long far BoyMsgCnt;
extern int BoyX;
extern int BoyY;
extern int far BoyTurnCnt;
extern int far BoyWait;
extern long far BirdDelay;
extern long far CatDelay;
extern int DogX;
extern int DogY;
extern int far BoyDir;
extern int far DogTurnCnt;
extern unsigned int far BoyMessOn;
extern int far BoyPx;
extern int far BoyPy;
extern int BoyFrame;
extern int BoyHere;
extern int far BoyStandCnt;
extern int far NodeCnt;
extern int far NodeNum;
extern int BirdOn;
extern int far CatCycle;
extern int CatFrame;
extern int CatOn;
extern int DogFrame;
extern int far DogDir;
extern int far FootHere;
extern int far FootTog;
extern int far FootX;
extern int far FootY;
extern int far MowX;
extern int far MowY;
extern int far BoyIsMowing;
extern int RainOn;
extern int far SwarmDelayB;
extern int far SwarmDelayR;
extern int BirdFrame;
extern int far LastColonyPopB;
extern int far LastColonyPopR;
extern unsigned int far BoyMsgOffset;
extern int far YardCycle;

void far InitSimYard(void)
{
    BoyMsgCnt = 0L;
    BoyX = 0xb4;
    BoyY = 0x49;
    BoyTurnCnt = 0xc;
    BoyWait = 0x14;
    BirdDelay = 0L;
    CatDelay = 0L;
    DogX = 0xfa;
    DogY = 0x96;
    BoyDir = 2;
    DogTurnCnt = 2;
    BoyMessOn = 0;
    BoyPx = 0;
    BoyPy = 0;
    BoyFrame = 0;
    BoyHere = 0;
    BoyStandCnt = 0;
    NodeCnt = 0;
    NodeNum = 0;
    BirdOn = 0;
    CatCycle = 0;
    CatFrame = 0;
    CatOn = 0;
    DogFrame = 0;
    DogDir = 0;
    FootHere = 0;
    FootTog = 0;
    FootX = 0;
    FootY = 0;
    MowX = 0;
    MowY = 0;
    BoyIsMowing = 0;
    RainOn = 0;
    SwarmDelayB = 0;
    SwarmDelayR = 0;
    BirdFrame = 1;
    LastColonyPopB = 1;
    LastColonyPopR = 1;
    BoyMsgOffset = -1;
    YardCycle = -1;
}
