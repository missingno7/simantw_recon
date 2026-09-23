/* GetRedDefendDir: preserve border turns; for RedPlane mode 1, head
 * toward RedLocX/RedLocY when beyond half the defend radius, otherwise
 * choose a random direction. Modes 2 and 3 defer to GetNestDir.
 */
extern int far RedPlane;
extern int far RedLocX;
extern int far RedLocY;
extern int far ModePopR[];
extern char far TurnTab[][8];
extern int far SRand1(unsigned int range);
extern int far GetDir(int x1, int y1, int x2, int y2);
extern int far GetDis(int x1, int y1, int x2, int y2);
extern int far GetNestDir(int x, int y, int dir, int flag);

int far GetRedDefendDir(int x, int y, int dir)
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

    switch (RedPlane) {
    case 1:
        goto chase;
    case 2:
        return GetNestDir(x, y, dir, 0);
    case 3:
        return GetNestDir(x, y, dir, 0x80);
    }
check:
    if (r != 0)
        return ((char far *)TurnTab - 1)[dir * 8 + r];
    return dir;

chase:
    r = GetDis(x, y, RedLocX, RedLocY);
    if (ModePopR[5] >> 1 < r)
        r = GetDir(x, y, RedLocX, RedLocY);
    else
        r = SRand1(8) + 1;
    goto check;
}

