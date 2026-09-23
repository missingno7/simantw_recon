/* Hypothesis: the target’s JE after the alarm-scent lookup selects GetAlarmDir when the scent byte is zero; the prior candidates inverted this test. */
/* Hypothesis: reuse DoToAlarm’s explicit shared hole-test join; target has the same CX zero/one flag and common GoInNest tail. Correct the far YellowFight ABI and near MeColor binding as well. */
/*
 * DoRecruitAnt: per-tick behavior for an A-list ant (index) responding
 * to a recruit/defend call. If its current cell is a nest hole (the
 * same inline IsItHole test as build/grind/agentU/_DoReturnFoodAnt.c),
 * it enters the nest (GoInNest) and returns. Otherwise flags is
 * attribute&0xf8, and the heading comes from one of three functions
 * (all (x,y,dirlow)): when the alarm-scent Dx8 sub-region
 * ((x&-2)<<4)+(y>>1)+0x52d2 (same idiom as build/grind/agentU/
 * _DoToAlarm.c) is nonzero, GetAlarmDir; otherwise, when attribute
 * (unmasked, as a plain word) is > 0x7f, GetRedDefendDir; otherwise
 * GetDefendDir. Dx8/Dy8 step the result to (nx, ny); if the stepped
 * cell's MapA value exceeds Barrier the ant turns in place
 * (TurnTab[dirlow*8+SRand8()]|flags) and returns. An empty destination
 * commits the move (no stamina/scent). An occupied destination checks
 * IsYellowAnt(occupant): when true and (attribute^MeColor)&0x80 is
 * set, YellowFight(index,1); when that XOR bit is clear, if MeWantFood
 * is set the ant first stamps AlistT/LifeA with (occupant|flags) and
 * calls DoTroph(x,y,occupant) (a food-sharing exchange), then in
 * either case turns in place via the same TurnTab expression. A
 * non-yellow occupant with (occupant^attribute)&0x80==0 also turns in
 * place; otherwise it fights like src/recovered/wf_StartFightA-
 * b2f3e31b2f.c: FindInAList(nx,ny), GetWinner(defenderType,
 * attackerType), AlarmHere2(nx,ny,0x28). AlistX/AlistY/AlistT/AlistM/
 * AlistS, Dx8/Dy8, TurnTab, Barrier, TERRAINset, MeColor, MeWantFood
 * and MapA/LifeA are the exact MAPSYM names from direct_data_bindings.
 * IsValidA, SRand8, IsYellowAnt reuse src/recovered/IsValidA.c,
 * src/recovered/SRand8.c, src/recovered/IsYellowAnt.c; GoInNest,
 * GetAlarmDir, GetRedDefendDir, GetDefendDir, YellowFight, DoTroph,
 * FindInAList, GetWinner, AlarmHere2 are unit/game neighbours without
 * an admitted declaration yet.
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
extern unsigned int far MeWantFood;
extern unsigned char near MapA[];
extern unsigned char near LifeA[];
extern unsigned char near MeColor;

extern int far IsValidA(int x, int y);
extern int far SRand8(void);
extern int far GetAlarmDir(int x, int y, int dir);
extern int far GetRedDefendDir(int x, int y, int dir);
extern int far GetDefendDir(int x, int y, int dir);
extern int far IsYellowAnt(int value);
extern int far FindInAList(int x, int y);
extern void near GoInNest(int x, int y, int index);
extern void far YellowFight(int kind, int index);
extern void far DoTroph(int x, int y, int life);
extern int near GetWinner(int defender, int attacker);
extern void near AlarmHere2(int x, int y, int level);

void near DoRecruitAnt(int index)
{
    int x, y;
    int attribute;
    int found;
    int flags;
    int dirlow;
    int newdir;
    int nx, ny;
    int newtile;
    int oldlife;
    unsigned char newattr;

    x = AlistX[index] & 0xff;
    y = AlistY(index);
    attribute = AlistT(index);

    found = 0;
    if (!IsValidA(x, y))
        goto nest_test;
    if (TERRAINset == 0) {
        if (MapA[x * 64 + y] == 0x50)
            found = 1;
        goto nest_test;
    }
    newtile = MapA[x * 64 + y];
    if (newtile >= 0x80 && newtile <= 0x8f)
        found = 1;

nest_test:
    if (found) {
        GoInNest(x, y, index);
        return;
    }

    flags = attribute & 0xf8;
    dirlow = attribute & 7;

    if (Dx8[((x & -2) << 4) + (y >> 1) + 0x52d2] == 0) {
        newdir = GetAlarmDir(x, y, dirlow);
    } else if (attribute > 0x7f) {
        newdir = GetRedDefendDir(x, y, dirlow);
    } else {
        newdir = GetDefendDir(x, y, dirlow);
    }

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

    if (IsYellowAnt(oldlife)) {
        if (((attribute ^ MeColor) & 0x80) != 0) {
            YellowFight(1, index);
            return;
        }
        if (MeWantFood != 0) {
            newattr = (unsigned char)oldlife | flags;
            AlistT(index) = newattr;
            LifeA[x * 64 + y] = newattr;
            DoTroph(x, y, oldlife);
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
