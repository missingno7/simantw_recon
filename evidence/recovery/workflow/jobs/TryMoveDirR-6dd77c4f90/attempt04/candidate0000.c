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
    int cell;
    int dy, dx;
    unsigned char flag;
    unsigned char far *rt;

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

    rt = &RlistT[Tindex];
    flag = (*rt & 0xf8) | dir;
    LifeR[cell] = flag;
    LifeR[x * 64 + y] = 0;
    RlistX[Tindex] = flag;
    RlistY[Tindex] = (unsigned char)dy;
    *rt = LifeR[cell];
    return 1;
}
