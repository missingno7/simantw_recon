/* Hypothesis: express the valid-cell and terrain-specific hole predicate as one compound condition; expect a shared post-predicate GoInNest block. */
/* Hypothesis: match target far-call translation and push order for YellowFight; MeColor is a direct near DGROUP byte. */
/*
 * DoToAlarm: per-tick behavior for an A-list ant (index) heading toward
 * an alarm. If its current cell is a nest hole (the same inline
 * IsItHole test as build/grind/agentU/_DoReturnFoodAnt.c), it enters
 * the nest (GoInNest) and returns. Otherwise the alarm-scent map (a
 * Dx8 sub-region at ((x&-2)<<4)+(y>>1)+0x52d2, same evenized-x/
 * halved-y idiom as src/recovered/wf_JamScentBT-86d27c2a8a.c) is
 * checked at the ant's own cell; when it is 0 and SRand4()==0 (no
 * scent, ~1-in-4 chance) the ant just refreshes LifeA at its own cell
 * and changes mode via GetNewMode(digmode, attribute), returning
 * without moving. Otherwise GetAlarmDir(x, y, attribute&7) picks a
 * heading and Dx8/Dy8 step it to (nx, ny); the rest -- Barrier-gated
 * turn-in-place, empty-cell commit, IsYellowAnt/MeColor-gated
 * YellowFight vs turn, else StartFightA-shaped combat via
 * FindInAList/GetWinner/AlarmHere2 -- is identical to
 * build/grind/agentU/_DoRandAntAA.c. AlistX/AlistY/AlistT/AlistM/
 * AlistS, Dx8/Dy8, TurnTab, Barrier, TERRAINset, MeColor and MapA/
 * LifeA are the exact MAPSYM names from direct_data_bindings.
 * IsValidA, SRand4, SRand8, IsYellowAnt reuse src/recovered/IsValidA.c,
 * src/recovered/SRand4.c, src/recovered/SRand8.c,
 * src/recovered/IsYellowAnt.c; GoInNest, GetNewMode, GetAlarmDir,
 * YellowFight, FindInAList, GetWinner, AlarmHere2 are unit/game
 * neighbours without an admitted declaration yet.
 */
extern unsigned char far AlistX[];
#define AlistY(i) (((unsigned char far *)AlistX)[(i) + 0x278e - 0x23a4])
#define AlistT(i) (((unsigned char far *)AlistX)[(i) + 0x2f62 - 0x23a4])
#define AlistM(i) (((unsigned char far *)AlistX)[(i) + 0x2b78 - 0x23a4])
#define AlistS(i) (((unsigned char far *)AlistX)[(i) + 0x334c - 0x23a4])
extern unsigned char far Dx8[];
extern unsigned char far Dy8[];
extern unsigned char far TurnTab[];
extern int far Barrier;
extern unsigned int far TERRAINset;
extern unsigned char near MapA[];
extern unsigned char near LifeA[];
extern unsigned char near MeColor;

extern int far IsValidA(int x, int y);
extern int far SRand4(void);
extern int far SRand8(void);
extern int far GetNewMode(int mode, int attribute);
extern int far GetAlarmDir(int x, int y, int dir);
extern int far IsYellowAnt(int value);
extern int far FindInAList(int x, int y);
extern void near GoInNest(int x, int y, int index);
extern void far YellowFight(int kind, int index);
extern int near GetWinner(int defender, int attacker);
extern void near AlarmHere2(int x, int y, int level);

void near DoToAlarm(int index)
{
    int x, y;
    int attribute;
    int flags;
    int digmode;
    int dirlow;
    int newdir;
    int nx, ny;
    int newtile;
    int oldlife;
    unsigned char newattr;

    x = AlistX[index] & 0xff;
    y = AlistY(index);
    attribute = AlistT(index);

    if (IsValidA(x, y)) {
        newtile = MapA[x * 64 + y];
        if ((TERRAINset == 0 && newtile == 0x50) ||
            (TERRAINset != 0 && newtile >= 0x80 && newtile <= 0x8f)) {
            GoInNest(x, y, index);
            return;
        }
    }

    flags = attribute & 0xf8;

    if (Dx8[((x & -2) << 4) + (y >> 1) + 0x52d2] == 0 && SRand4() == 0) {
        LifeA[x * 64 + y] = (unsigned char)attribute;
        digmode = (attribute & 0x78) >> 3;
        AlistM(index) = (unsigned char)GetNewMode(digmode, attribute);
        return;
    }

    dirlow = attribute & 7;
    newdir = GetAlarmDir(x, y, dirlow);
    nx = x + (signed char)Dx8[newdir];
    ny = y + (signed char)Dy8[newdir];
    newtile = MapA[nx * 64 + ny];

    if (newtile > Barrier) {
        newattr = TurnTab[dirlow * 8 + SRand8()] | flags;
        AlistT(index) = newattr;
        LifeA[x * 64 + y] = newattr;
        return;
    }

    oldlife = LifeA[nx * 64 + ny];
    if (oldlife == 0) {
        newattr = (unsigned char)newdir | flags;
        LifeA[nx * 64 + ny] = newattr;
        AlistT(index) = newattr;
        LifeA[x * 64 + y] = 0;
        AlistX[index] = (unsigned char)nx;
        AlistY(index) = (unsigned char)ny;
        return;
    }

    if (IsYellowAnt(oldlife) == 1) {
        if (((attribute ^ MeColor) & 0x80) != 0) {
            YellowFight(1, index);
            return;
        }
        newattr = TurnTab[dirlow * 8 + SRand8()] | flags;
        AlistT(index) = newattr;
        LifeA[x * 64 + y] = newattr;
        return;
    }

    if (((oldlife ^ attribute) & 0x80) == 0) {
        newattr = TurnTab[dirlow * 8 + SRand8()] | flags;
        AlistT(index) = newattr;
        LifeA[x * 64 + y] = newattr;
        return;
    }

    {
        int attackertype;
        int loser;

        attackertype = AlistT(index);
        AlistT(index) = 0;
        LifeA[x * 64 + y] = 0;
        loser = FindInAList(nx, ny);
        if (loser >= 0) {
            int winner;
            winner = GetWinner(AlistT(loser), attackertype);
            AlistT(loser) = (unsigned char)((winner & 0x80) + 0x70);
            LifeA[nx * 64 + ny] = (unsigned char)((winner & 0x80) + 0x70);
            AlistM(loser) = 0xa;
            AlistS(loser) = (unsigned char)winner;
            AlarmHere2(nx, ny, 0x28);
        }
    }
}
