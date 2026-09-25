/*
 * RaidOutR: a R-colony ant at map cell (x, y) tries to leave on a raid.
 * GetExitDirR(x, y, 8) returns a 1-based exit direction or 0 for none; a
 * zero result is replaced by a random SRand8() direction, otherwise the
 * direction is converted to 0-based.  TryMoveDirR (far, same code group, LINK-translated)
 * is attempted with that direction and, if it fails, once more with a fresh
 * SRand8() direction.  If both moves fail the ant stays: the LifeR cell at
 * x*64 + y (verified near array) is rewritten from the current list
 * record's attribute byte RlistT[Tindex] (both far DGROUP objects via
 * segment-9/segment-8 selector slots, as in DoAntSimB / ClearLifeR).
 */
extern int far GetExitDirR(int x, int y, int limit);
extern int far SRand8(void);
extern int far TryMoveDirR(int x, int y, int dir);
extern int far Tindex;
extern unsigned char far RlistT[];
extern unsigned char near LifeR[];

void far RaidOutR(int x, int y)
{
    int dir;

    dir = GetExitDirR(x, y, 8);
    if (dir == 0)
        dir = SRand8();
    else
        dir--;
    if (TryMoveDirR(x, y, dir) == 0) {
        if (TryMoveDirR(x, y, SRand8()) == 0)
            LifeR[x * 64 + y] = RlistT[Tindex];
    }
}
