extern int far IsValidA(int x, int y);
extern unsigned char near MapA[];

void PlacePillTile(int x, int y, unsigned char value)
{
    register int column = x;
    register int row = y;
    if (IsValidA(column, row) == 1)
        MapA[column * 64 + row] = value;
}
