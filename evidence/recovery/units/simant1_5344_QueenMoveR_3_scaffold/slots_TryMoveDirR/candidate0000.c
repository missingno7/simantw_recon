extern signed char far Dy8[];
extern signed char far Dx8[];
extern unsigned char near MapR[];
extern unsigned char near LifeR[];
extern int far Tindex;
extern unsigned char far RlistT[];
extern unsigned char far RlistX[];
extern unsigned char far RlistY[];

extern int near GetOutR(int x);

/* Keep the signed direction guard; a negative direction exits, while zero and positive directions read the red displacement tables. The target reaches its local GetOutR path with a direct same-segment near call. */
int far TryMoveDirR(int x, int y, int dir)
{
    int dy, dx, cell;

    if (dir < 0)
        return 0;

    dy = Dy8[dir + 8] + y;
    dx = Dx8[dir] + x;
    if (dx > 0x3f)
        return 0;
    if (dx < 0)
        return 0;
    if (dy > 0x3f)
        return 0;
    if (dy < 1)
        return GetOutR(x);

    cell = dx * 64 + dy;
    if (MapR[cell] >= 0x1c)
        return 0;

    LifeR[cell] = (RlistT[Tindex] & 0xf8) | dir;
    LifeR[x * 64 + y] = 0;
    RlistX[Tindex] = LifeR[cell];
    RlistY[Tindex] = (unsigned char)dy;
    RlistT[Tindex] = LifeR[cell];
    return 1;
}


