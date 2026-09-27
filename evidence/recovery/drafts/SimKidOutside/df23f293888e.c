/* Private character, direction and foot-offset tables used by the boy simulation. */
static signed char near kidCycleFrame[4] = { 0, 1, 2, 1 };
static signed char near kidDirectionFrame[4] = { 0, 3, 6, 9 };
static int near kidMowXFrame[4] = { -10, 25, -10, -33 };
static int near kidMowYFrame[4] = { -33, -10, 25, -10 };
static signed char near kidStepX[4] = { 0, 1, 0, -1 };
static signed char near kidStepY[4] = { -1, 0, 1, 0 };

extern int near BoyHere;
extern int near RainOn;
extern int near BoyX;
extern int near BoyY;
extern int near BoyFrame;
extern int near MePlane;
extern unsigned char near LifeA[];

extern unsigned long far BoyMsgCnt;
extern int far BoyTurnCnt;
extern int far BoyDir;
extern int far BoyMessOn;
extern int far BoyMsgOffset;
extern int far BoyPx;
extern int far BoyPy;
extern int far BoyIsMowing;
extern int far BoyStandCnt;
extern int far FootHere;
extern int far FootX;
extern int far FootY;
extern int far YardCycle;
extern int far LastMowX;
extern int far LastMowY;
extern int far GrassMap[];
extern signed char far BxTab[];
extern signed char far ByTab[];
extern int far CurGameType;
extern int far ListIndexA;
extern int far SpidOn;
extern int far MeMode;
extern int far SRand1(int range);
extern int far SRand32(void);
extern int far SRand4(void);
extern long far MacTickCount(void);
extern void far FootFall(int x, int y);
extern void far KillSpider(void);
extern void far YellowDeath(int code);
extern void *memset(void *, int, unsigned);

extern int __based(__segname("SIMANT_DATA_GROUP")) NodeNum;
extern int __based(__segname("SIMANT_DATA_GROUP")) FootTog;
extern signed char __based(__segname("SIMANT_DATA_GROUP")) AlistT[];
extern signed char __based(__segname("SIMANT_DATA_GROUP")) AlistM[];
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) YMapPopB[];
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) YMapPopR[];
extern int __based(__segname("PACK")) CurYardPnt[2];
extern int __based(__segname("PACK")) MowX;
extern int __based(__segname("PACK")) MowY;
extern int __based(__segname("PACK")) BColoniesKilled;
extern int __based(__segname("PACK")) RColoniesKilled;

/* Tick the boy, choose his next yard cell, update the foot/mower marker, then
 * resolve ants and spiders affected by the newly occupied mower cell. */
void far SimKidOutside(void)
{
    int x;
    int y;
    int direction;
    int mask;
    int message;
    int pixelX;
    int pixelY;
    int population;
    int index;

    /* A visible foot or the slow yard phases hold this tick at the exit. */
    if (FootHere == 0 || (YardCycle & 3) == 0) {

    /* A mower move only hunts adjacent uncut cells after its last cut cell. */
    if (BoyIsMowing != 0) {
        if (BoyPx == LastMowX && BoyPy == LastMowY)
            goto turn_and_state;
    } else {
        goto turn_and_state;
    }

    x = BoyPx;
    y = BoyPy;
    for (direction = 3; direction >= 0; --direction) {
        if (x + kidStepX[direction] >= 0 && x + kidStepX[direction] <= 11 &&
            y + kidStepY[direction] >= 0 && y + kidStepY[direction] <= 15) {
            mask = 1 << (y + kidStepY[direction]);
            if ((GrassMap[x + kidStepX[direction]] & mask) != 0) {
                GrassMap[x + kidStepX[direction]] -= mask;
                BoyDir = direction;
                goto turn_and_state;
            }
        }
    }

    if (BoyPx > 10) {
        BoyDir = 0;
        goto turn_and_state;
    }
    if (BoyPy > 14) {
        BoyDir = 1;
        goto turn_and_state;
    }
    if (BoyPy >= 1) {
        BoyDir = YardCycle & 3;
        goto turn_and_state;
    }

    BoyMsgCnt = MacTickCount() + 300L;
    BoyMessOn = 1;
    BoyMsgOffset = 6;
    BoyHere = 4;
    BoyDir = 2;

turn_and_state:
    --BoyTurnCnt;
    if (BoyTurnCnt < 0) {
        BoyDir = (BoyDir + SRand1(3) - 1) & 3;
        BoyTurnCnt = 4;
    }

    /* The BoyHere stages walk the child into and out of the mowing routine. */
    switch (BoyHere) {
    case 1:
        if (SRand1(900) == 0) {
            BoyMsgCnt = MacTickCount() + 300L;
            BoyMessOn = 1;
            BoyMsgOffset = 1;
            BoyHere = 2;
            goto animate_boy;
        }
        if (SRand1(600) == 0 || CurGameType == 3 || CurGameType == 0) {
            BoyMsgCnt = MacTickCount() + 300L;
            BoyMessOn = 1;
            BoyMsgOffset = 2;
            if (RainOn != 0)
                BoyHere = 5;
            goto animate_boy;
        }
        if (SRand1(200) == 0) {
            message = SRand1(8) + 7;
            if (message <= 22) {
                BoyMsgCnt = MacTickCount() + 300L;
                BoyMessOn = 1;
                BoyMsgOffset = message;
            }
        }
        if (RainOn != 0)
            BoyHere = 5;
        goto animate_boy;

    case 2:
        if (BoyPy < 12) {
            BoyDir = 2;
            goto animate_boy;
        }
        if (BoyPy > 12) {
            BoyDir = 0;
            goto animate_boy;
        }
        if (BoyPx > 3) {
            BoyDir = 3;
            goto animate_boy;
        }
        BoyHere = 3;
        LastMowX = BoyPx;
        LastMowY = 13;
        BoyIsMowing = 1;
        GrassMap[0] = 0;
        GrassMap[1] = 0;
        GrassMap[2] = 0;
        for (index = 3; index < 12; ++index)
            GrassMap[index] = 0xffff;
        BoyDir = 2;
        BoyX = 125;
        BoyY = 170;
        goto animate_boy;

    case 3:
        if (SRand1(100) == 0) {
            message = SRand1(3) + 3;
            if (message <= 22) {
                BoyMsgCnt = MacTickCount() + 300L;
                BoyMessOn = 1;
                BoyMsgOffset = message;
            }
        }
        if (SRand1(200) == 0) {
            BoyMsgCnt = MacTickCount() + 300L;
            BoyMessOn = 1;
            BoyMsgOffset = 6;
            BoyHere = 4;
            LastMowX = BoyPx;
            LastMowY = BoyPy;
        }
        goto animate_boy;

    case 4:
        if (BoyPy < 12) {
            BoyDir = 2;
            goto animate_boy;
        }
        if (BoyPy > 12) {
            BoyDir = 0;
            goto animate_boy;
        }
        if (BoyPx > 3) {
            BoyDir = 3;
            goto animate_boy;
        }
        BoyHere = 5;
        BoyIsMowing = 0;
        LastMowX = BoyPx;
        LastMowY = BoyPy;
        goto animate_boy;

    case 5:
        if (BoyPy < 5) {
            BoyDir = 2;
            goto animate_boy;
        }
        if (BoyPy > 5) {
            BoyDir = 0;
            goto animate_boy;
        }
        if (BoyPx > 3) {
            BoyDir = 3;
            goto animate_boy;
        }
        BoyHere = 1;
        goto animate_boy;
    }

animate_boy:
    BoyHere = 1;
    BoyFrame = kidDirectionFrame[BoyDir] + kidCycleFrame[YardCycle & 3];
    if (BoyIsMowing != 0) {
        BoyFrame += 100;
        BoyX += BxTab[BoyDir];
        BoyY += ByTab[BoyDir];
    } else if (BoyStandCnt != 0) {
        --BoyStandCnt;
        BoyFrame = BoyDir + 20;
    } else {
        if (SRand32() == 0)
            BoyStandCnt = 20;
        BoyX += BxTab[BoyDir];
        BoyY += ByTab[BoyDir];
    }

    /* Convert the moving sprite's pixel location back to a bounded yard cell. */
    pixelX = (BoyX + BoyY - 200) / 28;
    pixelY = (BoyY - 38) / 10;
    BoyPx = pixelX;
    BoyPy = pixelY;
    if (BoyPy < 0)
        BoyPy = 0;
    if (BoyPy > 15)
        BoyPy = 15;
    if (BoyPx < 0)
        BoyPx = 0;
    if (BoyPx > 11)
        BoyPx = 11;

    /* Reverse away from the yard limits, then update the foot at CurYardPnt. */
    if (BoyIsMowing == 0) {
        if (BoyPy < 1)
            BoyDir = 2;
        else if (BoyPy > 14)
            BoyDir = 0;
        if (BoyPx > 10) {
            BoyDir = 3;
        } else if (BoyPy < 5) {
            if (BoyPx < 4)
                BoyDir = 1;
        } else if (BoyPx < 3) {
            BoyDir = 0;
            if (BoyPy < 6 && BoyHere == 3 && BoyPx < 4)
                BoyDir = 1;
            if (BoyPy < 6 && BoyHere != 3)
                NodeNum = 21;
        }
    }

    FootHere = 0;
    FootTog = (FootTog == 1) ? 0 : 1;
    if (BoyPy == CurYardPnt[1] && BoyPx == CurYardPnt[0]) {
        FootHere = 1;
        pixelY = BoyY - 38;
        FootY = pixelY % 10;
        pixelX = BoyX + BoyY - 200;
        FootX = (((pixelX % 28) << 2) + 6) & 0x7f;
        FootY = ((FootY + 1) * 6) & 0x3f;
        MowX = FootX + kidMowXFrame[BoyDir & 3];
        MowY = FootY + kidMowYFrame[BoyDir & 3];
        if ((BoyDir & 1) != 0) {
            if (FootTog != 0)
                FootY += 6;
            else
                FootY -= 6;
        } else {
            if (FootTog != 0)
                FootX += 6;
            else
                FootX -= 6;
        }
        FootFall(FootX, FootY);

        if (BoyIsMowing != 0 && CurGameType == 0) {
            /* A mowing foot can clear active ants of the selected yard cell. */
            index = ListIndexA;
            while (index > 0) {
                --index;
                if (AlistT[index] != 0 && SRand4() != 0) {
                    LifeA[((AlistM[index] & 0xff) << 6) + AlistT[index]] = 0;
                    AlistT[index] = 0;
                }
            }
            if (SpidOn != 0 && SRand4() != 0)
                KillSpider();
            if (MeMode <= 1 && MePlane == 1 && SRand4() != 0)
                YellowDeath(6);
        }
    } else if (BoyIsMowing != 0) {
    /* If the mowing cell moved away from CurYardPnt, retain the two map bytes
     * and count a colony kill whenever the corresponding cell was occupied. */
        index = (BoyPx << 4) + BoyPy;
        population = YMapPopB[index];
        if (population != 0) {
            population -= population >> 2;
            if (population == 0)
                ++BColoniesKilled;
            YMapPopB[index] = population;
        }
        population = YMapPopR[index];
        if (population != 0) {
            population -= population >> 2;
            if (population == 0)
                ++RColoniesKilled;
            YMapPopR[index] = population;
        }
    }
    }
    return;
}
