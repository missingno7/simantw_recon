extern int far GetMap(int plane, int x, int y);

int far WallNeighbors(int x, int y, int plane)
{
    int m;
    int w;
    int result;

    result = 0;

    m = GetMap(plane, x - 1, y);
    w = (m >= 0x60 && m <= 0x67);
    if (w == 1)
        result++;
    result *= 2;

    m = GetMap(plane, x, y + 1);
    w = (m >= 0x60 && m <= 0x67);
    if (w == 1)
        result++;
    result *= 2;

    m = GetMap(plane, x + 1, y);
    w = (m >= 0x60 && m <= 0x67);
    if (w == 1)
        result++;
    result *= 2;

    m = GetMap(plane, x, y - 1);
    w = (m >= 0x60 && m <= 0x67);
    if (w == 1)
        result++;

    return result;
}
