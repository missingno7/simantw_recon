/*
 * DoRandR: resolve one R-colony ant's turn at map cell (x, y), given a
 * combined attacker/direction value attr and a mode hint modeArg.  On a
 * roughly 1-in-32 SRand32()==0 roll, the current Dx8 list record's mode
 * field (Tindex-indexed) is refreshed via GetNewModeR(modeArg).  cell
 * points at the LifeR grid cell.  If the cell's ant code is in 8..0x67,
 * FindInRList(x,y,ant) locates its Dx8 record; when found, GetWinner
 * decides the fight (stamina/type/*cell/mode-0xa, as in DoRandB /
 * CheckNestFightB).  Otherwise -- out of that range -- a yellow ant is
 * checked instead: if IsYellowAnt(ant) and the player has NOT yet
 * chosen a colour (MeColor==0), YellowFight(3, Tindex) resolves it
 * (kind 3 for the R colony, vs DoRandB's kind 2).  Either resolution
 * ends the turn immediately.  Otherwise the ant tries to move: first
 * with dir = attr & 7, then -- on failure -- with a fresh SRand8()
 * direction (the final attempt's own success/failure is not checked).
 * Unlike DoRandB, every intermediate value here (cell pointer, ant,
 * fight index, handled flag) is stack-resident, not register-shared.
 * TryMoveDirR is same-code-group (LINK-translated near call), as is
 * YellowFight.
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
    unsigned char near *cell;
    int ant;
    int index;
    int winner;
    int handled;

    if (SRand32() == 0)
        Dx8[Tindex + 0x44f0] = (unsigned char)GetNewModeR(modeArg);

    cell = &LifeR[(x << 6) + y];
    ant = *cell;
    if (ant > 7 && ant < 0x68) {
        index = FindInRList(x, y, ant);
        if (index >= 0) {
            winner = GetWinner(ant, attr);
            Dx8[index + 0x48dc] = winner;
            Dx8[index + 0x46e6] = (winner & 0x80) + 0x70;
            *cell = (winner & 0x80) + 0x70;
            Dx8[index + 0x44f0] = 0xa;
            handled = 1;
        } else {
            handled = 0;
        }
    } else if (IsYellowAnt(ant) != 0 && MeColor == 0) {
        YellowFight(3, Tindex);
        handled = 1;
    } else {
        handled = 0;
    }
    if (handled)
        return;

    if (TryMoveDirR(x, y, attr & 7) != 0)
        return;
    TryMoveDirR(x, y, SRand8());
}
