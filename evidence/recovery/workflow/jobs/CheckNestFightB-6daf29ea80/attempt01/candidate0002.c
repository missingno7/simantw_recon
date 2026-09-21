/*
 * CheckNestFightB: resolve an attack on the B-colony nest cell (x, y) by
 * an attacker of the given type.  The LifeB cell's ant byte is read; a
 * yellow ant there while the player has a colour is handled by
 * YellowFight(2, Tindex) and reports 1.  Otherwise an ant code in
 * 0x88..0xe7 is looked up in the B list; when found, GetWinner (near)
 * decides the fight: the list stamina byte (offset 0x3f0e) takes the
 * winner value, the list type byte (0x3d18) and the LifeB cell take the
 * winner's colour bit plus 0x70, the list mode (0x3b22) becomes 0xa and
 * 1 is reported.  All three list bytes share one selector slot, so the
 * segment object is a single far byte addressed by offset.  Anything
 * else reports 0.
 */
extern unsigned char near LifeB[];
extern int near MeColor;
extern int far Tindex;
extern unsigned char far Dx8;
#define AT(off) ((&Dx8)[off])
#define WRITECELL *cell

extern int far IsYellowAnt(int ant);
extern void far YellowFight(int kind, int index);
extern int far FindInBList(int x, int y, int ant);
extern int near GetWinner(int defender, int attacker);

int far CheckNestFightB(int x, int y, int attacker)
{
    
    int ant;
    int index;
    int winner;

    cell = &LifeB[(x << 6) + y];
    ant = (unsigned char)*cell;
    if (IsYellowAnt(ant) == 1 && MeColor != 0) {
        YellowFight(2, Tindex);
        return 1;
    }
    if (ant > 0x87 && ant < 0xe8) {
        index = FindInBList(x, y, ant);
        if (index >= 0) {
            winner = GetWinner(ant, attacker);
            AT(index + 0x3f0e) = winner;
            AT(index + 0x3d18) = (winner & 0x80) + 0x70;
            WRITECELL = (winner & 0x80) + 0x70;
            AT(index + 0x3b22) = 0xa;
            return 1;
        }
    }
    return 0;
}
