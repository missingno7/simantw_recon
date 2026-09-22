/* Derived mechanically from the mirrored colony function _DoNestAntB (tools/mirror_pairs.py):
 * colony-specific MAPSYM identifiers swapped BAntsExpired->RAntsExpired, BlistM->RlistM, BlistS->RlistS, BlistT->RlistT, BlistX->RlistX, BlistY->RlistY, CheckNestFightB->CheckNestFightR, DoAntSimB->DoAntSimR, DoDigInB->DoDigInR, DoDigOutB->DoDigOutR, DoFoodInB->DoFoodInR, DoNestAntB->DoNestAntR, DoNestFightB->DoNestFightR, DoNestingB->DoNestingR, DoRestB->DoRestR, FindInBList->FindInRList, FlyAwayB->FlyAwayR, GetExitDirB->GetExitDirR, GetNew; constants and structure unchanged.
 * Verified only by the strict matcher; where the pair is not a pure mirror the
 * diagnostic names the asymmetry. */
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
extern unsigned char near LifeR[];
extern unsigned char near MapR[];
extern int near MeColor;
extern int near MePlane;
extern int near HealthR;
extern int far Tindex;
extern unsigned char far Dx8[];
extern int far TemRModePop[];
extern int far TemRModePop[];
extern long far RAntsExpired;
extern long far RAntsExpired;
extern long far TotalEggsDiedB;
extern int far FlyAwayR;
extern int far BalloonModeFlag;

extern int far SRand256(void);
extern int far SRand32(void);
extern int far SRand8(void);
extern int far SRand1(int range);
extern int far IsYellowAnt(int ant);
extern void far YellowFight(int kind, int index);
extern int far FindInRList(int x, int y, int ant);
extern int near GetWinner(int defender, int attacker);
extern int far GetNewMode(int mode, int fullValue);
extern int far GetNewModeR(int mode);
extern int far GetExitDirR(int x, int y, int limit);
extern int far TryMoveDirR(int x, int y, int dir);
extern void far RestBalloons(int x, int y, int plane);

extern void far DoNestingR(int x, int y, int attr, int mode0);
extern void far DoFoodInR(int x, int y, int attr);
extern void far DoDigInR(int x, int y, int attr, int mode0);
extern void far DoDigOutR(int x, int y, int attr);
extern void far SimEggR(int x, int y);
extern void far SimQueenR(int x, int y, int mode0, int attr);
extern void far DoNestFightR(int x, int y);
extern void far RaidInR(int x, int y, int attr);

#define RlistM(i) Dx8[(i) + 0x3b22]
#define RlistT(i) Dx8[(i) + 0x3d18]
#define RlistS(i) Dx8[(i) + 0x3f0e]
#define RlistX(i) Dx8[(i) + 0x3736]
#define RlistY(i) Dx8[(i) + 0x392c]

void far DoNestAntR(int x, int y, int attr)
{
    int mode0;
    int far *tindexPtr;
    int mode;
    int ant;
    int cellIndex;
    int index;
    int winner;
    int dir;

    mode0 = (attr & 0x78) >> 3;

    if ((unsigned char)attr & 0x80)
        goto HighHalf;

    /* ---- low half (own colony) ---- */
    tindexPtr = &Tindex;
    mode = RlistM(*tindexPtr);
    TemRModePop[mode]++;

    if (SRand256() == 0 && mode != 9 && SRand32() > HealthR) {
        RlistT(*tindexPtr) = 0;
        LifeR[(x << 6) + y] = 0;
        RAntsExpired++;
        return;
    }

    switch (mode) {
    case 0:
    default:
        if (!SRand32())
            RlistM(*tindexPtr) = GetNewModeR(mode0);
        cellIndex = (x << 6) + y;
        ant = LifeR[cellIndex];
        if (IsYellowAnt(ant) == 1 && MeColor != 0) {
            YellowFight(2, *tindexPtr);
            return;
        }
        if (ant > 0x87 && ant < 0xe8) {
            index = FindInRList(x, y, ant);
            if (index >= 0) {
                winner = GetWinner(ant, attr);
                RlistS(index) = winner;
                RlistT(index) = (winner & 0x80) + 0x70;
                LifeR[cellIndex] = (winner & 0x80) + 0x70;
                RlistM(index) = 0xa;
                return;
            }
        }
        if (TryMoveDirR(x, y, attr & 7))
            return;
        TryMoveDirR(x, y, SRand8());
        return;

    case 1:
        DoNestingR(x, y, attr, mode0);
        return;

    case 3:
        DoFoodInR(x, y, attr);
        return;

    case 4:
        DoDigInR(x, y, attr, mode0);
        return;

    case 6:
        if (MePlane == 2) {
            cellIndex = (x << 6) + y;
            ant = LifeR[cellIndex];
            if (IsYellowAnt(ant) == 1 && MeColor != 0) {
                YellowFight(2, *tindexPtr);
                return;
            }
            if (ant > 0x87 && ant < 0xe8) {
                index = FindInRList(x, y, ant);
                if (index >= 0) {
                    winner = GetWinner(ant, attr);
                    RlistS(index) = winner;
                    RlistT(index) = (winner & 0x80) + 0x70;
                    LifeR[cellIndex] = (winner & 0x80) + 0x70;
                    RlistM(index) = 0xa;
                    return;
                }
            }
            if (TryMoveDirR(x, y, attr & 7))
                return;
            TryMoveDirR(x, y, SRand8());
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
        DoDigOutR(x, y, attr);
        return;

    case 8:
        SimEggR(x, y);
        return;

    case 9:
        SimQueenR(x, y, mode0, attr);
        return;

    case 10:
        DoNestFightR(x, y);
        return;

    case 13:
        cellIndex = (x << 6) + y;
        ant = LifeR[cellIndex];
        if (IsYellowAnt(ant) == 1 && MeColor != 0) {
            YellowFight(2, *tindexPtr);
            return;
        }
        if (ant > 0x87 && ant < 0xe8) {
            index = FindInRList(x, y, ant);
            if (index >= 0) {
                winner = GetWinner(ant, attr);
                RlistS(index) = winner;
                RlistT(index) = (winner & 0x80) + 0x70;
                LifeR[cellIndex] = (winner & 0x80) + 0x70;
                RlistM(index) = 0xa;
                return;
            }
        }
        LifeR[cellIndex] = RlistT(*tindexPtr);
        if (SRand1(20) == 0) {
            RlistM(*tindexPtr) = GetNewMode((RlistT(*tindexPtr) & 0x78) >> 3, RlistT(*tindexPtr));
            return;
        }
        if (BalloonModeFlag == 1)
            RestBalloons(x, y, 2);
        return;

    case 14:
        if (!SRand32())
            RlistM(*tindexPtr) = GetNewModeR(mode0);
        cellIndex = (x << 6) + y;
        ant = LifeR[cellIndex];
        if (IsYellowAnt(ant) == 1 && MeColor != 0) {
            YellowFight(2, *tindexPtr);
            goto FlyAwayTail;
        }
        if (ant > 0x87 && ant < 0xe8) {
            index = FindInRList(x, y, ant);
            if (index >= 0) {
                winner = GetWinner(ant, attr);
                RlistS(index) = winner;
                RlistT(index) = (winner & 0x80) + 0x70;
                LifeR[cellIndex] = (winner & 0x80) + 0x70;
                RlistM(index) = 0xa;
                goto FlyAwayTail;
            }
        }
        if (!TryMoveDirR(x, y, attr & 7))
            TryMoveDirR(x, y, SRand8());
    FlyAwayTail:
        if (FlyAwayR > 100)
            RlistM(*tindexPtr) = 0xf;
        return;

    case 17:
        cellIndex = (x << 6) + y;
        if (MapR[cellIndex] < 0x14) {
            RlistM(*tindexPtr) = GetNewModeR(mode0);
            return;
        }
        dir = (SRand1(3) + attr - 1) & 7;
        dir |= attr & 0xf8;
        RlistT(*tindexPtr) = dir;
        LifeR[cellIndex] = dir;
        if (SRand1(100) == 0) {
            LifeR[cellIndex] = 0;
            RlistT(*tindexPtr) = 0;
            if ((dir & 0x80) == 0)
                RAntsExpired++;
            else
                RAntsExpired++;
        }
        return;
    }

    /* ---- high half (opposing colony) ---- */
HighHalf:
    tindexPtr = &Tindex;
    mode = RlistM(*tindexPtr);
    TemRModePop[mode]++;

    if (attr > 0xef) {
        DoNestFightR(x, y);
        return;
    }

    cellIndex = (x << 6) + y;
    ant = LifeR[cellIndex];
    if (IsYellowAnt(ant) == 1 && MeColor != 0) {
        YellowFight(2, *tindexPtr);
        return;
    }

    if (ant > 0 && ant < 0x68) {
        index = FindInRList(x, y, ant);
        if (index >= 0) {
            if (ant <= 0x5f) {
                RlistT(index) = 0;
                LifeR[(RlistX(index) << 6) + RlistY(index)] = 0;
                if (ant < 8) {
                    RlistM(*tindexPtr) = 3;
                    RlistT(*tindexPtr) |= 8;
                    LifeR[cellIndex] = RlistT(*tindexPtr);
                    RlistT(index) = 0;
                    TotalEggsDiedB++;
                    return;
                }
            }
            winner = GetWinner(RlistT(index), attr);
            RlistT(*tindexPtr) = 0;
            RlistS(index) = winner;
            RlistT(index) = (winner & 0x80) + 0x70;
            LifeR[cellIndex] = (winner & 0x80) + 0x70;
            RlistM(index) = 0xa;
            return;
        }
    }

    if (mode == 7) {
        RaidInR(x, y, attr);
        return;
    }

    dir = GetExitDirR(x, y, 8);
    if (dir < 0)
        dir = SRand8();
    if (TryMoveDirR(x, y, dir - 1))
        return;
    if (TryMoveDirR(x, y, SRand8()))
        return;
    LifeR[cellIndex] = RlistT(*tindexPtr);
}
