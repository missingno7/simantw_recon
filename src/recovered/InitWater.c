extern void far PlaceDrop(int value);

void InitWater(void)
{
    int i;

    for (i = 0; i < 100; ++i)
        PlaceDrop(i);
}
