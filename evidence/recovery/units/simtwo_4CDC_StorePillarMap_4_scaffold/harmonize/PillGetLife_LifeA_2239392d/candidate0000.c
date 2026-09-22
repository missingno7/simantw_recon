extern int far IsValidA(int x, int y);
extern unsigned char near LifeA[128][64];

int PillGetLife(int x, int y)
{
    if (!IsValidA(x, y))
        return;
    return LifeA[x * 64 + y];
}
