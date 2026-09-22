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
extern unsigned char near LifeR[];
extern unsigned char near MapR[];
extern int near MeColor;
extern int near MePlane;
extern int near HealthR;
extern int far Tindex;
extern unsigned char far Dx8[];
extern int far TemBModePop[];
extern int far TemRModePop[];
extern long far BAntsExpired;
extern long far RAntsExpired;
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
extern void far StayInR(int x, int y, int attr);

#define RlistM(i) Dx8[(i) + 0x44f0]
#define RlistT(i) Dx8[(i) + 0x46e6]
#define RlistS(i) Dx8[(i) + 0x48dc]
#define RlistX(i) Dx8[(i) + 0x4104]
#define RlistY(i) Dx8[(i) + 0x42fa]

void far DoNestAntR(int x, int y, int attr)
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
            mode = RlistM(Tindex);
            TemRModePop[mode]++;

            if (SRand256() == 0 && mode != 9 && SRand32() > HealthR) {
                RlistT(Tindex) = 0;
                LifeR[(x << 6) + y] = 0;
                RAntsExpired++;
                return;
            }

            switch (mode) {
            case 0:
            default:
                if (!SRand32())
                    RlistM(Tindex) = GetNewModeR(mode0);
                cellIndex = (x << 6) + y;
                ant = LifeR[cellIndex];
                if (ant > 7 && ant < 0x68) {
                    index = FindInRList(x, y, ant);
                    if (index >= 0) {
                        winner = GetWinner(ant, attr);
                        RlistS(index) = winner;
                        RlistT(index) = (winner & 0x80) + 0x70;
                        LifeR[cellIndex] = (winner & 0x80) + 0x70;
                        RlistM(index) = 0xa;
                        return;
                    }
                } else if (IsYellowAnt(ant) != 0 && MeColor == 0) {
                    YellowFight(3, Tindex);
                    return;
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

            case 2:
            case 5:
            case 6:
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
                if (ant > 7 && ant < 0x68) {
                    index = FindInRList(x, y, ant);
                    if (index >= 0) {
                        winner = GetWinner(ant, attr);
                        RlistS(index) = winner;
                        RlistT(index) = (winner & 0x80) + 0x70;
                        LifeR[cellIndex] = (winner & 0x80) + 0x70;
                        RlistM(index) = 0xa;
                        return;
                    }
                } else if (IsYellowAnt(ant) != 0 && MeColor == 0) {
                    YellowFight(3, Tindex);
                    return;
                }
                LifeR[cellIndex] = RlistT(Tindex);
                if (SRand1(20) == 0) {
                    RlistM(Tindex) = GetNewMode((RlistT(Tindex) & 0x78) >> 3, RlistT(Tindex));
                    return;
                }
                if (BalloonModeFlag == 0)
                    RestBalloons(x, y, 3);
                return;

            case 14:
                if (!SRand32())
                    RlistM(Tindex) = GetNewModeR(mode0);
                cellIndex = (x << 6) + y;
                ant = LifeR[cellIndex];
                if (ant > 7 && ant < 0x68) {
                    index = FindInRList(x, y, ant);
                    if (index >= 0) {
                        winner = GetWinner(ant, attr);
                        RlistS(index) = winner;
                        RlistT(index) = (winner & 0x80) + 0x70;
                        LifeR[cellIndex] = (winner & 0x80) + 0x70;
                        RlistM(index) = 0xa;
                        goto FlyAwayTail;
                    }
                } else if (IsYellowAnt(ant) != 0 && MeColor == 0) {
                    YellowFight(3, Tindex);
                    goto FlyAwayTail;
                }
                if (!TryMoveDirR(x, y, attr & 7))
                    TryMoveDirR(x, y, SRand8());
            FlyAwayTail:
                if (FlyAwayR > 100)
                    RlistM(Tindex) = 0xf;
                return;

            case 17:
                cellIndex = (x << 6) + y;
                if (MapR[cellIndex] < 0x14) {
                    RlistM(Tindex) = GetNewModeR(mode0);
                    return;
                }
                dir = (SRand1(3) + attr - 1) & 7;
                dir |= attr & 0xf8;
                RlistT(Tindex) = dir;
                LifeR[cellIndex] = dir;
                if (SRand1(100) == 0) {
                    LifeR[cellIndex] = 0;
                    RlistT(Tindex) = 0;
                    if ((dir & 0x80) == 0)
                        BAntsExpired++;
                    else
                        RAntsExpired++;
                }
                return;
            }

    }

    /* ---- high half (opposing colony) ---- */
    mode = RlistM(Tindex);
    TemBModePop[mode]++;

    if (attr < 8) {
        RlistT(Tindex) = 0;
        LifeR[(RlistX(Tindex) << 6) + RlistY(Tindex)] = 0;
        return;
    }

    if (attr > 0x6f) {
        DoNestFightR(x, y);
        return;
    }

    cellIndex = (x << 6) + y;
    ant = LifeR[cellIndex];

    if (ant > 0x80 && ant < 0xe8) {
        index = FindInRList(x, y, ant);
        if (index >= 0) {
            if (ant > 0xdf) {
                RlistT(index) = 0;
                LifeR[(RlistX(index) << 6) + RlistY(index)] = 0;
            }
            if (ant < 0x88) {
                RlistM(Tindex) = 3;
                RlistT(Tindex) |= 8;
                LifeR[cellIndex] = RlistT(Tindex);
                RlistT(index) = 0;
                return;
            }
            winner = GetWinner(RlistT(index), attr);
            RlistT(Tindex) = 0;
            RlistS(index) = winner;
            RlistT(index) = (winner & 0x80) + 0x70;
            LifeR[cellIndex] = (winner & 0x80) + 0x70;
            RlistM(index) = 0xa;
            return;
        }
    }

    if (mode == 6) {
        if (MePlane == 3) {
            StayInR(x, y, attr);
            return;
        }
    } else if (mode == 7) {
        RaidInR(x, y, attr);
        return;
    }

    dir = GetExitDirR(x, y, 8);
    if (dir == 0)
        dir = SRand8();
    else
        dir--;
    if (TryMoveDirR(x, y, dir))
        return;
    if (TryMoveDirR(x, y, SRand8()))
        return;
    LifeR[cellIndex] = RlistT(Tindex);

    return;
}
