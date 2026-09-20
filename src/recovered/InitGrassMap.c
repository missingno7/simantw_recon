extern int far GrassMap[];

void InitGrassMap(void)
{
    int i;

    GrassMap[0] = 0;
    GrassMap[1] = 0;
    GrassMap[2] = 0;
    for (i = 0; i < 9; ++i)
        GrassMap[i + 3] = -1;
}
