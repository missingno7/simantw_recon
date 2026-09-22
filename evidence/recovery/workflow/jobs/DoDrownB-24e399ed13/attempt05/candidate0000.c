/*
 * DoDrownB: per-turn drowning check for a B ant at (x, y) with
 * direction/state byte dirArg.  If the MapB tile there is still
 * deep water (< 0x14), the ant just transitions state via
 * GetNewModeB((dirArg&0x78)>>3), stored into BlistM[Tindex], and
 * returns (still stuck in the water; the store-then-bare-return
 * shape matches DoDigInB's proven byte-exact mode-transition tail).
 * Otherwise (tile >= 0x14, shallow/opened ground) a new direction
 * byte is rolled: newAttr = ((SRand1(3) + dirArg - 1) & 7) |
 * (dirArg & 0xf8), stored into both BlistT[Tindex] and LifeB[x][y].
 * An SRand1(100) roll that comes back nonzero ends the turn there
 * (bare return).  The attribute parameter is copied to a local that is
 * updated in place (SI); the cell index (x<<6)+y is written out at each
 * use and becomes a /Og common subexpression with a frame home.  On a zero roll the ant drowns: LifeB[x][y] and
 * BlistT[Tindex] are cleared, and one of two far long tallies is
 * incremented depending on newAttr's high bit (0x80): RAntsExpired
 * when set, BAntsExpired when clear.
 */
extern unsigned char near LifeB[];
extern unsigned char near MapB[];
extern int far Tindex;
extern unsigned char far BlistM[];
extern unsigned char far BlistT[];
extern long far RAntsExpired;
extern long far BAntsExpired;
extern int far GetNewModeB(int mode);
extern int far SRand1(int range);

int far DoDrownB(int x, int y, int attrArg)
{
    int attr;

    if (MapB[(x << 6) + y] < 0x14) {
        BlistM[Tindex] = GetNewModeB((attrArg & 0x78) >> 3);
        return;
    }

    attr = attrArg;
    attr = ((SRand1(3) + attr - 1) & 7) | (attr & 0xf8);
    BlistT[Tindex] = attr;
    LifeB[(x << 6) + y] = attr;

    if (SRand1(100) != 0)
        return;

    LifeB[(x << 6) + y] = 0;
    BlistT[Tindex] = 0;

    if (attr & 0x80)
        RAntsExpired++;
    else
        BAntsExpired++;
    return;
}
