/*
 * DoRandB: one random-walk turn of a B-colony ant at LifeB cell (x, y),
 * given the combined attacker/direction word attr and a mode hint
 * modeArg.  On a 1-in-32 SRand32()==0 roll the current Dx8 record's mode
 * field (BlistM, Tindex-indexed) is refreshed by GetNewModeB(modeArg).
 * The cell's ant byte is read: a yellow ant while the player has a colour
 * is resolved by YellowFight(2, Tindex); otherwise an ant code in
 * 0x88..0xe7 is looked up with FindInBList(x, y, ant) and, when found,
 * GetWinner(ant, attr) decides the fight exactly as CheckNestFightB does
 * (BlistS 0x3f0e, BlistT 0x3d18 and the LifeB cell take the winner's
 * colour bit plus 0x70, BlistM 0x3b22 becomes 0xa).  Either resolution
 * sets handled and ends the turn; otherwise the ant tries
 * TryMoveDirB(x, y, attr & 7) and, on failure, once more with a fresh
 * SRand8() direction.
 *
 * Frame/register evidence (agentY, mirrors DoRecruitN): no cell-pointer
 * variable; [bp-6] is the /Og common subexpression &LifeB[(x<<6)+y]
 * shared by the ant read and the fight store, so the subscript is written
 * out at both uses.  index at [bp-2], handled at [bp-4] cached in SI
 * (mov [bp-4],1 / mov si,[bp-4] where SI still holds ant), ant cached in
 * SI from its definition, x in DI; handled is assigned in every leaf and
 * tested with == 1 (dec si; je).  Requires the og profile (/Oeglw).
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
    int index;
    int handled;
    int ant;
    int winner;

    if (SRand32() == 0)
        Dx8[Tindex + 0x3b22] = (unsigned char)GetNewModeB(modeArg);

    ant = LifeB[(x << 6) + y];
    if (IsYellowAnt(ant) == 1 && MeColor != 0) {
        YellowFight(2, Tindex);
        handled = 1;
    } else if (ant > 0x87 && ant < 0xe8 && (index = FindInBList(x, y, ant)) >= 0) {
        winner = GetWinner(ant, attr);
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

    if (TryMoveDirB(x, y, attr & 7) != 0)
        return;
    TryMoveDirB(x, y, SRand8());
}
