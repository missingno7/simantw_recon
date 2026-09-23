extern int far IsValidA(int x, int y);
extern unsigned char near MapA[];
void PlacePillTile(int x, int y, unsigned char value)
{
    if (IsValidA(x, y) == 1) ((unsigned char near *)MapA)[y + (x << 6)] = value;
}
