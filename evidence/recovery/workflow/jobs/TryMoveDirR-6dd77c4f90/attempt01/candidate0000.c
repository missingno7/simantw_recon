extern unsigned char far Dy8[];
extern unsigned char far Dx8[];
extern unsigned char near MapR[];
extern unsigned char near LifeR[];
extern int far Tindex;
extern unsigned char far RlistT[];
extern unsigned char far RlistX[];
extern unsigned char far RlistY[];

extern int far GetOutR(int x);

int far TryMoveDirR(int x, int y, int dir)
{
    int nx, ny;
    unsigned char near *cell;
    unsigned char flag;

    if (dir < 0)
        return 0;

    ny = Dy8[dir + 8] + y;
    nx = Dx8[dir] + x;
    if (nx > 0x3f)
        return 0;
    if (nx < 0)
        return 0;
    if (ny > 0x3f)
        return 0;
    if (ny < 1)
        return GetOutR(x);

    cell = &LifeR[nx * 64 + ny];
    if (MapR[nx * 64 + ny] >= 0x1c)
        return 0;

    flag = (RlistT[Tindex] & 0xf8) | dir;
    *cell = flag;
    LifeR[x * 64 + y] = 0;
    RlistX[Tindex] = flag;
    RlistY[Tindex] = (unsigned char)ny;
    RlistT[Tindex] = *cell;
    return 1;
}
