/*
 * DoRestB: resolve a resting/idle B-colony ant at cell (x, y) against an
 * attacker value.  cell points at the LifeB grid cell.  As in DoRandB /
 * CheckNestFightB: a yellow ant with MeColor set is resolved by
 * YellowFight(2, Tindex); otherwise an ant code in 0x88..0xe7 is looked
 * up via FindInBList(x,y,ant) and, if found, GetWinner(ant, attacker)
 * decides the fight (stamina/type/*cell/mode-0xa).  Either resolution
 * ends the call immediately.  Otherwise (no fight): the cell is
 * refreshed from the current Dx8 record's type field
 * (Dx8[Tindex+0x3d18], via a genuine far pointer to Tindex, matching
 * the target's explicit LES-based dereference); on a 1-in-20 SRand1(20)
 * roll the mode field is recomputed via the two-argument GetNewMode
 * (bits 3-6 of the type value, and the type value itself) exactly as
 * GetNewModeB likely wraps it; otherwise, when the segment8 word at
 * offset 0x85fc (no MAPSYM public name found for this slot) equals 1,
 * RestBalloons(x, y, 2) is invoked.
 */
extern unsigned char near LifeB[];
extern int near MeColor;
extern int far Tindex;
extern unsigned char far Dx8[];
extern int far IsYellowAnt(int ant);
extern void far YellowFight(int kind, int index);
extern int far FindInBList(int x, int y, int ant);
extern int near GetWinner(int defender, int attacker);
extern int far SRand1(int range);
extern int far GetNewMode(int mode, int fullValue);
extern int far BalloonModeFlag;
extern void far RestBalloons(int x, int y, int plane);

void far DoRestB(int x, int y, int attacker)
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

    cell = &LifeB[(x << 6) + y];
    ant = *cell;
    handled = 0;
    if (IsYellowAnt(ant) == 1 && MeColor != 0) {
        YellowFight(2, Tindex);
        handled = 1;
    } else if (ant > 0x87 && ant < 0xe8) {
        index = FindInBList(x, y, ant);
        if (index >= 0) {
            winner = GetWinner(ant, attacker);
            Dx8[index + 0x3f0e] = winner;
            Dx8[index + 0x3d18] = (winner & 0x80) + 0x70;
            *cell = (winner & 0x80) + 0x70;
            Dx8[index + 0x3b22] = 0xa;
            handled = 1;
        }
    }
    if (handled)
        return;

    tindexPtr = &Tindex;
    *cell = Dx8[*tindexPtr + 0x3d18];

    if (SRand1(20) == 0) {
        t = *tindexPtr;
        val = Dx8[t + 0x3d18];
        mode = GetNewMode((val & 0x78) >> 3, val);
        t = *tindexPtr;
        Dx8[t + 0x3b22] = (unsigned char)mode;
        return;
    }

    if (BalloonModeFlag == 1)
        RestBalloons(x, y, 2);
}
