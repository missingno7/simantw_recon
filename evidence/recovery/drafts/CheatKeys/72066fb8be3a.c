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

extern int near HealthB;
extern int near HealthR;
extern int near MeHealth;
extern int near QueenStorageB;
extern int near QueenStorageR;
extern int near MeLocX;
extern int near MeLocY;
extern unsigned char far Dx8[];
extern unsigned char far Dy8[];
extern int far AlwaysHealthy;
extern unsigned char far YMapPopB[];
extern unsigned char far YMapPopR[];
extern int far BColoniesStarted;
extern int far RColoniesStarted;

void far CheatKeys(int key)
{
    int i;
    int j;
    int direction;
    int x;
    int y;

    WinPrintf("Cheat key %d", key);

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
        for (i = 0; i != 0x40; ++i)
            MakeNewHoleB(i);
        break;

    case 6:
        for (i = 0; i != 0x40; ++i)
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
            direction = RRand(6) + 1;
            y = MeLocY + Dy8[SRand8()];
            x = MeLocX + Dx8[SRand8()];
            PlaceEggB(x, y, direction);
        }
        break;

    case 10:
        for (i = 16; i != 0; --i) {
            direction = RRand(6) + 0x81;
            y = MeLocY + Dy8[SRand8()];
            x = MeLocX + Dx8[SRand8()];
            PlaceEggR(x, y, direction);
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
    case 17:
        /* These two toggles still need their exact MAPSYM state identity. */
        break;

    case 18:
        myBeginSound(2, 0, 0x7e);
        BColoniesStarted += 0x10;
        for (i = 0; i != 0xc0; i += 0x10)
            for (j = 0; j != 0x10; ++j)
                YMapPopB[i + j] += 4;
        break;

    case 19:
        myBeginSound(1, 0, 0x7e);
        for (i = 0; i != 0xc0; i += 0x10) {
            for (j = 0; j != 0x10; ++j) {
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
        /* The segment-8 flag at +0x5e has no named MAPSYM public. */
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
    case 24:
    case 25:
        /* Network/DDE cases require the private buffers and strings. */
        break;
    }
}
