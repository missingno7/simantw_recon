extern unsigned char far AlistT[];
#define AlistX(i) (((unsigned char far *)&AlistT(0))[(i) + 0x23a4 - 0x2f62])
#define AlistY(i) (((unsigned char far *)&AlistT(0))[(i) + 0x278e - 0x2f62])
#define AlistT(i) (((unsigned char far *)&AlistT(0))[(i)])
#define AlistM(i) (((unsigned char far *)&AlistT(0))[(i) + 0x2b78 - 0x2f62])
#define AlistS(i) (((unsigned char far *)&AlistT(0))[(i) + 0x334c - 0x2f62])
/* Disassembly-led reconstruction of the simulation tick coordinator. */
extern int far Cycle; extern int far match_position[];
extern long far GameTime;
extern unsigned int far OptionStates[];
extern int far AlwaysHealthy;
extern int far NextFeed;
extern int far FoodB;
extern int far IsGameOver;
extern int far gGameNeedsSaving;
extern int far FightBalloonCnt;
extern int far QueenBalloonCnt;
extern int far EggBalloonCnt;
extern int far RestBalloonCnt;
extern int far LastFightPnt[2];
extern int far LastRestPnt[2];
extern int far LastQueenPnt[2];
extern int far custRegHandle;
extern int far LastEggPnt;
extern int far CurGameType;
extern int far ModePopB[6];
extern int far ModePopR[6];
extern int far TemBModePop[20];
extern int far TemRModePop[20];
extern int far FlyAwayB;
extern int far FlyAwayR;
extern int near HealthB;
extern int near HealthR;
extern void far AddFood(int amount, int kind);
extern int far SRand1(int range);
extern void far CompactListA(void);
extern void far FullCount(void);
extern void far HistUpdate(void);
extern void near SmoothAlarm(void);
extern void far CompactListB(void);
extern void near FillHolesBN(void);
extern void near ColonySmellBN(void);
extern void near ColonySmellBT(void);
extern void far CompactListR(void);
extern void near FillHolesRN(void);
extern void near ColonySmellRN(void);
extern void near ColonySmellRT(void);
extern void far DoSimYard(void);
extern void far DoWater(void);
extern void far DoAntLions(void);
extern void far MoveSpider(void);
extern void far DoPillar(void);
extern int far GetStrategy(void);
extern void near DoAntSimA(void);
extern void near DoAntSimB(void);
extern void near DoAntSimR(void);
extern void near DoAntSimY(void);
extern void near MakeRedInitiator(void);
extern void near DoAntMoveY(void);
extern void far Feedback(void);
extern void far EndGameDialog(int mode);

void far DoAntSim(void)
{
    int far *cycle;
    int i;

    cycle = (int far *)match_position;
    cycle += 0x3afe;
    if (++*cycle > 0x1000)
        *cycle = 0;
    ++GameTime;

    if (OptionStates[5] == 1) {
        FightBalloonCnt = 0;
        QueenBalloonCnt = 0;
        EggBalloonCnt = 0;
        RestBalloonCnt = 0;
        LastFightPnt[0] = -1;
        LastFightPnt[1] = -1;
        LastRestPnt[0] = -1;
        LastRestPnt[1] = -1;
        LastQueenPnt[0] = -1;
        LastQueenPnt[1] = -1;
        custRegHandle = -1;
        LastEggPnt = -1;
    }

    if (((unsigned char far *)cycle)[0] & 0x3f) {
        /* The periodic counters and food update run only on a 64-tick edge. */
    } else {
        if (AlwaysHealthy == 0) {
            --HealthB;
            if (HealthB < 0)
                HealthB = 0;
        }
        --HealthR;
        if (HealthR < 0)
            HealthR = 0;
        if (CurGameType != 3 && NextFeed < FoodB) {
            AddFood(0x96, 1);
            NextFeed = SRand1(0x32) + 1;
        }
    }

    if (((unsigned char far *)cycle)[0] & 0x1f ? 0 : 1) {
        switch (((unsigned char far *)cycle)[0] >> 5 & 3) {
        case 0:
            CompactListA();
            break;
        case 1:
            FullCount();
            HistUpdate();
            SmoothAlarm();
            break;
        case 2:
            CompactListB();
            FillHolesBN();
            ColonySmellBN();
            ColonySmellBT();
            break;
        case 3:
            CompactListR();
            FillHolesRN();
            ColonySmellRN();
            ColonySmellRT();
            break;
        }
    }

    DoSimYard();
    DoWater();
    DoAntLions();
    MoveSpider();
    if (Cycle & 1)
        DoPillar();
    GetStrategy();

    for (i = 0; i < 20; ++i)
        TemRModePop[i] = 0;
    for (i = 0; i < 20; ++i)
        TemBModePop[i] = 0;

    if (FlyAwayB != 0)
        --FlyAwayB;
    if (FlyAwayR != 0)
        --FlyAwayR;

    DoAntSimA();
    DoAntSimB();
    DoAntSimR();
    DoAntSimY();

    ModePopB[0] = TemBModePop[2] + TemBModePop[3];
    ModePopB[1] = TemBModePop[4] + TemBModePop[5];
    ModePopB[2] = TemBModePop[1];
    ModePopB[3] = TemBModePop[7];
    ModePopB[4] = TemBModePop[12];
    ModePopB[5] = TemBModePop[6];
    ModePopR[0] = TemRModePop[2] + TemRModePop[3];
    ModePopR[1] = TemRModePop[4] + TemRModePop[5];
    ModePopR[2] = TemRModePop[1];
    ModePopR[3] = TemRModePop[7];
    ModePopR[4] = TemRModePop[12];
    ModePopR[5] = TemRModePop[6];

    if (TemRModePop[19] < 1)
        MakeRedInitiator();
    DoAntMoveY();
    Feedback();
    if (IsGameOver != 0)
        EndGameDialog(0);
    gGameNeedsSaving = 1;
}
