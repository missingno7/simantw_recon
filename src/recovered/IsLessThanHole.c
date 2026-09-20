extern int far TERRAINset;

int IsLessThanHole(int value)
{
    int test = value;

    if (TERRAINset == 0 && test < 0x50)
        return 1;
    return test < 0x59;
}
