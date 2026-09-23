/* Hypothesis: match target push order for YellowFight and clear the previous LifeA cell after committing a move; use the proven shared based segment for all A-list arrays. */
/*
 * DoAttackAnt: per-tick behavior for an A-list ant (index) in "attack"
 * mode, hunting toward the enemy nest. If the ant's current cell is a
 * nest hole (the same inline IsItHole test as build/grind/agentU/
 * _DoReturnFoodAnt.c), it enters the nest (GoInNest) and returns.
 * Otherwise the caste bits (attribute&0x78)>>3 are looked up in
 * IsCarryCaste[caste*2]; when that caste is a carrying caste (==1) the
 * caste is replaced by UnCarryCaste[caste] (direction bits 0-2 and the
 * team bit 0x80 preserved via &0x87) before continuing, dropping
 * whatever it was carrying. GetNestDir(x, y, attribute&7, attribute^
 * 0x80) then picks a heading toward the *enemy* nest (team bit
 * flipped) and Dx8/Dy8 step it to (nx, ny) -- same idiom as
 * build/grind/agentU/_DoReturnFoodAnt.c's GetNestDir call, just with
 * the flipped team bit. If the stepped cell's MapA value exceeds
 * Barrier, the ant turns in place (TurnTab[dirlow*8+SRand8()]|flags)
 * and returns. Otherwise: an empty destination commits the move (no
 * stamina/scent here). An occupied destination checks
 * IsYellowAnt(occupant): when it is exactly a regular yellow ant and
 * (attribute^MeColor)&0x80 is set, the two yellow ants fight via
 * YellowFight(1, index); when that XOR bit is clear (either case) or
 * (occupant^attribute)&0x80==0 in the non-yellow case, the ant instead
 * turns in place at its original cell. Otherwise (hostile, non-yellow)
 * it fights like src/recovered/wf_StartFightA-b2f3e31b2f.c:
 * FindInAList(nx,ny) for the defender, GetWinner(defenderType,
 * attackerType), and AlarmHere2(nx,ny,0x28).
 * AlistX/AlistY/AlistT/AlistM/AlistS, IsCarryCaste, UnCarryCaste,
 * Dx8/Dy8, TurnTab, Barrier, TERRAINset, MeColor and MapA/LifeA are the
 * exact MAPSYM names from direct_data_bindings. IsValidA, SRand8,
 * IsYellowAnt reuse src/recovered/IsValidA.c, src/recovered/SRand8.c,
 * src/recovered/IsYellowAnt.c; GoInNest, GetNestDir, YellowFight,
 * FindInAList, GetWinner, AlarmHere2 are unit/game neighbours without
 * an admitted declaration yet.
 */
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) AlistX[];
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) AlistY[];
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) AlistT[];
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) AlistM[];
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) AlistS[];
extern unsigned int far IsCarryCaste[];
extern unsigned char far UnCarryCaste[];
extern unsigned char far Dx8[];
extern unsigned char far Dy8[];
extern unsigned char far TurnTab[];
extern int far Barrier;
extern unsigned int far TERRAINset;
extern unsigned char near MapA[];
extern unsigned char near LifeA[];
extern unsigned char MeColor;

extern int far IsValidA(int x, int y);
extern int far GetNestDir(int x, int y, int dir, int attribute);
extern int far SRand8(void);
extern int far IsYellowAnt(int value);
extern int far FindInAList(int x, int y);
extern void near GoInNest(int x, int y, int index);
extern void near YellowFight(int kind, int index);
extern int near GetWinner(int defender, int attacker);
extern void near AlarmHere2(int x, int y, int level);

void near DoAttackAnt(int index)
{
    int x, y;
    int attribute;
    int found;
    int caste;
    int flags;
    int dirlow;
    int newdir;
    int nx, ny;
    int newtile;
    int oldlife;
    unsigned char newattr;

    x = AlistX[index];
    y = AlistY[index];
    attribute = AlistT[index] & 0xff;

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

    caste = (attribute & 0x78) >> 3;
    if (IsCarryCaste[caste] == 1)
        attribute = (UnCarryCaste[caste] << 3) | (attribute & 0x87);

    flags = attribute & 0xf8;
    dirlow = attribute & 7;
    newdir = GetNestDir(x, y, dirlow, attribute ^ 0x80);
    nx = x + (signed char)Dx8[newdir];
    ny = y + (signed char)Dy8[newdir];
    newtile = MapA[nx * 64 + ny];

    if (newtile > Barrier) {
        newattr = TurnTab[dirlow * 8 + SRand8()] | flags;
        AlistT[index] = newattr;
        LifeA[x * 64 + y] = newattr;
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
        return;
    }

    if (IsYellowAnt(oldlife) == 1) {
        if (((attribute ^ MeColor) & 0x80) != 0) {
            YellowFight(1, index);
            return;
        }
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
