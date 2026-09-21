/*
 * DoRecruitN: resolve one recruited/neutral ant's turn at map cell
 * (x, y) against an attacker value.  When MePlane==2 the call is
 * delegated entirely to DoDigOutB(x,y,attacker).  Otherwise the body is
 * identical to DoRandB's: cell points at the LifeB grid cell; a yellow
 * ant with MeColor set is resolved by YellowFight(2,Tindex); otherwise
 * an ant code in 0x88..0xe7 is looked up via FindInBList(x,y,ant) and,
 * if found, GetWinner(ant,attacker) decides the fight (stamina/type/
 * *cell/mode-0xa, as in CheckNestFightB).  Either resolution ends the
 * call immediately.  Otherwise the ant tries to move: first with
 * dir = attacker & 7, then -- on failure -- with a fresh SRand8()
 * direction (the final attempt's own success/failure is not checked).
 * DoDigOutB, GetWinner and YellowFight are same-code-group calls.
 */
extern int near MePlane;
extern unsigned char near LifeB[];
extern int near MeColor;
extern int far Tindex;
extern unsigned char far Dx8[];
extern void far DoDigOutB(int x, int y, int attacker);
extern int far IsYellowAnt(int ant);
extern void far YellowFight(int kind, int index);
extern int far FindInBList(int x, int y, int ant);
extern int near GetWinner(int defender, int attacker);
extern int far TryMoveDirB(int x, int y, int dir);
extern int far SRand8(void);

void far DoRecruitN(int x, int y, int attacker)
{
    unsigned char near *cell;
    int ant;
    int index;
    int winner;
    int handled;

    if (MePlane == 2) {
        DoDigOutB(x, y, attacker);
        return;
    }

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

    if (TryMoveDirB(x, y, attacker & 7) != 0)
        return;
    TryMoveDirB(x, y, SRand8());
}
