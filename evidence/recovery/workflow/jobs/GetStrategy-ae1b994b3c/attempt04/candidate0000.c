/* Select the blue colony's strategy from health and population state. */
extern int near MePlane;
extern int near MeLocX;
extern int near MeLocY;
extern int near HealthB;
extern int near BpopT;
extern int near RpopT;
extern int far ChaseSpid;
extern int far FuzLocX;
extern int far FuzLocY;
extern int far SpidOn;
extern int far RedQueens;
extern int far TilesDugB;
extern int far StrategicModeB;
extern int far StrategicModeR;
extern int far SRand1(int range);
extern int near SpidX;
extern int near SpidY;
extern unsigned long far GetDis(int x1, int y1, int x2, int y2);
extern int near GstrR(void);
extern void near SetCasteProd(void);
extern void near SetModeProd(void);

void far GetStrategy(void)
{
    int distance;
    int bluePop;
    int halfPop;
    int redPop;

    ChaseSpid = 0;
    if (MePlane == 1) {
        FuzLocX = SRand1(5) + MeLocX - 2;
        FuzLocY = SRand1(5) + MeLocY - 2;
        if (FuzLocX < 0)
            FuzLocX = 0;
        if (FuzLocX > 127)
            FuzLocX = 127;
        if (FuzLocY < 0)
            FuzLocY = 0;
        if (FuzLocY > 63)
            FuzLocY = 63;
        if (SpidOn) {
            distance = (int)GetDis(SpidX >> 4, SpidY >> 4, MeLocX, MeLocY);
            if (distance < 100)
                ChaseSpid = 1;
        }
    }

    FuzLocX = MeLocX;
    if (HealthB < 10) {
        redPop = RpopT;
        halfPop = BpopT >> 1;
        if (halfPop <= redPop)
            goto chooseMode;
        if (redPop <= 0)
            goto chooseMode;
        if (RedQueens <= 0)
            goto chooseMode;
        StrategicModeB = 0;
        goto strategyReady;
    }
    goto chooseMode;

chooseMode:
    if (HealthB < 30) {
        StrategicModeB = 5;
    } else if (HealthB < 50) {
        StrategicModeB = 4;
    } else {
        bluePop = BpopT;
        if (TilesDugB < bluePop) {
            StrategicModeB = 3;
        } else if (TilesDugB < bluePop * 2) {
            StrategicModeB = 2;
        } else if (bluePop <= 100) {
            redPop = RpopT;
            if (redPop > 0 && RedQueens > 0 && bluePop / 3 > redPop)
                StrategicModeB = 0;
            else
                StrategicModeB = 1;
        } else {
            StrategicModeB = 1;
        }
    }
strategyReady:
    StrategicModeR = GstrR();
    SetCasteProd();
    SetModeProd();
}
