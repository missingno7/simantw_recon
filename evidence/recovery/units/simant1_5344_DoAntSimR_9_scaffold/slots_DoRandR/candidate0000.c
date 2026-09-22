/*
 * DoRandR: one random-walk turn of a red-colony ant at LifeR cell (x, y),
 * given the combined attacker/direction word attr and a mode hint
 * modeArg.  On a 1-in-32 SRand32()==0 roll the current Dx8 record's mode
 * field (RlistM 0x44f0, Tindex-indexed) is refreshed by GetNewModeR.
 * The cell's ant byte is read.  Red twin of DoRandB with the tests in
 * the opposite order: an ant code in 8..0x67 is looked up with
 * FindInRList(x, y, ant) and, when found, GetWinner(ant, attr) decides
 * the fight (RlistS 0x48dc, RlistT 0x46e6 and the LifeR cell take the
 * winner's colour bit plus 0x70, RlistM 0x44f0 becomes 0xa); a code
 * outside that range that is a yellow ant while the player has no colour
 * is resolved by YellowFight(3, Tindex).  Either resolution sets handled
 * and ends the turn; a failed list lookup or anything else leaves the
 * ant unhandled and it tries TryMoveDirR(x, y, attr & 7) and, on
 * failure, once more with a fresh SRand8() direction.
 *
 * Frame/register evidence (agentY): x in SI and y in DI for the whole
 * body; ant [bp-2], handled [bp-4], index [bp-6] all memory resident and
 * [bp-8] the /Og common subexpression &LifeR[(x<<6)+y] (no cell
 * variable; the subscript is written at both uses).  A failed FindInRList
 * branches straight to the single handled = 0 store (not to the yellow
 * test) while handled keeps only four references, which the
 * break-out-of-block form reproduces; a fifth reference (an inner else
 * handled = 0) would move handled into SI.  The final test is a plain
 * nonzero test (cmp [bp-4],0; jne).  Requires the og profile (/Oeglw).
 */
extern unsigned char near LifeR[];
extern int near MeColor;
extern int far Tindex;
extern unsigned char far Dx8[];
extern int far IsYellowAnt(int ant);
extern void far YellowFight(int kind, int index);
extern int far FindInRList(int x, int y, int ant);
extern int near GetWinner(int defender, int attacker);
extern int far TryMoveDirR(int x, int y, int dir);
extern int far SRand8(void);
extern int far SRand32(void);
extern int far GetNewModeR(int mode);

void far DoRandR(int x, int y, int attr, int modeArg)
{
    int ant;
    int handled;
    int index;
    int winner;

    if (SRand32() == 0)
        Dx8[Tindex + 0x44f0] = (unsigned char)GetNewModeR(modeArg);

    ant = LifeR[(x << 6) + y];
    do {
        if (ant > 7 && ant < 0x68) {
            index = FindInRList(x, y, ant);
            if (index >= 0) {
                winner = GetWinner(ant, attr);
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
    if (TryMoveDirR(x, y, attr & 7) != 0)
        return;
    TryMoveDirR(x, y, SRand8());
}
