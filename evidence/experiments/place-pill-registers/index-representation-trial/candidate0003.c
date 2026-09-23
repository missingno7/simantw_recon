extern int far IsValidA(int x, int y);
extern unsigned char near MapA[];
void PlacePillTile(int x, int y, unsigned char value)
{
    int column = x; int row = y;
    if (IsValidA(column, row) == 1) ((unsigned char near *)MapA)[(column << 6) + row] = value;
}
