extern int far IsValidA(int x, int y);
extern unsigned char near MapA[];

void PlacePillTile(register int x, register int y, unsigned char value)
{
    if (IsValidA(x, y) == 1)
        MapA[x * 64 + y] = value;
}
