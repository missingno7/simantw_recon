/*
 * DoToNestAnt: per-tick behavior for an A-list ant (index) heading
 * toward the nest looking for food. If its current cell is a nest hole
 * (the same inline IsItHole test as build/grind/agentU/
 * _DoReturnFoodAnt.c), it enters the nest (GoInNest) and returns.
 * Otherwise flags/digmode/dirlow split attribute as in
 * build/grind/agentU/_DoDigOutAntA.c, GetNestDir(x,y,dirlow,attribute)
 * (build/grind/agentU/_DoReturnFoodAnt.c's 4-arg form) picks a heading,
 * Dx8/Dy8 step it to (nx,ny), and the stepped cell's MapA value is read
 * as newtile. IsItFood(newtile) (inline, same bands as
 * src/recovered/wf_IsItFood-c02f58780a.c) combined with digmode being
 * 2 or 6 triggers pickup: LifeA/AlistT get (newtile-attribute|flags|8),
 * AlistM becomes 3 (carrying), PickupFoodA(nx,ny) is called and AlistS
 * is set to 0xc8 (full carry), then return -- no move. Otherwise, if
 * newtile exceeds Barrier the ant turns in place and returns; an empty
 * destination commits the move (LifeA/AlistX/AlistY/AlistT updated,
 * AlistS decremented and JamScentRN/JamScentBN jammed by team bit, as
 * in build/grind/agentU/_DoDigOutAntA.c). An occupied destination: when
 * IsYellowAnt(occupant) and (attribute^MeColor)&0x80 is set,
 * YellowFight(index,1); otherwise, when MeWantFood==1, the ant first
 * stamps AlistT/LifeA with (occupant|flags) and calls
 * DoTroph(x,y,occupant) before falling into the shared turn-in-place
 * tail (as in build/grind/agentU/_DoRecruitAnt.c, which checks
 * MeWantFood!=0 instead of ==1); a non-yellow occupant with
 * (occupant^attribute)&0x80==0 also turns in place; otherwise full
 * StartFightA-shaped combat via FindInAList/GetWinner/AlarmHere2.
 * AlistX/AlistY/AlistT/AlistM/AlistS, Dx8/Dy8, TurnTab, Barrier,
 * TERRAINset, MeColor, MeWantFood and MapA/LifeA are the exact MAPSYM
 * names from direct_data_bindings. IsValidA, SRand8, IsYellowAnt reuse
 * src/recovered/IsValidA.c, src/recovered/SRand8.c,
 * src/recovered/IsYellowAnt.c; GoInNest, GetNestDir, PickupFoodA,
 * JamScentRN, JamScentBN, YellowFight, DoTroph, FindInAList, GetWinner,
 * AlarmHere2 are unit/game neighbours (JamScentRN/BN reuse the
 * signatures of src/recovered/wf_JamScentRN-18f9c8a2bb.c and
 * src/recovered/wf_JamScentBN-cd34069882.c) without an admitted
 * declaration yet.
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
extern unsigned char MeColor;

extern int far IsValidA(int x, int y);
extern int far GetNestDir(int x, int y, int dir, int attribute);
extern void far PickupFoodA(int x, int y);
extern int far SRand8(void);
extern void near JamScentRN(int x, int y, int scent);
extern void near JamScentBN(int x, int y, int scent);
extern int far IsYellowAnt(int value);
extern void near GoInNest(int x, int y, int index);
extern void far YellowFight(int index, int flag);
extern void far DoTroph(int x, int y, int life);
extern int far FindInAList(int x, int y);
extern int near GetWinner(int defender, int attacker);
extern void near AlarmHere2(int x, int y, int level);

void near DoToNestAnt(int index)
{
    int x, y;
    int attribute;
    int found;
    int flags;
    int digmode;
    int dirlow;
    int newdir;
    int nx, ny;
    int newtile;
    int isfood;
    int oldlife;
    unsigned char newattr;

    x = AlistX[index] & 0xff;
    y = AlistY(index);
    attribute = AlistT(index);

    if (IsValidA(x, y)) {
        if (TERRAINset == 0) {
            if (MapA[x * 64 + y] == 0x50)
                found = 1;
            else
                found = 0;
        } else {
            newtile = MapA[x * 64 + y];
            if (newtile >= 0x80 && newtile <= 0x8f)
                found = 1;
            else
                found = 0;
        }
    } else {
        found = 0;
        goto hole_join;
    }
hole_join:
    if (found) {
        GoInNest(x, y, index);
        return;
    }
    flags = attribute & 0xf8;
    digmode = (attribute & 0x78) >> 3;
    dirlow = attribute & 7;
    newdir = GetNestDir(x, y, dirlow, attribute);
    nx = x + (signed char)Dx8[newdir];
    ny = y + (signed char)Dy8[newdir];
    newtile = MapA[nx * 64 + ny];

    if (TERRAINset == 0)
        isfood = (newtile >= 0x48 && newtile <= 0x4b);
    else
        isfood = (newtile >= 0x18 && newtile <= 0x27);

    if (isfood && (digmode == 6 || digmode == 2)) {
        newattr = (unsigned char)(newdir | flags | 8);
        AlistT(index) = newattr;
        LifeA[x * 64 + y] = newattr;
        AlistM(index) = 3;
        PickupFoodA(nx, ny);
        AlistS(index) = 0xc8;
        return;
    }

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

        if (AlistS(index) != 0) {
            AlistS(index)--;
            if (attribute & 0x80)
                JamScentRN(nx, ny, AlistS(index));
            else
                JamScentBN(nx, ny, AlistS(index));
        }
        return;
    }

    if (IsYellowAnt(oldlife)) {
        if (((attribute ^ MeColor) & 0x80) != 0) {
            YellowFight(index, 1);
            return;
        }
        newattr = TurnTab[dirlow * 8 + SRand8()] | flags;
        AlistT(index) = newattr;
        LifeA[x * 64 + y] = newattr;
        return;
    }

    if (MeWantFood == 1) {
        newattr = (unsigned char)oldlife | flags;
        AlistT(index) = newattr;
        LifeA[x * 64 + y] = newattr;
        DoTroph(x, y, oldlife);
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
