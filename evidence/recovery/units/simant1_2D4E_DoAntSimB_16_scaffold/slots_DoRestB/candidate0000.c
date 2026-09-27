/*
 * DoRestB: one turn of a resting B-colony ant at LifeB cell (x, y) with
 * the attacker/direction word attacker.  The cell's ant byte is read: a
 * yellow ant while the player has a colour is resolved by
 * YellowFight(2, Tindex); otherwise an ant code in 0x88..0xe7 is looked
 * up with FindInBList(x, y, ant) and, when found, GetWinner(ant,
 * attacker) decides the fight exactly as CheckNestFightB does (BlistS
 * 0x3f0e, BlistT 0x3d18 and the LifeB cell take the winner's colour bit
 * plus 0x70, BlistM 0x3b22 becomes 0xa).  Either resolution sets handled
 * and ends the turn.  Otherwise the cell is refreshed from the current
 * record's type byte BlistT[Tindex]; on a 1-in-20 SRand1(20) roll the
 * record's mode BlistM[Tindex] is recomputed by GetNewMode(caste, type)
 * with caste = bits 3-6 of the type byte; otherwise, when the rest
 * balloon option OptionStates[5] equals 1, RestBalloons(x, y, 2) shows a
 * balloon.
 *
 * Frame/register evidence (agentY): x in DI; ant cached in SI from its
 * definition; index [bp-2]; handled [bp-4] cached in SI (assigned in
 * every leaf, tested with == 1: dec si; je); [bp-6] is the /Og common
 * subexpression &LifeB[(x<<6)+y] (no cell variable) and [bp-0xa]/[bp-8]
 * the /Og far-address subexpression &Tindex reloaded with LES for the
 * three Tindex reads after the fight (no pointer variable); the type
 * byte (cached in DI) and its caste (a separate local, SI) are both
 * computed before the GetNewMode call.  The
 * 0x85fc word of segment 8 lies inside the public OptionStates array
 * (0x85f2), element 5.  Requires the og profile (/Oeglw).
 */
extern unsigned char near LifeB[];
extern int near MeColor;
extern int far Tindex;
extern unsigned char far Dx8[];
extern int far OptionStates[];
extern int far IsYellowAnt(int ant);
extern void far YellowFight(int kind, int index);
extern int far FindInBList(int x, int y, int ant);
extern int near GetWinner(int defender, int attacker);
extern int far SRand1(int range);
extern int far GetNewMode(int caste, int type);
extern void far RestBalloons(int x, int y, int plane);

void far DoRestB(int x, int y, int attacker)
{
    int index;
    int handled;
    int ant;
    int winner;
    int type;
    int caste;

    ant = LifeB[(x << 6) + y];
    if (IsYellowAnt(ant) == 1 && MeColor != 0) {
        YellowFight(2, Tindex);
        handled = 1;
    } else if (ant > 0x87 && ant < 0xe8 && (index = FindInBList(x, y, ant)) >= 0) {
        winner = GetWinner(ant, attacker);
        Dx8[index + 0x3f0e] = winner;
        Dx8[index + 0x3d18] = (winner & 0x80) + 0x70;
        LifeB[(x << 6) + y] = (winner & 0x80) + 0x70;
        Dx8[index + 0x3b22] = 0xa;
        handled = 1;
    } else {
        handled = 0;
    }
    if (handled == 1)
        return;

    LifeB[(x << 6) + y] = Dx8[Tindex + 0x3d18];
    if (SRand1(20) == 0) {
        type = Dx8[Tindex + 0x3d18];
        caste = (type & 0x78) >> 3;
        Dx8[Tindex + 0x3b22] = (unsigned char)GetNewMode(caste, type);
        return;
    }
    if (OptionStates[5] == 1)
        RestBalloons(x, y, 2);
}
