/*
 * DoRecruitN: one turn of a recruited nest ant at LifeB cell (x, y) with
 * the attacker/direction word attacker.  Off the nest plane (MePlane != 2)
 * the turn is handed entirely to DoDigOutB(x, y, attacker).  On the nest
 * plane the cell's ant byte is read: a yellow ant while the player has a
 * colour is resolved by YellowFight(2, Tindex); otherwise an ant code in
 * 0x88..0xe7 is looked up with FindInBList(x, y, ant) and, when found,
 * GetWinner(ant, attacker) decides the fight exactly as CheckNestFightB
 * does (BlistS stamina 0x3f0e, BlistT type 0x3d18 and the LifeB cell take
 * the winner's colour bit plus 0x70, BlistM mode 0x3b22 becomes 0xa).
 * Either resolution sets handled and ends the turn (handled == 1);
 * otherwise the ant tries TryMoveDirB(x, y, attacker & 7) and, on
 * failure, once more with a fresh SRand8() direction.
 *
 * Frame/register evidence (agentY): the target has no cell-pointer
 * variable of its own; [bp-6] is the optimiser's common subexpression
 * &LifeB[(x<<6)+y] shared by the ant read and the fight store, so the
 * subscript is written out at both uses.  index lives at [bp-2], handled
 * at [bp-4] with SI caching (mov [bp-4],1 / mov si,[bp-4] in the fight
 * block where SI still holds ant), ant is cached in SI from its
 * definition, x stays in DI.  The handled flag is set in every leaf of
 * the if/else-if/else chain (no hoisted default store) and tested with
 * == 1 (dec si; je).  This shape is produced only by the /Og build
 * (catalog profile "og", /Oeglw); the baseline /Oelw recomputes the
 * subscript and allocates registers differently.
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
    int index;
    int handled;
    int ant;
    int winner;

    if (MePlane != 2) {
        DoDigOutB(x, y, attacker);
        return;
    }

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

    if (TryMoveDirB(x, y, attacker & 7) != 0)
        return;
    TryMoveDirB(x, y, SRand8());
}
