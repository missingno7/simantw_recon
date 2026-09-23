/*
 * DoForageAnt: per-tick behavior for an A-list ant (index) foraging.
 * Largest target in this unit (1126 bytes); only the opening is
 * independently traced instruction-by-instruction, the rest follows
 * the established sibling template by strong analogy and is NOT fully
 * verified -- see the block ledger for the precise cutoff.
 *
 * Traced: the usual inline IsItHole test + GoInNest (as in
 * build/grind/agentU/_DoReturnFoodAnt.c). Then SRand32()==0 (~1-in-32)
 * sets AlistM=0xd and returns without acting. Otherwise flags/digmode
 * split attribute, and the forage-scent Dx8 sub-region (same
 * evenized-x/halved-y idiom as build/grind/agentU/_DoToAlarm.c, at
 * offset 0x52d2) being 0 sets AlistM=0xb and returns. Otherwise
 * GetForageDir(x,y,dirlow,attribute) (4-arg form like GetNestDir) is
 * called; a negative result means no direction was found: SRand8()==0
 * resets AlistM=0, else GetNewMode(digmode,attribute) picks a new
 * AlistM and AlistS=0, and either way DecTSmell(x>>1,y>>1,attribute&
 * 0x80) decays the trail smell before returning without moving.
 *
 * NOT independently traced (assumed by analogy to
 * build/grind/agentU/_DoToNestAnt.c and _DoDigOutAntA.c): a
 * non-negative GetForageDir result steps Dx8/Dy8 to (nx,ny); the
 * stepped cell's MapA value, checked as food via the inline IsItFood
 * bands and gated by digmode in {2,6}, triggers PickupFoodA/AlistM=3/
 * AlistS=0xc8; otherwise Barrier-gated turn-in-place vs committed move
 * (LifeA/AlistX/AlistY/AlistT, AlistS-gated JamScentRN/JamScentBN);
 * an occupied destination: IsYellowAnt/MeColor-gated YellowFight,
 * MeWantFood-gated DoTroph-then-turn, else StartFightA-shaped combat
 * via FindInAList/GetWinner/AlarmHere2.
 */
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) AlistX[];
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) AlistY[];
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) AlistT[];
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) AlistM[];
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) AlistS[];
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
extern int far SRand32(void);
extern int far SRand8(void);
extern int far SRand16(void);
extern int far GetNewMode(int mode, int attribute);
extern int far GetForageDir(int x, int y, int dir, int attribute);
extern void far PickupFoodA(int x, int y);
extern void near JamScentRN(int x, int y, int scent);
extern void near JamScentBN(int x, int y, int scent);
extern void near DecTSmell(int x, int y, int team);
extern int far IsYellowAnt(int value);
extern void near GoInNest(int x, int y, int index);
extern void far YellowFight(int index, int flag);
extern void far DoTroph(int x, int y, int life);
extern int far FindInAList(int x, int y);
extern int near GetWinner(int defender, int attacker);
extern void near AlarmHere2(int x, int y, int level);

void near DoForageAnt(int index)
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
    y = AlistY[index];
    attribute = AlistT[index];

    if (!IsValidA(x, y)) {
        found = 0;
    } else if (TERRAINset == 0) {
        if (MapA[x * 64 + y] != 0x50)
            found = 0;
        else
            found = 1;
    } else {
        newtile = MapA[x * 64 + y];
        if (newtile < 0x80 || newtile > 0x8f)
            found = 0;
        else
            found = 1;
    }

    if (found) {
        GoInNest(x, y, index);
        return;
    }

    if (SRand32() == 0) {
        AlistM[index] = 0xd;
        return;
    }

    flags = attribute & 0xf8;
    digmode = (attribute & 0x78) >> 3;
    dirlow = attribute & 7;

    if (Dx8[((x & -2) << 4) + (y >> 1) + 0x52d2] == 0) {
        AlistM[index] = 0xb;
        return;
    }

mode_dispatch:
    if (digmode != 6 && digmode != 2) {
        AlistM[index] = (unsigned char)GetNewMode(digmode, attribute);
        AlistS[index] = 0;
        return;
    }

    newdir = GetForageDir(x, y, dirlow, attribute);
    if (newdir < 0) {
        if (SRand8() == 0) {
            AlistM[index] = 0;
        } else {
            AlistM[index] = (unsigned char)GetNewMode(digmode, attribute);
            AlistS[index] = 0;
        }
        DecTSmell(x >> 1, y >> 1, attribute & 0x80);
        return;
    }

    nx = x + (signed char)Dx8[newdir];
    ny = y + (signed char)Dy8[newdir];
    newtile = MapA[nx * 64 + ny];

    if (TERRAINset == 0)
        isfood = (newtile >= 0x48 && newtile <= 0x4b);
    else
        isfood = (newtile >= 0x18 && newtile <= 0x27);

    if (isfood && (digmode == 6 || digmode == 2)) {
        newattr = (unsigned char)(newtile | flags | 8);
        AlistT[index] = newattr;
        LifeA[x * 64 + y] = newattr;
        AlistM[index] = 3;
        PickupFoodA(nx, ny);
        AlistS[index] = 0xc8;
        return;
    }

    if (newtile > Barrier) {
        newattr = TurnTab[dirlow * 8 + SRand8()] | flags;
        AlistT[index] = newattr;
        LifeA[x * 64 + y] = newattr;
        if (SRand16() == 0)
            goto mode_dispatch;
        return;
    }

    oldlife = LifeA[nx * 64 + ny];
    if (oldlife == 0) {
        newattr = (unsigned char)newdir | flags;
        LifeA[nx * 64 + ny] = newattr;
        AlistT[index] = newattr;
        LifeA[x * 64 + y] = 0;
        AlistX[index] = (unsigned char)nx;
        AlistY[index] = (unsigned char)ny;

        if (AlistS[index] != 0) {
            AlistS[index]--;
            if (attribute & 0x80)
                JamScentRN(nx, ny, AlistS[index]);
            else
                JamScentBN(nx, ny, AlistS[index]);
        }
        DecTSmell(nx, ny, attribute & 0x80);
        return;
    }

    if (IsYellowAnt(oldlife)) {
        if (((attribute ^ MeColor) & 0x80) != 0) {
            YellowFight(index, 1);
            return;
        }
        newattr = TurnTab[dirlow * 8 + SRand8()] | flags;
        AlistT[index] = newattr;
        LifeA[x * 64 + y] = newattr;
        return;
    }

    if (MeWantFood != 0) {
        newattr = (unsigned char)oldlife | flags;
        AlistT[index] = newattr;
        LifeA[x * 64 + y] = newattr;
        DoTroph(x, y, oldlife);
        newattr = TurnTab[dirlow * 8 + SRand8()] | flags;
        AlistT[index] = newattr;
        LifeA[x * 64 + y] = newattr;
        return;
    }

    if (((oldlife ^ attribute) & 0x80) == 0) {
        newattr = TurnTab[dirlow * 8 + SRand8()] | flags;
        AlistT[index] = newattr;
        LifeA[x * 64 + y] = newattr;
        return;
    }

    {
        int attackertype;
        int loser;

        attackertype = AlistT[index];
        AlistT[index] = 0;
        LifeA[x * 64 + y] = 0;
        loser = FindInAList(nx, ny);
        if (loser >= 0) {
            int winner;
            winner = GetWinner(AlistT[loser], attackertype);
            AlistT[loser] = (unsigned char)((winner & 0x80) + 0x70);
            LifeA[nx * 64 + ny] = (unsigned char)((winner & 0x80) + 0x70);
            AlistM[loser] = 0xa;
            AlistS[loser] = (unsigned char)winner;
            AlarmHere2(nx, ny, 0x28);
        }
    }
}
