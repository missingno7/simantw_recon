/* Candidate translation unit simtwo_1378_InitSimYard_12_scaffold_split: composed from preserved exact-body sources
 * in MAPSYM order. Internal evidence id, not a historical filename.
 * Members: _InitSimYard, _DoSimYard, _SendBoyMsg, _SimRain, _IsValidYard, _InitGrassMap, _SimCat, _FollowBoyDir, _FollowCatDir, _MakeBark, _MaintainSwarm, _GetNearbyPatches
 * SCAFFOLDED: unclaimed members _SimKidOutside, _SimKidInside, _SimBird, _SimDog, _SimColonies are stand-ins in POOLSTUB_TEXT (pool order only, never compared). */

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
extern int far GrassMap[];
extern int near CatX;
extern int near CatY;
extern int near YardMode;
extern int far CatDir;
extern int far MapMode;
extern char far Dx8[];
extern char far Dy8[];
extern int far SRand16(void);
extern int far SRand64(void);
extern unsigned long far GetDis(int x1, int y1, int x2, int y2);
extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);
extern int far DogPy;
extern int far DogPx;
extern long far DogBarkDelay;
extern int far SwarmCntB;
extern int far SwarmCntR;
extern int near QueenStorageB;
extern int near QueenStorageR;
extern unsigned char far YMapPopB[];
extern unsigned char far YMapPopR[];
static unsigned char PatchX[6] = { 0, 1, 0, 0xff, 0, 0 };
static unsigned char PatchY[6] = { 0xff, 0, 1, 0, 0, 0 };

extern int far LastMowX;  /* scaffold reference for pool word C534 (segment 9, MAPSYM_SITE_NAME) */
extern int far LastMowY;  /* scaffold reference for pool word C536 (segment 9, MAPSYM_SITE_NAME) */
extern int far BxTab;  /* scaffold reference for pool word C53A (segment 8, MAPSYM_SITE_NAME) */
extern int far ByTab;  /* scaffold reference for pool word C53C (segment 8, MAPSYM_SITE_NAME) */
extern int far CurGameType;  /* scaffold reference for pool word C53E (segment 9, MAPSYM_SITE_NAME) */
extern int far ListIndexA;  /* scaffold reference for pool word C540 (segment 9, MAPSYM_SITE_NAME) */
extern int far SpidOn;  /* scaffold reference for pool word C542 (segment 9, MAPSYM_SITE_NAME) */
extern int far MeMode;  /* scaffold reference for pool word C544 (segment 9, MAPSYM_SITE_NAME) */
extern int far CurYardPnt;  /* scaffold reference for pool word C548 (segment 9, MAPSYM_SITE_NAME) */
extern int far AlistT;  /* scaffold reference for pool word C54A (segment 8, MAPSYM_SITE_NAME) */
extern int far match_position;  /* scaffold reference for pool word C54C (segment 9, MAPSYM_SITE_NAME) */
extern int far gameCycles;  /* scaffold reference for pool word C54E (segment 9, MAPSYM_SITE_NAME) */
extern int far match_length;  /* scaffold reference for pool word C550 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far BirdGoalX;  /* scaffold reference for pool word C552 (segment 9, MAPSYM_SITE_NAME) */
extern int far BirdGoalY;  /* scaffold reference for pool word C554 (segment 9, MAPSYM_SITE_NAME) */

void far pool_stub_SimKidOutside(void);
void far pool_stub_SimKidInside(void);
void far pool_stub_SimBird(void);
void far pool_stub_SimDog(void);
void far pool_stub_SimColonies(void);
int IsValidYard(int x,int y);
void InitGrassMap(void);
void far SimCat(void);
int far FollowBoyDir(void);
int FollowCatDir(void);
void far MakeBark(int kind, int level);
void far MaintainSwarm(void);
int far GetNearbyPatches(int x, int y);

#pragma alloc_text(POOLSTUB_TEXT, pool_stub_SimKidOutside)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_SimKidInside)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_SimBird)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_SimDog)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_SimColonies)
#pragma alloc_text(RUN2_TEXT, IsValidYard, InitGrassMap)
#pragma alloc_text(RUN3_TEXT, SimCat)
#pragma alloc_text(RUN4_TEXT, FollowBoyDir, FollowCatDir, MakeBark)
#pragma alloc_text(RUN5_TEXT, MaintainSwarm)
#pragma alloc_text(RUN6_TEXT, GetNearbyPatches)

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

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _SimKidOutside.
 * It only reproduces the object's selector-pool allocation order for the
 * words C534 C536 C538 C53A C53C C53E C540 C542 C544; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_SimKidOutside(void)
{
    volatile int t;

    t = LastMowX;
    t = LastMowY;
    t = GrassMap[0];
    t = BxTab;
    t = ByTab;
    t = CurGameType;
    t = ListIndexA;
    t = SpidOn;
    t = MeMode;
}

int IsValidYard(int x,int y) { if(x>=0 && y>=0 && x<=11 && y<=15) return 1; return 0; }

void InitGrassMap(void)
{
    int i;

    GrassMap[0] = 0;
    GrassMap[1] = 0;
    GrassMap[2] = 0;
    for (i = 0; i < 9; ++i)
        GrassMap[i + 3] = -1;
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _SimKidInside.
 * It only reproduces the object's selector-pool allocation order for the
 * words C546 C548 C54A; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_SimKidInside(void)
{
    volatile int t;

    t = (int)MapMode;
    t = CurYardPnt;
    t = AlistT;
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _SimBird.
 * It only reproduces the object's selector-pool allocation order for the
 * words C54C C54E C550 C552 C554; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_SimBird(void)
{
    volatile int t;

    t = match_position;
    t = gameCycles;
    t = match_length;
    t = BirdGoalX;
    t = BirdGoalY;
}

void far SimCat(void)
{
    int oldCatOn;
    int direction;
    int newX;
    int newY;
    unsigned long dis;

    oldCatOn = CatOn;
    if (oldCatOn != 0) {
        CatCycle = (CatCycle + 1) & 0xfff;
        if (oldCatOn == 1) {
            direction = CatDir;
            newX = CatX + Dx8[direction] * 4;
            newY = CatY + Dy8[direction] * 4;
            if (SRand16() != 0) {
                if (newX >= 0xfc && newX <= 0x1ef) {
                    CatX = newX;
                    CatY = newY;
                    CatFrame++;
                    if (CatDir == 2) {
                        if (CatFrame >= 3)
                            CatFrame = 1;
                    } else {
                        if (CatFrame >= 6)
                            CatFrame = 4;
                    }
                    goto barkCheck;
                }
            }
            if (CatDir == 2) {
                CatDir = 6;
                CatFrame = 4;
            } else {
                CatDir = 2;
                CatFrame = 1;
            }
        barkCheck:
            if (MapMode == 0 && YardMode < 2) {
                if (SRand64() == 0) {
                    myBeginSound(0xd, 0, 5);
                    return;
                }
            }
            if (SRand16() == 0 && CatCycle > 100 && DogDir == 2 && BoyHere == 0) {
                CatOn = 2;
                CatCycle = 0;
                CatFrame = 10;
                return;
            }
            if (CatCycle > 50) {
                dis = GetDis(CatX, CatY, DogX, DogY);
                if (dis <= 0x960) {
                    CatOn = 3;
                    CatFrame = 20;
                    if (MapMode == 0 && YardMode < 2) {
                        myBeginSound(0xe, 0, 5);
                        return;
                    }
                }
            }
            return;
        } else if (oldCatOn == 2) {
            CatFrame++;
            if (CatFrame >= 13)
                CatFrame = 11;
            CatCycle++;
            if (CatCycle > 30) {
                CatCycle = 0;
                CatOn = 1;
                CatFrame = (CatDir == 2) ? 0 : 3;
                return;
            }
            return;
        } else {
            CatFrame++;
            if (CatFrame >= 30) {
                CatFrame = 0;
                CatOn = 0;
                CatDelay = MacTickCount() + 600L;
                return;
            }
            return;
        }
    }
    if (MacTickCount() > CatDelay) {
        CatDelay = MacTickCount() + 200L;
        if (SRand16() == 0 || GlobalKey == 0x8d) {
            CatOn = 1;
            CatX = 0xfc;
            CatY = 0x19;
            CatDir = 2;
            CatFrame = 0;
            CatCycle = 0;
        }
    }
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _SimDog.
 * It only reproduces the object's selector-pool allocation order for the
 * words C55C C55E C560; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_SimDog(void)
{
    volatile int t;

    t = (int)DogPx;
    t = (int)DogPy;
    t = (int)DogBarkDelay;
}

int far FollowBoyDir(void)
{
    int dy, dx;
    int ady, adx;

    dx = DogPx - BoyPx;
    dy = DogPy - BoyPy;
    if (dx < 0)
        adx = -dx;
    else
        adx = dx;
    if (dy < 0)
        ady = -dy;
    else
        ady = dy;

    if (adx < 1 && ady < 1) {
        if (BoyIsMowing != 0 && MapMode == 0 && YardMode < 2 && MacTickCount() > DogBarkDelay) {
            switch (1) {
            case 0:
            case 2:
                myBeginSound(0x17, 0, 0x7f);
                break;
            case 1:
                myBeginSound(0x15, 0, 0x7f);
                break;
            case 3:
                myBeginSound(0x16, 0, 0x7f);
                break;
            }
            DogBarkDelay = SRand1(30) + MacTickCount() + 60;
        }
    }

    if (adx < 2 && ady < 2)
        return YardCycle & 3;
    if (dy < 0)
        return 2;
    if (dy > 1)
        return 0;
    if (dx < 0)
        return 1;
    if (dx > 1)
        return 3;
    return YardCycle & 3;
}

int FollowCatDir(void)
{
    int direction;

    direction = DogPx;
    if (direction < 5)
        return 1;
    if (*(volatile int *)&direction > 8)
        return 3;
    if (DogPy > 0)
        return 0;
    return YardCycle & 3;
}

void far MakeBark(int kind, int level)
{
    if (MapMode == 0 && YardMode < 2 && MacTickCount() > DogBarkDelay) {
        switch (kind) {
        case 3:
            myBeginSound(0x17, 0, level);
            break;
        case 1:
            myBeginSound(0x15, 0, level);
            break;
        case 0:
        case 2:
            myBeginSound(0x16, 0, level);
            break;
        }
        DogBarkDelay = SRand1(30) + MacTickCount() + 60;
    }
}

void far MaintainSwarm(void)
{
    int n;

    n = SwarmCntB;
    if (SwarmCntB > 0) {
        if (SwarmCntB >= 4)
            n = SwarmCntB - (SwarmCntB >> 2);
        else
            n = SwarmCntB - 1;
    }
    if (QueenStorageB > n)
        n = QueenStorageB;
    if (n > 50)
        n = 50;
    SwarmCntB = n;

    n = SwarmCntR;
    if (SwarmCntR > 0) {
        if (SwarmCntR >= 4)
            n = SwarmCntR - (SwarmCntR >> 2);
        else
            n = SwarmCntR - 1;
    }
    if (QueenStorageR > n)
        n = QueenStorageR;
    if (n > 50)
        n = 50;
    SwarmCntR = n;

}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _SimColonies.
 * It only reproduces the object's selector-pool allocation order for the
 * words C562 C564; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_SimColonies(void)
{
    volatile int t;

    t = YMapPopR[0];
    t = YMapPopB[0];
}

int far GetNearbyPatches(int x, int y)
{
    int index;
    register int offset;
    int count;
    register int patchX;
    register int patchY;

    count = 0;
    for (index = 0; index < 6; ++index) {
        patchY = PatchY[index] + y;
        patchX = PatchX[index] + x;
        if (patchX >= 0 && patchY >= 0 &&
            patchX < 12 && patchY < 16) {
            offset = (patchX << 4) + patchY;
            if (YMapPopB[(patchX << 4) + patchY] != 0)
                count += 3;
            if (YMapPopR[(patchX << 4) + patchY] != 0)
                count -= 3;
        }
    }
    return count;
}

