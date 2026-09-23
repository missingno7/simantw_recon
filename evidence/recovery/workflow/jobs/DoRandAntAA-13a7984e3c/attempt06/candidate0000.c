/*
 * DoRandAntAA: per-tick behavior for an A-list ant (index) doing a
 * random walk. If the ant's current cell is a nest hole (the same
 * inline IsItHole test as build/grind/agentU/_DoReturnFoodAnt.c), it
 * enters the nest (GoInNest) and returns. Otherwise GetRandDir(x, y,
 * attribute&7) picks a new heading (border bounce or
 * TurnTab[dir][SRand8()] inside the yard -- see
 * src/recovered/wf_GetRandDir-2664e9d7f9.c) and Dx8/Dy8 step it to
 * (nx, ny). If the stepped cell's MapA value exceeds Barrier, the ant
 * turns in place instead (TurnTab[dirlow*8+SRand8()]|flags) and
 * returns. Otherwise: an empty destination (LifeA==0) commits the move
 * (LifeA marked at the new cell and cleared at the old one, AlistX/
 * AlistY/AlistT updated) with no further action. An occupied
 * destination checks IsYellowAnt(occupant): when it is exactly a
 * regular yellow ant (IsYellowAnt()==1) and (attribute^MeColor)&0x80 is
 * set, the two yellow ants fight via YellowFight(index, 1); when that
 * XOR bit is clear (from either the yellow-ant case or the
 * (occupant^attribute)&0x80 test in the non-yellow case) the ant
 * instead turns in place at its original cell. Otherwise (hostile,
 * non-yellow, XOR bit set) it fights like src/recovered/wf_StartFightA-
 * b2f3e31b2f.c: clear its own AlistT/LifeA, FindInAList(nx,ny) finds
 * the defender, GetWinner(defenderType, attackerType) decides colour/
 * mode/stamina, and AlarmHere2(nx,ny,0x28) is raised.
 * AlistX/AlistY/AlistT/AlistM/AlistS, Dx8/Dy8, TurnTab, Barrier,
 * TERRAINset, MeColor and MapA/LifeA are the exact MAPSYM names from
 * direct_data_bindings. IsValidA, SRand8, IsYellowAnt reuse
 * src/recovered/IsValidA.c, src/recovered/SRand8.c,
 * src/recovered/IsYellowAnt.c; GetRandDir reuses
 * src/recovered/wf_GetRandDir-2664e9d7f9.c; GoInNest, YellowFight,
 * FindInAList, GetWinner, AlarmHere2 are unit/game neighbours without
 * an admitted declaration yet (FindInAList/GetWinner/AlarmHere2
 * signatures follow src/recovered/wf_StartFightA-b2f3e31b2f.c).
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
extern unsigned char near MapA[];
extern unsigned char near LifeA[];
extern unsigned char MeColor;

extern int far IsValidA(int x, int y);
extern int far GetRandDir(int x, int y, int dir);
extern int far SRand8(void);
extern int far IsYellowAnt(int value);
extern int far FindInAList(int x, int y);
extern void near GoInNest(int x, int y, int index);
extern void far YellowFight(int index, int flag);
extern int near GetWinner(int defender, int attacker);
extern void near AlarmHere2(int x, int y, int level);

void near DoRandAntAA(int index)
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

    flags = attribute & 0xf8;
    dirlow = attribute & 7;
    newdir = GetRandDir(x, y, dirlow);
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
            YellowFight(index, 1);
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
