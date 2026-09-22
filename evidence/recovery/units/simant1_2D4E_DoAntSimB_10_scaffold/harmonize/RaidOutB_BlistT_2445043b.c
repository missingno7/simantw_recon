/*
 * RaidOutB: a B-colony ant at map cell (x, y) tries to leave on a raid.
 * GetExitDirB(x, y, 8) returns a 1-based exit direction or 0 for none; a
 * zero result is replaced by a random SRand8() direction, otherwise the
 * direction is converted to 0-based.  TryMoveDirB (far, same code group, LINK-translated)
 * is attempted with that direction and, if it fails, once more with a fresh
 * SRand8() direction.  If both moves fail the ant stays: the LifeB cell at
 * x*64 + y (verified near array) is rewritten from the current list
 * record's attribute byte BlistT[Tindex] (both far DGROUP objects via
 * segment-9/segment-8 selector slots, as in DoAntSimB / ClearLifeB).
 */
extern int far GetExitDirB(int x, int y, int limit);
extern int far SRand8(void);
extern int far TryMoveDirB(int x, int y, int dir);
extern int far Tindex;
#define BlistT(i) AT((i) + 0x3d18)
extern unsigned char near LifeB[];

void far RaidOutB(int x, int y)
{
    int dir;

    dir = GetExitDirB(x, y, 8);
    if (dir == 0)
        dir = SRand8();
    else
        dir--;
    if (TryMoveDirB(x, y, dir) == 0) {
        if (TryMoveDirB(x, y, SRand8()) == 0)
            LifeB[x * 64 + y] = BlistT[Tindex];
    }
}
