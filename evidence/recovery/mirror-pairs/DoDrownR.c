/* Derived mechanically from the mirrored colony function _DoDrownB (tools/mirror_pairs.py):
 * colony-specific MAPSYM identifiers swapped BAntsExpired->RAntsExpired, BlistM->RlistM, BlistT->RlistT, DoDigInB->DoDigInR, DoDrownB->DoDrownR, GetNewModeB->GetNewModeR, LifeB->LifeR, MapB->MapR; constants and structure unchanged.
 * Verified only by the strict matcher; where the pair is not a pure mirror the
 * diagnostic names the asymmetry. */
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
 * (bare return).  On a zero roll the ant drowns: LifeB[x][y] and
 * BlistT[Tindex] are cleared, and one of two far long tallies is
 * incremented depending on newAttr's high bit (0x80): RAntsExpired
 * when set, BAntsExpired when clear.
 */
extern unsigned char near LifeR[];
extern unsigned char near MapR[64][64];
extern int far Tindex;
extern unsigned char far RlistM[];
extern unsigned char far RlistT[];
extern long far RAntsExpired;
extern long far RAntsExpired;
extern int far GetNewModeR(int mode);
extern int far SRand1(int range);

int far DoDrownR(int x, int y, int dirArg)
{
    int newAttr;

    if (MapR[x][y] < 0x14) {
        RlistM[Tindex] = GetNewModeR((dirArg & 0x78) >> 3);
        return;
    }

    newAttr = ((SRand1(3) + dirArg - 1) & 7) | (dirArg & 0xf8);
    RlistT[Tindex] = newAttr;
    LifeR[(x << 6) + y] = newAttr;

    if (SRand1(100) != 0)
        return;

    LifeR[(x << 6) + y] = 0;
    RlistT[Tindex] = 0;

    if (newAttr & 0x80)
        RAntsExpired++;
    else
        RAntsExpired++;
    return;
}
