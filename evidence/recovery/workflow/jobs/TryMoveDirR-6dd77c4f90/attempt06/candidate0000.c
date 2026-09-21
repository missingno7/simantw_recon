extern signed char far Dy8[];
extern unsigned char far Dx8[];
extern unsigned char near MapR[];
extern unsigned char near LifeR[];
extern int far Tindex;

extern int far GetOutR(int x);

int far TryMoveDirR(int x, int y, int dir)
{
    int dy, dx, cell;
    unsigned char flag;

    if (dir < 0)
        return 0;

    dy = Dy8[dir + 8] + y;
    dx = (signed char)Dx8[dir] + x;
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

    flag = (Dx8[Tindex + 0x46e6] & 0xf8) | dir;
    LifeR[cell] = flag;
    LifeR[x * 64 + y] = 0;
    Dx8[Tindex + 0x4104] = (unsigned char)dx;
    Dx8[Tindex + 0x42fa] = (unsigned char)dy;
    Dx8[Tindex + 0x46e6] = LifeR[cell];
    return 1;
}
