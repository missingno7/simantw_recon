/*
 * DoRestR: one turn of a resting red-colony ant at LifeR cell (x, y)
 * with the attacker/direction word attacker.  Red twin of DoRestB with
 * DoRandR's test order: an ant code in 8..0x67 is looked up with
 * FindInRList(x, y, ant) and, when found, GetWinner(ant, attacker)
 * decides the fight (RlistS 0x48dc, RlistT 0x46e6 and the LifeR cell
 * take the winner's colour bit plus 0x70, RlistM 0x44f0 becomes 0xa); a
 * code outside that range that is a yellow ant while the player has no
 * colour is resolved by YellowFight(3, Tindex).  Either resolution sets
 * handled and ends the turn.  Otherwise the cell is refreshed from the
 * current record's type byte RlistT[Tindex]; on a 1-in-20 SRand1(20)
 * roll the record's mode RlistM[Tindex] is recomputed by
 * GetNewMode(caste, type) with caste = bits 3-6 of the type byte;
 * otherwise, when the rest balloon option OptionStates[5] is set,
 * RestBalloons(x, y, 3) shows a balloon.
 *
 * Frame/register evidence (agentY): y in SI and x in DI for the whole
 * body; ant [bp-2], handled [bp-4], index [bp-6] memory resident; [bp-8]
 * is the /Og common subexpression &LifeR[(x<<6)+y] (no cell variable)
 * and [bp-0xc]/[bp-0xa] the /Og far-address subexpression &Tindex
 * reloaded with LES for the Tindex reads after the fight (no pointer
 * variable).  A failed FindInRList branches straight to the single
 * handled = 0 store while handled keeps four references (break-out-of-
 * block form, as in DoRandR); the flag test is a plain nonzero test.
 * The type byte (DI) and its caste (SI) are computed before the
 * GetNewMode call.  The 0x85fc word of segment 8 is OptionStates[5].
 * Requires the og profile (/Oeglw).
 */
extern unsigned char near LifeR[];
extern int near MeColor;
extern int far Tindex;
extern unsigned char far Dx8[];
extern int far OptionStates[];
extern int far IsYellowAnt(int ant);
extern void far YellowFight(int kind, int index);
extern int far FindInRList(int x, int y, int ant);
extern int near GetWinner(int defender, int attacker);
extern int far SRand1(int range);
extern int far GetNewMode(int caste, int type);
extern void far RestBalloons(int x, int y, int plane);

void far DoRestR(int x, int y, int attacker)
{
    int ant;
    int handled;
    int index;
    int winner;
    int type;
    int caste;

    ant = LifeR[(x << 6) + y];
    do {
        if (ant > 7 && ant < 0x68) {
            index = FindInRList(x, y, ant);
            if (index >= 0) {
                winner = GetWinner(ant, attacker);
                Dx8[index + 0x48dc] = winner;
                Dx8[index + 0x46e6] = (winner & 0x80) + 0x70;
                LifeR[(x << 6) + y] = (winner & 0x80) + 0x70;
                Dx8[index + 0x44f0] = 0xa;
                handled = 1;
                break;
            }
        } else if (IsYellowAnt(ant) != 0 && MeColor == 0) {
            YellowFight(3, Tindex);
            handled = 1;
            break;
        }
        handled = 0;
    } while (0);
    if (handled)
        return;

    LifeR[(x << 6) + y] = Dx8[Tindex + 0x46e6];
    if (SRand1(20) == 0) {
        type = Dx8[Tindex + 0x46e6];
        caste = (type & 0x78) >> 3;
        Dx8[Tindex + 0x44f0] = (unsigned char)GetNewMode(caste, type);
        return;
    }
    if (OptionStates[5] != 0)
        RestBalloons(x, y, 3);
}
