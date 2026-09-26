int far RallocFindMem(int seed)
{
    int i;
    int x = seed;
    int y = 1;
    for (i = 0; i < 4; ++i) {
        x = x + i;
        y = y + x;
    }
    return x + y;
}
