extern int far IsValidA(int x, int y);
extern unsigned char near MapA[];

/* Model a promoted value parameter and narrow only at the byte store. */
void PlacePillTile(int x, int y, int value)
{
    if (IsValidA(x, y) == 1)
        MapA[x * 64 + y] = (unsigned char)value;
}
