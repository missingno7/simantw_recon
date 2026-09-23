/* GetDefendDir: choose a defensive direction for a Blue ant at (x, y)
 * facing dir.  Border tiles reuse the same edge/corner turning logic as
 * the admitted GetRandDir.  On an interior tile MePlane selects the
 * response: MePlane==1 (spider threat) heads toward the spider via
 * GetDir when ChaseSpid is armed, otherwise toward the remembered
 * FuzLocX/FuzLocY spot (or picks a random turn once already within
 * half DefendRadius of it) and returns TurnTab[dir][target] (or dir
 * unchanged if no target); MePlane==2/3 defer to GetNestDir with an
 * extra flag (0/0x80); any other MePlane just keeps going the same
 * direction.
 */
extern int near MePlane;
extern int near SpidX;
extern int near SpidY;
extern int far ChaseSpid;
extern int far FuzLocX;
extern int far FuzLocY;
extern int far DefendRadius;
extern char far TurnTab[][8];
extern int far SRand1(unsigned int range);
extern int far GetDir(int x1, int y1, int x2, int y2);
extern int far GetDis(int x1, int y1, int x2, int y2);
extern int far GetNestDir(int x, int y, int dir, int flag);

int far GetDefendDir(int x, int y, int dir)
{
    int r;

    if (x == 0) {
        if (y == 0)
            r = SRand1(3) + 3;
        else if (y == 63)
            r = SRand1(3) + 1;
        else
            r = SRand1(5) + 1;
    } else if (y == 0) {
        if (x == 127)
            r = SRand1(3) + 5;
        else
            r = SRand1(5) + 3;
    } else if (x == 127) {
        if (y == 63)
            r = SRand1(3) + 7;
        else
            r = SRand1(5) + 5;
    } else if (y == 63)
        r = SRand1(5) + 7;
    else
        r = 0;

    if (r != 0)
        return (unsigned char)r - 1 & 7;

    switch (MePlane) {
    case 1:
        goto chase;
    case 2:
        return GetNestDir(x, y, dir, 0);
    case 3:
        return GetNestDir(x, y, dir, 0x80);
    }
check:
    if (r != 0)
        return TurnTab[dir][r];
    return dir;

chase:
    if (ChaseSpid == 1) {
        r = GetDir(x, y, SpidX >> 4, SpidY >> 4);
    } else {
        r = GetDis(x, y, FuzLocX, FuzLocY);
        if (DefendRadius >> 1 < r)
            r = GetDir(x, y, FuzLocX, FuzLocY);
        else
            r = SRand1(8) + 1;
    }
    goto check;
}
