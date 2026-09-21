extern int far GetMap(int plane, int x, int y);

int far WallNeighbors(int x, int y, int plane)
{
    int result;
    int m;

    result = 0;
    m = GetMap(plane, x - 1, y);
    result = (result + (m >= 0x60 && m <= 0x67)) * 2;
    m = GetMap(plane, x, y + 1);
    result = (result + (m >= 0x60 && m <= 0x67)) * 2;
    m = GetMap(plane, x + 1, y);
    result = (result + (m >= 0x60 && m <= 0x67)) * 2;
    m = GetMap(plane, x, y - 1);
    result = result + (m >= 0x60 && m <= 0x67);

    return result;
}
