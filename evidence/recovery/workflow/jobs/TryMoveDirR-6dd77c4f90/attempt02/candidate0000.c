extern signed char far Dy8[];
extern signed char far Dx8[];
extern unsigned char near MapR[];
extern unsigned char near LifeR[];
extern int far Tindex;
extern unsigned char far RlistT[];
extern unsigned char far RlistX[];
extern unsigned char far RlistY[];

extern int far GetOutR(int x);

int far TryMoveDirR(int x, int y, int dir)
{
    int dx, dy;
    int cell;
    unsigned char flag;

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

    flag = (RlistT[Tindex] & 0xf8) | dir;
    LifeR[cell] = flag;
    LifeR[x * 64 + y] = 0;
    RlistX[Tindex] = flag;
    RlistY[Tindex] = (unsigned char)dy;
    RlistT[Tindex] = LifeR[cell];
    return 1;
}
