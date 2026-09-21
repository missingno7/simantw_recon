extern signed char far Dx8[];
extern signed char far Dy8[];
extern unsigned char near LifeA[];
extern int far FindInAList(int x, int y);

int near LostHeadA(int y, int x, int life)
{
    int index;

    index = life & 7;
    y += Dy8[index];
    x += Dx8[index];
    if (LifeA[(x << 6) + y] - life == -8)
        return 0;
    if (FindInAList(y, x) >= 0)
        return 0;
    return 1;
}
