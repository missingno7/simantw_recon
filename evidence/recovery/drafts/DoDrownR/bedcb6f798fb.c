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
struct RListPlanes {
    unsigned char x[502];
    unsigned char y[502];
    unsigned char m[502];
    unsigned char t[502];
    unsigned char s[502];
};
extern struct RListPlanes far RlistX;
extern unsigned char near MapR[];
extern unsigned char near LifeR[];
extern int far Tindex;
extern unsigned char far Dx8[];
extern long far RAntsExpired;
extern long far BAntsExpired;
extern int far GetNewModeR(int mode);
extern int far SRand1(int range);

void far DoDrownR(int x, int y, int attr)
{
    int index[1];
    int dir;

    index[0] = (x << 6) + y;
    if (MapR[index[0]] < 0x14) {
        RlistX.m[Tindex] = (unsigned char)GetNewModeR((attr & 0x78) >> 3);
        return;
    }
    dir = SRand1(3) + attr - 1;
    dir &= 7;
    dir |= attr & 0xf8;
    RlistX.t[Tindex] = (unsigned char)dir;
    LifeR[(x << 6) + y] = (unsigned char)dir;
    if (SRand1(100) == 0) {
        LifeR[(x << 6) + y] = 0;
        RlistX.t[Tindex] = 0;
        if (dir & 0x80)
            RAntsExpired++;
        else
            BAntsExpired++;
    }
}
