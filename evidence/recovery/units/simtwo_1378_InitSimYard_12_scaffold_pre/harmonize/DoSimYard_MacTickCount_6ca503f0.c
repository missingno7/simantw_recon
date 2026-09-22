/* Candidate translation unit simtwo_1378_InitSimYard_4: composed from preserved exact-body sources
 * in MAPSYM order. Internal evidence id, not a historical filename.
 * Members: _InitSimYard, _DoSimYard, _SendBoyMsg, _SimRain */

extern unsigned long far BoyMsgCnt;
extern int near BoyX;
extern int near BoyY;
extern int far BoyTurnCnt;
extern int far BoyWait;
extern long far BirdDelay;
extern long far CatDelay;
extern int near DogX;
extern int near DogY;
extern int far BoyDir;
extern int far DogTurnCnt;
extern int far BoyMessOn;
extern int far BoyPx;
extern int far BoyPy;
extern int near BoyFrame;
extern int near BoyHere;
extern int far BoyStandCnt;
extern int far NodeCnt;
extern int far NodeNum;
extern int near BirdOn;
extern int far CatCycle;
extern int near CatFrame;
extern int near CatOn;
extern int near DogFrame;
extern int far DogDir;
extern int far FootHere;
extern int far FootTog;
extern int far FootX;
extern int far FootY;
extern int far MowX;
extern int far MowY;
extern int far BoyIsMowing;
extern int near RainOn;
extern int far SwarmDelayB;
extern int far SwarmDelayR;
extern int near BirdFrame;
extern int far LastColonyPopB;
extern int far LastColonyPopR;
extern int far BoyMsgOffset;
extern int far YardCycle;
extern int near ForSaleState;
extern int far TERRAINset;
extern int far GlobalKey;
extern int far RainCnt;
extern void far SimKidInside(void);
extern void far SimKidOutside(void);
extern void far SimBird(void);
extern void far SimCat(void);
extern void far SimDog(void);
extern void far SimColonies(void);
extern int far RRand(int range);
extern int far SRand1(int range);
extern void far InitWater(void);
extern long far MacTickCount(void);

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

void far DoSimYard(void)
{
    YardCycle++;
    if (YardCycle >= 0x400)
        YardCycle = 0;

    if (NodeNum < 0x26)
        SimKidInside();
    else
        SimKidOutside();
    SimBird();
    SimCat();
    if (ForSaleState == 0)
        SimDog();

    if (TERRAINset != 1) {
        if (RainOn == 0) {
            if (GlobalKey != 0xa8) {
                if (RRand(32) != 0)
                    goto done;
                if (RRand(128) != 0)
                    goto done;
            }
            RainOn = 1;
            RainCnt = SRand1(150) + 150;
            InitWater();
            BoyMsgCnt = MacTickCount() + 300L;
            BoyMessOn = 1;
            BoyMsgOffset = 0;
            goto done;
        }
        if (RainCnt > 0)
            RainCnt--;
        if (RainCnt < 1)
            RainOn = 0;
    }
done:
    SimColonies();
}

void SendBoyMsg(int message) {
    if (message <= 22) {
        BoyMsgCnt = MacTickCount() + 300L;
        BoyMessOn = 1;
        BoyMsgOffset = message;
    }
}

void far SimRain(void)
{
    if (TERRAINset != 1) {
        if (RainOn == 0) {
            if (GlobalKey != 0xa8) {
                if (RRand(32) != 0)
                    return;
                if (RRand(128) != 0)
                    return;
            }
            RainOn = 1;
            RainCnt = SRand1(150) + 150;
            InitWater();
            BoyMsgCnt = MacTickCount() + 300;
            BoyMessOn = 1;
            BoyMsgOffset = 0;
            return;
        }
        if (RainCnt > 0)
            RainCnt--;
        if (RainCnt < 1)
            RainOn = 0;
    }
}

