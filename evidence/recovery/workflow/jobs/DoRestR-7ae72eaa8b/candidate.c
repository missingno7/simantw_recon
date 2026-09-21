/*
 * DoRestR: resolve a resting/idle R-colony ant at cell (x, y) against an
 * attacker value.  cell points at the LifeR grid cell.  As in DoRandR:
 * if the cell's ant code is in 8..0x67, FindInRList(x,y,ant) locates its
 * Dx8 record and, if found, GetWinner(ant, attacker) decides the fight
 * (RlistS/RlistT/*cell/RlistM-0xa).  Otherwise a yellow ant is checked
 * instead (IsYellowAnt(ant)!=0 && MeColor==0 -> YellowFight(3, Tindex),
 * matching DoRandR's inverted MeColor polarity for the R colony).
 * Either resolution ends the call immediately.  Otherwise: the cell is
 * refreshed from the current Dx8 record's type field
 * (Dx8[Tindex+0x46e6], via a genuine far pointer to Tindex); on a
 * 1-in-20 SRand1(20) roll the mode field is recomputed via the
 * two-argument GetNewMode; otherwise, when the segment8 word at offset
 * 0x85fc (the same unnamed slot DoRestB reads, here tested !=0 instead
 * of ==1) is set, RestBalloons(x, y, 3) is invoked.
 */
extern unsigned char near LifeR[];
extern int near MeColor;
extern int far Tindex;
extern unsigned char far Dx8[];
extern int far IsYellowAnt(int ant);
extern void far YellowFight(int kind, int index);
extern int far FindInRList(int x, int y, int ant);
extern int near GetWinner(int defender, int attacker);
extern int far SRand1(int range);
extern int far GetNewMode(int mode, int fullValue);
extern int far BalloonModeFlag;
extern void far RestBalloons(int x, int y, int plane);

void far DoRestR(int x, int y, int attacker)
{
    unsigned char near *cell;
    int ant;
    int index;
    int winner;
    int handled;
    int far *tindexPtr;
    int t;
    int val;
    int mode;

    cell = &LifeR[(x << 6) + y];
    ant = *cell;
    handled = 0;
    if (ant > 7 && ant < 0x68) {
        index = FindInRList(x, y, ant);
        if (index >= 0) {
            winner = GetWinner(ant, attacker);
            Dx8[index + 0x48dc] = winner;
            Dx8[index + 0x46e6] = (winner & 0x80) + 0x70;
            *cell = (winner & 0x80) + 0x70;
            Dx8[index + 0x44f0] = 0xa;
            handled = 1;
        }
    } else if (IsYellowAnt(ant) != 0 && MeColor == 0) {
        YellowFight(3, Tindex);
        handled = 1;
    }
    if (handled)
        return;

    tindexPtr = &Tindex;
    *cell = Dx8[*tindexPtr + 0x46e6];

    if (SRand1(20) == 0) {
        t = *tindexPtr;
        val = Dx8[t + 0x46e6];
        mode = GetNewMode((val & 0x78) >> 3, val);
        t = *tindexPtr;
        Dx8[t + 0x44f0] = (unsigned char)mode;
        return;
    }

    if (BalloonModeFlag != 0)
        RestBalloons(x, y, 3);
}
