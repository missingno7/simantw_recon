/*
 * DoRandB: resolve one B-colony ant's turn at map cell (x, y), given a
 * combined attacker/direction value attr and a mode hint modeArg.  On a
 * roughly 1-in-32 SRand32()==0 roll, the current Dx8 list record's mode
 * field (Tindex-indexed) is refreshed via GetNewModeB(modeArg).  cell
 * points at the LifeB grid cell; if a yellow ant occupies it and the
 * player has a colour, YellowFight(2, Tindex) resolves it.  Otherwise,
 * if the cell holds an ant code in 0x88..0xe7, FindInBList(x,y,ant)
 * locates its Dx8 record; when found, GetWinner(ant, attr) decides the
 * fight exactly as CheckNestFightB does (stamina field, type field,
 * *cell, mode field 0xa).  Either resolution (yellow fight or ant fight)
 * ends the turn immediately.  Otherwise the ant tries to move: first
 * with dir = attr & 7, then -- on failure -- with a fresh SRand8()
 * direction (the final attempt's own success/failure is not checked).
 * TryMoveDirB is same-code-group (LINK-translated near call), as are
 * GetWinner and YellowFight.
 */
extern unsigned char near LifeB[];
extern int near MeColor;
extern int far Tindex;
extern unsigned char far Dx8[];
extern int far IsYellowAnt(int ant);
extern void far YellowFight(int kind, int index);
extern int far FindInBList(int x, int y, int ant);
extern int near GetWinner(int defender, int attacker);
extern int far TryMoveDirB(int x, int y, int dir);
extern int far SRand8(void);
extern int far SRand32(void);
extern int far GetNewModeB(int mode);

void far DoRandB(int x, int y, int attr, int modeArg)
{
    int handled;
    unsigned char near *cell;
    int ant;
    int index;
    int winner;

    if (SRand32() == 0)
        Dx8[Tindex + 0x3b22] = (unsigned char)GetNewModeB(modeArg);

    cell = &LifeB[(x << 6) + y];
    ant = *cell;
    handled = 0;
    if (IsYellowAnt(ant) == 1 && MeColor != 0) {
        YellowFight(2, Tindex);
        handled = 1;
    } else if (ant > 0x87 && ant < 0xe8) {
        index = FindInBList(x, y, ant);
        if (index >= 0) {
            winner = GetWinner(ant, attr);
            Dx8[index + 0x3f0e] = winner;
            Dx8[index + 0x3d18] = (winner & 0x80) + 0x70;
            *cell = (winner & 0x80) + 0x70;
            Dx8[index + 0x3b22] = 0xa;
            handled = 1;
        }
    }
    if (handled)
        return;

    if (TryMoveDirB(x, y, attr & 7) != 0)
        return;
    TryMoveDirB(x, y, SRand8());
}
