extern int far TERRAINset;

int IsLessThanHole(int x)
{
    if (!TERRAINset)
        return x < 0x50;
    return x < 0x59;
}
