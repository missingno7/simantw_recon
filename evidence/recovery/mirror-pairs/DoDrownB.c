/* Derived mechanically from the mirrored colony function _DoDrownR (tools/mirror_pairs.py):
 * colony-specific MAPSYM identifiers swapped ClearLifeR->ClearLifeB, DoAntSimR->DoAntSimB, DoDrownR->DoDrownB, FindInRList->FindInBList, GetNewModeR->GetNewModeB, LifeR->LifeB, MapR->MapB, RAntsExpired->BAntsExpired; constants and structure unchanged.
 * Verified only by the strict matcher; where the pair is not a pure mirror the
 * diagnostic names the asymmetry. */
/*
 * DoDrownR: resolve an R-colony ant possibly standing in water at map
 * cell (x, y).  MapR[(x<<6)+y] terrain below 0x14 is ordinary land: the
 * ant's mode is simply recomputed from the packed attribute/direction
 * byte (bits 3-6 via GetNewModeR) and stored into the mode field of the
 * current Dx8 list record (offset 0x44f0, indexed by the shared cursor
 * Tindex).  0x14 or above is water: a fresh direction is rolled
 * (SRand1(3)+attr-1, masked to the low 3 bits, or'd with the preserved
 * high bits of attr including the colour bit) and stored into both the
 * record's type/attribute field (offset 0x46e6) and the LifeR map cell.
 * A 1-in-100 SRand1(100) roll then actually drowns the ant: LifeR and
 * the type field are cleared and one of the two far 32-bit "ants
 * expired" counters is incremented depending on the new value's colour
 * bit (0x80): RAntsExpired when set, BAntsExpired otherwise -- the same
 * shared counters DoDrownB uses.  Dx8 is the one shared far ant-record
 * object (DoAntSimR/ClearLifeR/FindInRList); its R-colony fields sit at
 * the same offsets used there.
 */
extern unsigned char near MapB[];
extern unsigned char near LifeB[];
extern int far Tindex;
extern unsigned char far Dx8[];
extern long far BAntsExpired;
extern long far BAntsExpired;
extern int far GetNewModeB(int mode);
extern int far SRand1(int range);

void far DoDrownB(int x, int y, int attr)
{
    int index;
    int a;
    int dir;

    index = x;
    index = (index << 6) + y;
    if (MapB[index] < 0x14) {
        Dx8[Tindex + 0x44f0] = (unsigned char)GetNewModeB((attr & 0x78) >> 3);
        return;
    }

    a = attr;
    dir = SRand1(3);
    dir = dir + a;
    dir = dir - 1;
    dir = dir & 7;
    dir = dir | (a & 0xf8);
    Dx8[Tindex + 0x46e6] = (unsigned char)dir;
    LifeB[index] = (unsigned char)dir;

    if (SRand1(100) == 0) {
        LifeB[index] = 0;
        Dx8[Tindex + 0x46e6] = 0;
        if (dir & 0x80)
            BAntsExpired++;
        else
            BAntsExpired++;
    }
}
