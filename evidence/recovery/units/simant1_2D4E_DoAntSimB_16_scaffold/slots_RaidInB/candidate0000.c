/*
 * RaidInB: a B-colony ant at map cell (x, y) looks for food to bring back,
 * given a direction hint dirHint.  If MapB[(x<<6)+y] is a food-pile tile
 * (0x10..0x13): a full pile (0x10) is replaced by a fresh SRand8() pile
 * value, otherwise the pile is decremented by one; FoodB (the world food
 * counter) is decremented if positive; the current Dx8 list record
 * (indexed by the shared cursor Tindex) gets mode 3 and has bit 8 set in
 * its type/attribute field, and LifeB is refreshed from that field.
 * Otherwise the ant tries to move: TryMoveDirB with a jittered direction
 * (SRand1(3)+dirHint-2)&7; on failure, GetEnterDirB(x,y,dirHint&7) picks
 * a direction (or, if negative, a fresh SRand1(8) one) and TryMoveDirB is
 * retried; if that also fails the ant simply enters the nest: Dx8's mode
 * field becomes 1 and LifeB is refreshed from its (unmodified) type
 * field.  TryMoveDirB is same-code-group (LINK-translated near call).
 *
 * Frame evidence (agentY): the target keeps y in DI and x in SI for the
 * whole body and holds the map index (x<<6)+y only as a compiler
 * temporary at [bp-4] cached in BX; there is no source-level index
 * variable.  The subscript expression is therefore written out at every
 * use and the temporary is the optimiser's common subexpression, which
 * only the /Og (og profile) build reproduces; under the baseline the
 * expression is recomputed at each use.
 */
extern unsigned char near MapB[];
extern unsigned char near LifeB[];
extern int far Tindex;
extern unsigned char far Dx8[];
extern int far FoodB;
extern int far SRand8(void);
extern int far SRand1(int range);
extern int far GetEnterDirB(int x, int y, int dir);
extern int far TryMoveDirB(int x, int y, int dir);

void far RaidInB(int x, int y, int dirHint)
{
    int dir;

    if (MapB[(x << 6) + y] >= 0x10 && MapB[(x << 6) + y] <= 0x13) {
        if (MapB[(x << 6) + y] == 0x10)
            MapB[(x << 6) + y] = (unsigned char)SRand8();
        else
            MapB[(x << 6) + y]--;
        if (FoodB > 0)
            FoodB--;
        Dx8[Tindex + 0x3b22] = 3;
        Dx8[Tindex + 0x3d18] |= 8;
        LifeB[(x << 6) + y] = Dx8[Tindex + 0x3d18];
        return;
    }

    dir = (SRand1(3) + dirHint - 2) & 7;
    if (TryMoveDirB(x, y, dir) != 0)
        return;

    dir = GetEnterDirB(x, y, dirHint & 7);
    if (dir < 0)
        dir = SRand1(8);
    if (TryMoveDirB(x, y, dir) != 0)
        return;

    Dx8[Tindex + 0x3b22] = 1;
    LifeB[(x << 6) + y] = Dx8[Tindex + 0x3d18];
}
