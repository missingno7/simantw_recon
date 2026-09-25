/*
 * RaidInR: an R-colony ant at map cell (x, y) looks for food to bring
 * back, given a direction hint dirHint.  If MapR[(x<<6)+y] is a
 * food-pile tile (0x10..0x13): a full pile (0x10) is replaced by a
 * fresh SRand8() pile value, otherwise the pile is decremented by one;
 * FoodR (the R-colony food counter) is decremented if positive; the
 * current Dx8 list record (indexed by the shared cursor Tindex) gets
 * mode 3 and has bit 8 set in its type/attribute field, and LifeR is
 * refreshed from that field.  Otherwise the ant tries to move:
 * TryMoveDirR with a jittered direction (SRand1(3)+dirHint-2)&7; on
 * failure, GetEnterDirR(x,y,dirHint&7) picks a direction (or, if
 * negative, a fresh SRand1(8) one) and TryMoveDirR is retried; if that
 * also fails the ant simply enters the nest: Dx8's mode field becomes 1
 * and LifeR is refreshed from its (unmodified) type field.  This mirrors
 * admitted twin RaidInB exactly, with the R-colony field offsets
 * (0x44f0, 0x46e6) used elsewhere by RlistM/RlistT.  TryMoveDirR is
 * same-code-group (LINK-translated near call).
 *
 * Frame/register evidence (agentY, as RaidInB): y in DI and x in SI for the
 * whole body, dir at [bp-2]; [bp-4] is the /Og common subexpression
 * (x<<6)+y cached in BX (no index variable: the subscript is written out
 * at every use).  Requires the og profile (/Oeglw).
 */
extern unsigned char near MapR[];
extern unsigned char near LifeR[];
extern int far Tindex;
extern unsigned char far Dx8[];
extern int far FoodR;
extern int far SRand8(void);
extern int far SRand1(int range);
extern int far GetEnterDirR(int x, int y, int dir);
extern int far TryMoveDirR(int x, int y, int dir);

void far RaidInR(int x, int y, int dirHint)
{
    int dir;

    if (MapR[(x << 6) + y] >= 0x10 && MapR[(x << 6) + y] <= 0x13) {
        if (MapR[(x << 6) + y] == 0x10)
            MapR[(x << 6) + y] = (unsigned char)SRand8();
        else
            MapR[(x << 6) + y]--;
        if (FoodR > 0)
            FoodR--;
        Dx8[Tindex + 0x44f0] = 3;
        Dx8[Tindex + 0x46e6] |= 8;
        LifeR[(x << 6) + y] = Dx8[Tindex + 0x46e6];
        return;
    }

    dir = (SRand1(3) + dirHint - 2) & 7;
    if (TryMoveDirR(x, y, dir) != 0)
        return;

    dir = GetEnterDirR(x, y, dirHint & 7);
    if (dir < 0)
        dir = SRand1(8);
    if (TryMoveDirR(x, y, dir) != 0)
        return;

    Dx8[Tindex + 0x44f0] = 1;
    LifeR[(x << 6) + y] = Dx8[Tindex + 0x46e6];
}
