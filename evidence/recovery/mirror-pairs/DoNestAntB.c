/* Derived mechanically from the mirrored colony function _DoNestAntR (tools/mirror_pairs.py):
 * colony-specific MAPSYM identifiers swapped DoAntSimR->DoAntSimB, DoDigInR->DoDigInB, DoDigOutR->DoDigOutB, DoFoodInR->DoFoodInB, DoNestAntR->DoNestAntB, DoNestFightR->DoNestFightB, DoNestingR->DoNestingB, DoRandR->DoRandB, FindInRList->FindInBList, FlyAwayR->FlyAwayB, GetExitDirR->GetExitDirB, GetNewModeR->GetNewModeB, HealthR->HealthB, LifeR->LifeB, MapR->MapB, RAntsExpired->BAntsExpired, RaidInR->RaidInB, RaidOutR->RaidOutB, RlistM->Blis; constants and structure unchanged.
 * Verified only by the strict matcher; where the pair is not a pure mirror the
 * diagnostic names the asymmetry. */
/*
 * DoNestAntR: per-tick AI dispatcher for one R-colony ant, called once per
 * pending Dx8 list record by DoAntSimR(x, y, attr).  attr is the ant's own
 * attribute/type byte (RlistT): bit 0x80 selects one of two independent
 * halves of this dispatcher (colony colour), bits 0x78 (>>3) give a
 * "mode0" nibble passed on to several per-mode workers.  This is the R
 * twin of DoNestAntB; despite sharing the overall dispatch shape it is
 * not a pure constant swap: the own-colony default/mode14 bodies check
 * their own-list range before the yellow-ant test (opposite order from
 * B), YellowFight is always called with kind 3 and gated on MeColor==0
 * (opposite polarity from B's MeColor!=0), the opposing-colony high half
 * has its own attr<8/attr>0x6f thresholds and its own mode6 (StayInR,
 * MePlane==3) / mode7 (RaidInR) special cases, and GetExitDirR signals
 * "no exit" with 0 rather than a negative value.
 *
 * Low half (attr&0x80==0): the current ant's own RlistM mode is read, a
 * per-mode population counter (TemRModePop) is bumped, and unless
 * mode==9 a random death check (SRand256()==0 && SRand32()>HealthR) can
 * clear the ant (RlistT=0, LifeR cell=0, RAntsExpired++) and return.
 * Otherwise mode (0..17) dispatches to one of the per-mode R-colony
 * workers (DoNestingR, DoFoodInR, DoDigInR, DoDigOutR, SimEggR,
 * SimQueenR, DoNestFightR) or to inline attack/movement logic matching
 * the DoRandR/RaidOutR sibling bodies, reused inline rather than by
 * call (matching this codebase's copy-paste style between similar
 * dispatchers).
 *
 * High half (attr&0x80!=0): bumps TemBModePop, and either clears the
 * current record directly when attr<8 (an eaten/expired egg), or
 * resolves via DoNestFightR-style combat when attr>0x6f, or otherwise
 * inspects the ant sitting on the destination cell: an opposing B-list
 * ant in 0x81..0xe7 is looked up, an old position above 0xdf is
 * cleared, one below 0x88 is treated as eaten/expired, otherwise
 * GetWinner decides the fight; failing that, mode==6 with MePlane==3
 * calls StayInR, mode==7 raids in (RaidInR), and any other mode tries
 * GetExitDirR/TryMoveDirR movement before giving up.
 */
extern unsigned char near LifeB[];
extern unsigned char near MapB[];
extern int near MeColor;
extern int near MePlane;
extern int near HealthB;
extern int far Tindex;
extern unsigned char far Dx8[];
extern int far TemBModePop[];
extern int far TemBModePop[];
extern long far BAntsExpired;
extern long far BAntsExpired;
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
extern void far StayInR(int x, int y, int attr);

#define BlistM(i) Dx8[(i) + 0x44f0]
#define BlistT(i) Dx8[(i) + 0x46e6]
#define BlistS(i) Dx8[(i) + 0x48dc]
#define BlistX(i) Dx8[(i) + 0x4104]
#define BlistY(i) Dx8[(i) + 0x42fa]

void far DoNestAntB(int x, int y, int attr)
{
    int mode0;
    int mode;
    int ant;
    int cellIndex;
    int index;
    int winner;
    int dir;

    mode0 = (attr & 0x78) >> 3;

    if (attr & 0x80) {
        /* ---- low half (own colony) ---- */
            mode = BlistM(Tindex);
            TemBModePop[mode]++;

            if (SRand256() == 0 && mode != 9 && SRand32() > HealthB) {
                BlistT(Tindex) = 0;
                LifeB[(x << 6) + y] = 0;
                BAntsExpired++;
                return;
            }

            switch (mode) {
            case 0:
            default:
                if (!SRand32())
                    BlistM(Tindex) = GetNewModeB(mode0);
                cellIndex = (x << 6) + y;
                ant = LifeB[cellIndex];
                if (ant > 7 && ant < 0x68) {
                    index = FindInBList(x, y, ant);
                    if (index >= 0) {
                        winner = GetWinner(ant, attr);
                        BlistS(index) = winner;
                        BlistT(index) = (winner & 0x80) + 0x70;
                        LifeB[cellIndex] = (winner & 0x80) + 0x70;
                        BlistM(index) = 0xa;
                        return;
                    }
                } else if (IsYellowAnt(ant) != 0 && MeColor == 0) {
                    YellowFight(3, Tindex);
                    return;
                }
                if (TryMoveDirB(x, y, attr & 7))
                    return;
                TryMoveDirB(x, y, SRand8());
                return;

            case 1:
                DoNestingB(x, y, attr, mode0);
                return;

            case 3:
                DoFoodInB(x, y, attr);
                return;

            case 4:
                DoDigInB(x, y, attr, mode0);
                return;

            case 2:
            case 5:
            case 6:
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
                cellIndex = (x << 6) + y;
                ant = LifeB[cellIndex];
                if (ant > 7 && ant < 0x68) {
                    index = FindInBList(x, y, ant);
                    if (index >= 0) {
                        winner = GetWinner(ant, attr);
                        BlistS(index) = winner;
                        BlistT(index) = (winner & 0x80) + 0x70;
                        LifeB[cellIndex] = (winner & 0x80) + 0x70;
                        BlistM(index) = 0xa;
                        return;
                    }
                } else if (IsYellowAnt(ant) != 0 && MeColor == 0) {
                    YellowFight(3, Tindex);
                    return;
                }
                LifeB[cellIndex] = BlistT(Tindex);
                if (SRand1(20) == 0) {
                    BlistM(Tindex) = GetNewMode((BlistT(Tindex) & 0x78) >> 3, BlistT(Tindex));
                    return;
                }
                if (BalloonModeFlag == 0)
                    RestBalloons(x, y, 3);
                return;

            case 14:
                if (!SRand32())
                    BlistM(Tindex) = GetNewModeB(mode0);
                cellIndex = (x << 6) + y;
                ant = LifeB[cellIndex];
                if (ant > 7 && ant < 0x68) {
                    index = FindInBList(x, y, ant);
                    if (index >= 0) {
                        winner = GetWinner(ant, attr);
                        BlistS(index) = winner;
                        BlistT(index) = (winner & 0x80) + 0x70;
                        LifeB[cellIndex] = (winner & 0x80) + 0x70;
                        BlistM(index) = 0xa;
                        goto FlyAwayTail;
                    }
                } else if (IsYellowAnt(ant) != 0 && MeColor == 0) {
                    YellowFight(3, Tindex);
                    goto FlyAwayTail;
                }
                if (!TryMoveDirB(x, y, attr & 7))
                    TryMoveDirB(x, y, SRand8());
            FlyAwayTail:
                if (FlyAwayB > 100)
                    BlistM(Tindex) = 0xf;
                return;

            case 17:
                cellIndex = (x << 6) + y;
                if (MapB[cellIndex] < 0x14) {
                    BlistM(Tindex) = GetNewModeB(mode0);
                    return;
                }
                dir = (SRand1(3) + attr - 1) & 7;
                dir |= attr & 0xf8;
                BlistT(Tindex) = dir;
                LifeB[cellIndex] = dir;
                if (SRand1(100) == 0) {
                    LifeB[cellIndex] = 0;
                    BlistT(Tindex) = 0;
                    if ((dir & 0x80) == 0)
                        BAntsExpired++;
                    else
                        BAntsExpired++;
                }
                return;
            }

    }

    /* ---- high half (opposing colony) ---- */
    mode = BlistM(Tindex);
    TemBModePop[mode]++;

    if (attr < 8) {
        BlistT(Tindex) = 0;
        LifeB[(BlistX(Tindex) << 6) + BlistY(Tindex)] = 0;
        return;
    }

    if (attr > 0x6f) {
        DoNestFightB(x, y);
        return;
    }

    cellIndex = (x << 6) + y;
    ant = LifeB[cellIndex];

    if (ant > 0x80 && ant < 0xe8) {
        index = FindInBList(x, y, ant);
        if (index >= 0) {
            if (ant > 0xdf) {
                BlistT(index) = 0;
                LifeB[(BlistX(index) << 6) + BlistY(index)] = 0;
            }
            if (ant < 0x88) {
                BlistM(Tindex) = 3;
                BlistT(Tindex) |= 8;
                LifeB[cellIndex] = BlistT(Tindex);
                BlistT(index) = 0;
                return;
            }
            winner = GetWinner(BlistT(index), attr);
            BlistT(Tindex) = 0;
            BlistS(index) = winner;
            BlistT(index) = (winner & 0x80) + 0x70;
            LifeB[cellIndex] = (winner & 0x80) + 0x70;
            BlistM(index) = 0xa;
            return;
        }
    }

    if (mode == 6) {
        if (MePlane == 3) {
            StayInR(x, y, attr);
            return;
        }
    } else if (mode == 7) {
        RaidInB(x, y, attr);
        return;
    }

    dir = GetExitDirB(x, y, 8);
    if (dir == 0)
        dir = SRand8();
    else
        dir--;
    if (TryMoveDirB(x, y, dir))
        return;
    if (TryMoveDirB(x, y, SRand8()))
        return;
    LifeB[cellIndex] = BlistT(Tindex);

    return;
}
