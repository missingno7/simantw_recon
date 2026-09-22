/*
 * DoNestAntB: per-tick AI dispatcher for one B-colony ant, called once per
 * pending Dx8 list record by DoAntSimB(x, y, attr).  attr is the ant's own
 * attribute/type byte (BlistT): bit 0x80 selects one of two independent
 * halves of this dispatcher (colony colour), bits 0x78 (>>3) give a
 * "mode0" nibble passed on to several per-mode workers.
 *
 * Low half (attr&0x80==0): the current ant's own BlistM mode is read, a
 * per-mode population counter (TemBModePop) is bumped, and unless
 * mode==9 a random death check (SRand256()==0 && SRand32()>HealthB) can
 * clear the ant (BlistT=0, LifeB cell=0, BAntsExpired++) and return.
 * Otherwise mode (0..17) dispatches to one of the per-mode B-colony
 * workers (DoNestingB, DoFoodInB, DoDigInB, DoDigOutB, SimEggB,
 * SimQueenB, DoNestFightB) or to inline attack/movement logic matching
 * CheckNestFightB/DoRestB's bodies, reused inline rather than by call
 * (matching this codebase's copy-paste style between similar
 * dispatchers).
 *
 * High half (attr&0x80!=0): bumps TemRModePop, and either resolves via
 * an inline DoNestFightB(x,y) call (attr>0xef) or otherwise inspects the
 * ant sitting on the destination cell: a yellow ant there is fought via
 * YellowFight; a B-list ant in 1..0x67 either has its old coordinate
 * cleared (and, below 8, is treated as eaten/expired) or is fought via
 * GetWinner; otherwise mode==7 raids in (RaidInB) while any other mode
 * tries GetExitDirB/TryMoveDirB movement before giving up.
 */
extern unsigned char near LifeB[];
extern unsigned char near MapB[];
extern int near MeColor;
extern int near MePlane;
extern int near HealthB;
extern int far Tindex;
extern unsigned char far Dx8[];
extern int far TemBModePop[];
extern int far TemRModePop[];
extern long far BAntsExpired;
extern long far RAntsExpired;
extern long far TotalEggsDiedB;
extern int far FlyAwayB;
extern int far BalloonModeFlag;

extern int far SRand256(void);
extern int far SRand32(void);
extern int far SRand8(void);
extern int far SRand1(int range);
extern int far IsYellowAnt(int ant);
extern void far YellowFight(int kind, int index);
extern int far FindInBList(int x, int y, int ant);
extern int near GetWinner(int defender, int attacker);
extern int far GetNewMode(int mode, int fullValue);
extern int far GetNewModeB(int mode);
extern int far GetExitDirB(int x, int y, int limit);
extern int far TryMoveDirB(int x, int y, int dir);
extern void far RestBalloons(int x, int y, int plane);

extern void far DoNestingB(int x, int y, int attr, int mode0);
extern void far DoFoodInB(int x, int y, int attr);
extern void far DoDigInB(int x, int y, int attr, int mode0);
extern void far DoDigOutB(int x, int y, int attr);
extern void far SimEggB(int x, int y);
extern void far SimQueenB(int x, int y, int mode0, int attr);
extern void far DoNestFightB(int x, int y);
extern void far RaidInB(int x, int y, int attr);

#define BlistM(i) Dx8[(i) + 0x3b22]
#define BlistT(i) Dx8[(i) + 0x3d18]
#define BlistS(i) Dx8[(i) + 0x3f0e]
#define BlistX(i) Dx8[(i) + 0x3736]
#define BlistY(i) Dx8[(i) + 0x392c]

void far DoNestAntB(int x, int y, int attr)
{
    int mode0;

    mode0 = (attr & 0x78) >> 3;
    if (attr & 0x80)
        goto HighHalf;

    /* ---- low half (own colony) ---- */
    {
        int far *tindexPtr = &Tindex;
        int mode = BlistM(*tindexPtr);
        TemBModePop[mode]++;

        if (SRand256() == 0 && mode != 9 && SRand32() > HealthB) {
            BlistT(*tindexPtr) = 0;
            LifeB[(x << 6) + y] = 0;
            BAntsExpired++;
            return;
        }

        switch (mode) {
        case 0:
        default:
            {
                int cellIndex;
                int ant;

                if (!SRand32())
                    BlistM(*tindexPtr) = GetNewModeB(mode0);
                cellIndex = (x << 6) + y;
                ant = LifeB[cellIndex];
                if (IsYellowAnt(ant) == 1 && MeColor != 0) {
                    YellowFight(2, *tindexPtr);
                    return;
                }
                if (ant > 0x87 && ant < 0xe8) {
                    int index = FindInBList(x, y, ant);
                    if (index >= 0) {
                        int winner = GetWinner(ant, attr);
                        BlistS(index) = winner;
                        BlistT(index) = (winner & 0x80) + 0x70;
                        LifeB[cellIndex] = (winner & 0x80) + 0x70;
                        BlistM(index) = 0xa;
                        return;
                    }
                }
                if (TryMoveDirB(x, y, attr & 7))
                    return;
                TryMoveDirB(x, y, SRand8());
                return;
            }

        case 1:
            DoNestingB(x, y, attr, mode0);
            return;

        case 3:
            DoFoodInB(x, y, attr);
            return;

        case 4:
            DoDigInB(x, y, attr, mode0);
            return;

        case 6:
            if (MePlane == 2) {
                int cellIndex = (x << 6) + y;
                int ant = LifeB[cellIndex];
                if (IsYellowAnt(ant) == 1 && MeColor != 0) {
                    YellowFight(2, *tindexPtr);
                    return;
                }
                if (ant > 0x87 && ant < 0xe8) {
                    int index = FindInBList(x, y, ant);
                    if (index >= 0) {
                        int winner = GetWinner(ant, attr);
                        BlistS(index) = winner;
                        BlistT(index) = (winner & 0x80) + 0x70;
                        LifeB[cellIndex] = (winner & 0x80) + 0x70;
                        BlistM(index) = 0xa;
                        return;
                    }
                }
                if (TryMoveDirB(x, y, attr & 7))
                    return;
                TryMoveDirB(x, y, SRand8());
                return;
            }
            /* fall through */
        case 2:
        case 5:
        case 7:
        case 11:
        case 12:
        case 15:
        case 16:
            DoDigOutB(x, y, attr);
            return;

        case 8:
            SimEggB(x, y);
            return;

        case 9:
            SimQueenB(x, y, mode0, attr);
            return;

        case 10:
            DoNestFightB(x, y);
            return;

        case 13:
            {
                int cellIndex = (x << 6) + y;
                int ant = LifeB[cellIndex];
                if (IsYellowAnt(ant) == 1 && MeColor != 0) {
                    YellowFight(2, *tindexPtr);
                    return;
                }
                if (ant > 0x87 && ant < 0xe8) {
                    int index = FindInBList(x, y, ant);
                    if (index >= 0) {
                        int winner = GetWinner(ant, attr);
                        BlistS(index) = winner;
                        BlistT(index) = (winner & 0x80) + 0x70;
                        LifeB[cellIndex] = (winner & 0x80) + 0x70;
                        BlistM(index) = 0xa;
                        return;
                    }
                }
                LifeB[cellIndex] = BlistT(*tindexPtr);
                if (SRand1(20) == 0) {
                    BlistM(*tindexPtr) = GetNewMode((BlistT(*tindexPtr) & 0x78) >> 3, BlistT(*tindexPtr));
                    return;
                }
                if (BalloonModeFlag == 1)
                    RestBalloons(x, y, 2);
                return;
            }

        case 14:
            {
                int cellIndex = (x << 6) + y;
                int ant;
                if (!SRand32())
                    BlistM(*tindexPtr) = GetNewModeB(mode0);
                ant = LifeB[cellIndex];
                if (IsYellowAnt(ant) == 1 && MeColor != 0) {
                    YellowFight(2, *tindexPtr);
                    goto FlyAwayTail;
                }
                if (ant > 0x87 && ant < 0xe8) {
                    int index = FindInBList(x, y, ant);
                    if (index >= 0) {
                        int winner = GetWinner(ant, attr);
                        BlistS(index) = winner;
                        BlistT(index) = (winner & 0x80) + 0x70;
                        LifeB[cellIndex] = (winner & 0x80) + 0x70;
                        BlistM(index) = 0xa;
                        goto FlyAwayTail;
                    }
                }
                if (!TryMoveDirB(x, y, attr & 7))
                    TryMoveDirB(x, y, SRand8());
            FlyAwayTail:
                if (FlyAwayB > 100)
                    BlistM(*tindexPtr) = 0xf;
                return;
            }

        case 17:
            {
                int cellIndex = (x << 6) + y;
                int dir;
                if (MapB[cellIndex] < 0x14) {
                    BlistM(*tindexPtr) = GetNewModeB(mode0);
                    return;
                }
                dir = (SRand1(3) + attr - 1) & 7;
                dir |= attr & 0xf8;
                BlistT(*tindexPtr) = dir;
                LifeB[cellIndex] = dir;
                if (SRand1(100) == 0) {
                    LifeB[cellIndex] = 0;
                    BlistT(*tindexPtr) = 0;
                    if ((dir & 0x80) == 0)
                        BAntsExpired++;
                    else
                        RAntsExpired++;
                }
                return;
            }
        }
    }

    /* ---- high half (opposing colony) ---- */
HighHalf:
    {
        int far *tindexPtr = &Tindex;
        int mode = BlistM(*tindexPtr);
        int cellIndex;
        int ant;

        TemRModePop[mode]++;

        if (attr > 0xef) {
            DoNestFightB(x, y);
            return;
        }

        cellIndex = (x << 6) + y;
        ant = LifeB[cellIndex];
        if (IsYellowAnt(ant) == 1 && MeColor != 0) {
            YellowFight(2, *tindexPtr);
            return;
        }

        if (ant > 0 && ant < 0x68) {
            int index = FindInBList(x, y, ant);
            if (index >= 0) {
                if (ant <= 0x5f) {
                    BlistT(index) = 0;
                    LifeB[(BlistX(index) << 6) + BlistY(index)] = 0;
                    if (ant < 8) {
                        BlistM(*tindexPtr) = 3;
                        BlistT(*tindexPtr) |= 8;
                        LifeB[cellIndex] = BlistT(*tindexPtr);
                        BlistT(index) = 0;
                        TotalEggsDiedB++;
                        return;
                    }
                }
                {
                    int winner = GetWinner(BlistT(index), attr);
                    BlistT(*tindexPtr) = 0;
                    BlistS(index) = winner;
                    BlistT(index) = (winner & 0x80) + 0x70;
                    LifeB[cellIndex] = (winner & 0x80) + 0x70;
                    BlistM(index) = 0xa;
                    return;
                }
            }
        }

        if (mode == 7) {
            RaidInB(x, y, attr);
            return;
        }

        {
            int dir = GetExitDirB(x, y, 8);
            if (dir < 0)
                dir = SRand8();
            if (TryMoveDirB(x, y, dir - 1))
                return;
            if (TryMoveDirB(x, y, SRand8()))
                return;
            LifeB[cellIndex] = BlistT(*tindexPtr);
        }
    }
}
