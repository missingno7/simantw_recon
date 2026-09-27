extern int far TERRAINset;

int IsNotBarrier(int x)
{
    if (!TERRAINset)
        return x <= 0x50;
    return x <= 0x5f;
}
