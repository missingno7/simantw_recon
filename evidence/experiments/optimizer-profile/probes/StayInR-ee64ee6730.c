/*
 * StayInR: an R-colony ant at map cell (x, y) forages or wanders nearby,
 * given a direction hint dirHint.  If MapR[(x<<6)+y] is a food-pile tile
 * (0x10..0x13): a full pile (0x10) is replaced by a fresh SRand8() pile
 * value, otherwise the pile is decremented by one; FoodR is decremented
 * if positive; the current Dx8 list record (Tindex-indexed) gets mode 3
 * and bit 8 set in its type field, and the call falls straight through
 * to the shared LifeR refresh below (no movement is attempted).
 * Otherwise: a jittered direction (SRand1(3)+dirHint-2)&7 is folded into
 * the type field's low 3 bits (high bits/colour preserved) *before* the
 * move is attempted; TryMoveDirR(x,y,dir) success returns immediately
 * without refreshing LifeR.  On failure, GetEnterDirR(x,y,dirHint&7)
 * picks a direction (or, if negative, a fresh SRand1(8) one) and
 * TryMoveDirR is retried; success again returns immediately.  Only when
 * both attempts fail (or the food-tile branch was taken) does LifeR get
 * refreshed from the record's current type field.  TryMoveDirR is
 * same-code-group (LINK-translated near call), matching RaidInR/DoRandR.
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

void far StayInR(int x, int y, int dirHint)
{
    int index;
    int dir;

    index = (x << 6) + y;
    if (MapR[index] >= 0x10 && MapR[index] <= 0x13) {
        if (MapR[index] == 0x10)
            MapR[index] = (unsigned char)SRand8();
        else
            MapR[index]--;
        if (FoodR > 0)
            FoodR--;
        Dx8[Tindex + 0x44f0] = 3;
        Dx8[Tindex + 0x46e6] |= 8;
    } else {
        dir = (SRand1(3) + dirHint - 2) & 7;
        Dx8[Tindex + 0x46e6] = (Dx8[Tindex + 0x46e6] & 0xf8) | dir;
        if (TryMoveDirR(x, y, dir) != 0)
            return;

        dir = GetEnterDirR(x, y, dirHint & 7);
        if (dir < 0)
            dir = SRand1(8);
        if (TryMoveDirR(x, y, dir) != 0)
            return;
    }

    LifeR[index] = Dx8[Tindex + 0x46e6];
}
