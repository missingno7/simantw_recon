/*
 * _CheatKeys hypothesis: dispatch the decoded letter index through the dense
 * 0..25 switch. The handlers update colony stores and health, place eggs,
 * adjust the population maps, or invoke the network setup paths. The entry
 * diagnostic text and the two undocumented flag words remain hypotheses.
 */

extern void far WinPrintf(char far *format, ...);
extern void far myBeginSound(unsigned int first, unsigned int second,
                             unsigned int third);
extern void far SetMyHealth(int health);
extern void far PictStrnDialog(int picture, int object, int force);
extern void far UpdateEverything(void);
extern void far SetSimCursor(int cursor);
extern void far myBeginSoundList(int list);
extern void far MakeNewHoleB(int index);
extern void far MakeNewHoleR(int index);
extern void far MakeBlkQueen(int x, int y, int direction);
extern void far MakeRedQueen(int x, int y, int direction);
extern int far RRand(int limit);
extern int far SRand8(void);
extern void far PlaceEggB(int x, int y, int direction);
extern void far PlaceEggR(int x, int y, int direction);
extern void far InvalQueenStorageDisp(void);
extern int far SRand2(void);
extern void far DrawSimPayoff(void);
extern int near GtRegisterClass(int instance);
extern int near GtInitiateDDE(int window, int instance);
extern int near NbCheck(void);
extern int near NbAddName(char far *name);
extern int near NbPostListen();
extern int near StopSimulation(void);
extern unsigned int far mem_Alloc(unsigned long bytes, int kind,
                                  char far *name);
extern void far *mem_Lock(unsigned int handle);
extern int far pascal MessageBox(int window, char far *text,
                                 char far *caption, unsigned int style);

extern int near HealthB;
extern int near HealthR;
extern int near MeHealth;
extern int near QueenStorageB;
extern int near QueenStorageR;
extern int near MeLocX;
extern int near MeLocY;
extern char far Dx8[];
extern char far Dy8[];
extern int far AlwaysHealthy;
extern unsigned char far YMapPopB[];
extern unsigned char far YMapPopR[];
extern int far BColoniesStarted;
extern int far RColoniesStarted;
extern int near hInst;
extern int near rootWnd;
extern int far SimAntDataFlag;
extern int far SimAntServerFlag;
extern unsigned char far SimAntServerNum;
extern int far SimAntClientFlag;
extern unsigned char far SimAntClientNum;
extern int far ncbTail;
extern int far ncbHead;
extern void far * near theNetBiosBuffer;

static int near ddeStarted = 0;
static unsigned int near ncbHandle = 0;
static int __based(__segname("SIMANT_DATA_GROUP")) cheatToggleA = 0;
static int __based(__segname("SIMANT_DATA_GROUP")) cheatToggleB = 0;
static int __based(__segname("SIMANT_DATA_GROUP")) cheatToggleC = 0;

void far CheatKeys(int key)
{
    register int i;
    register int j;
    unsigned int far *handleSlot;

    WinPrintf("CHEAT %d", key);

    switch (key) {
    case 0:
        myBeginSound(10, 0, 0x7e);
        QueenStorageR += 10;
        break;

    case 1:
        myBeginSound(1, 0, 0x7e);
        SetMyHealth(100);
        break;

    case 2:
        myBeginSound(1, 0, 0x7e);
        SetMyHealth(1);
        break;

    case 3:
        PictStrnDialog(0, 0x2724, 0);
        break;

    case 4:
        PictStrnDialog(0, 0x2726, 0);
        UpdateEverything();
        SetSimCursor(6);
        myBeginSoundList(0);
        SetSimCursor(0);
        PictStrnDialog(0, 0x2728, 0);
        break;

    case 5:
        for (i = 0; i < 0x40; ++i)
            MakeNewHoleB(i);
        break;

    case 6:
        for (i = 0; i < 0x40; ++i)
            MakeNewHoleR(i);
        break;

    case 7:
        MakeBlkQueen(MeLocX + 2, MeLocY, 2);
        break;

    case 8:
        MakeRedQueen(MeLocX + 2, MeLocY, 2);
        break;

    case 9:
        for (i = 16; i != 0; --i) {
            PlaceEggB(MeLocX + Dx8[SRand8()],
                      MeLocY + Dy8[SRand8()], RRand(6) + 1);
        }
        break;

    case 10:
        for (i = 16; i != 0; --i) {
            PlaceEggR(MeLocX + Dx8[SRand8()],
                      MeLocY + Dy8[SRand8()], RRand(6) + 0x81);
        }
        break;

    case 11:
        HealthB = 100;
        break;

    case 12:
        HealthR = 100;
        break;

    case 13:
        HealthR = 0;
        break;

    case 14:
        AlwaysHealthy = 0;
        HealthB = 0;
        break;

    case 15:
        QueenStorageB += 10;
        InvalQueenStorageDisp();
        myBeginSound(0x29, 0, 0x7e);
        break;

    case 16:
        if (cheatToggleA == 1)
            cheatToggleA = 0;
        else
            cheatToggleA = 1;
        if (cheatToggleA)
            myBeginSound(2, 0, 0x7e);
        else
            myBeginSound(1, 0, 0x7e);
        break;

    case 17:
        if (cheatToggleB == 1)
            cheatToggleB = 0;
        else
            cheatToggleB = 1;
        if (cheatToggleB)
            myBeginSound(2, 0, 0x7e);
        else
            myBeginSound(1, 0, 0x7e);
        break;

    case 18:
        myBeginSound(2, 0, 0x7e);
        BColoniesStarted += 0x10;
        for (i = 0; i < 0xc0; i += 0x10)
            for (j = 0; j < 0x10; ++j)
                YMapPopB[i + j] += 4;
        break;

    case 19:
        myBeginSound(1, 0, 0x7e);
        for (i = 0; i < 0xc0; i += 0x10) {
            for (j = 0; j < 0x10; ++j) {
                if (SRand2() == 0) {
                    ++YMapPopB[i + j];
                    ++BColoniesStarted;
                } else {
                    ++YMapPopR[i + j];
                    ++RColoniesStarted;
                }
            }
        }
        break;

    case 20:
        DrawSimPayoff();
        break;

    case 21:
        if (cheatToggleC == 1)
            cheatToggleC = 0;
        else {
            cheatToggleC = 1;
            HealthB = 100;
        }
        if (cheatToggleC)
            myBeginSound(2, 0, 0x7e);
        else
            myBeginSound(1, 0, 0x7e);
        break;

    case 22:
        if (AlwaysHealthy == 1) {
            AlwaysHealthy = 0;
        } else {
            AlwaysHealthy = 1;
            HealthB = 100;
        }
        break;

    case 23:
        if (!ddeStarted) {
            GtRegisterClass(hInst);
            ddeStarted = 1;
        }
        if (GtInitiateDDE(rootWnd, hInst)) {
            SimAntDataFlag = 1;
            return;
        }
        MessageBox(rootWnd, "Unable to access database.",
                   "SimAnt For Windows", 0x30);
        break;

    case 24:
        if (NbCheck()) {
            SimAntServerFlag = 1;
            SimAntServerNum = (unsigned char)NbAddName("SERVANT");
        } else {
            MessageBox(rootWnd, "Unable to access network.",
                       "SimAnt For Windows", 0x30);
        }
        break;

    case 25:
        if (!NbCheck()) {
            MessageBox(rootWnd, "Unable to access network.",
                       "SimAnt For Windows", 0x30);
            break;
        }
        SimAntClientFlag = 1;
        ncbTail = 0;
        ncbHead = 0;
        handleSlot = &ncbHandle;
        if (*handleSlot == 0) {
            *handleSlot = mem_Alloc(0x2000L, 0, "Net Bios Buffer");
            theNetBiosBuffer = mem_Lock(*handleSlot);
        }
        SimAntClientNum = (unsigned char)NbAddName("CLIEANT");
        NbPostListen("CLIEANT", "SERVANT", 0x3c, 0, "", StopSimulation);
        break;
    }
}
