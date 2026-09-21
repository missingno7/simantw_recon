/*
 * CheckNestFightR: resolve an attack on the R-colony nest cell (x, y) by
 * an attacker of the given type.  An ant code in 8..0x67 in the LifeR
 * cell is looked up in the R list; when found, GetWinner (near) decides
 * the fight: the list stamina byte (offset 0x48dc) takes the winner
 * value, the list type byte (0x46e6) and the LifeR cell take the
 * winner's colour bit plus 0x70, the list mode (0x44f0) becomes 0xa and
 * 1 is reported.  Any other code that is a yellow ant, while the player
 * has no colour yet, is handled by YellowFight(3, Tindex) and reports 1.
 * Everything else reports 0.  The three list bytes share one selector
 * slot, so the segment object is a single far byte addressed by offset;
 * Tindex is declared first so its selector slot precedes the list's.
 */
extern unsigned char near LifeR[];
extern int near MeColor;
extern int far Tindex;
extern unsigned char far Dx8;
#define AT(off) ((&Dx8)[off])

extern int far FindInRList(int x, int y, int ant);
extern int near GetWinner(int defender, int attacker);
extern int far IsYellowAnt(int ant);
extern void far YellowFight(int kind, int index);

int far CheckNestFightR(int x, int y, long attacker)
{
    unsigned char near *cell;
    int ant;
    int index;
    int winner;

    cell = &LifeR[(x << 6) + y];
    ant = *cell;
    if (ant > 7 && ant < 0x68) {
        index = FindInRList(x, y, ant);
        if (index >= 0) {
            winner = GetWinner(ant, (int)attacker);
            AT(index + 0x48dc) = winner;
            AT(index + 0x46e6) = (winner & 0x80) + 0x70;
            *cell = (winner & 0x80) + 0x70;
            AT(index + 0x44f0) = 0xa;
            return 1;
        }
    } else if (IsYellowAnt(ant) && MeColor == 0) {
        YellowFight(3, Tindex);
        return 1;
    }
    return 0;
}
