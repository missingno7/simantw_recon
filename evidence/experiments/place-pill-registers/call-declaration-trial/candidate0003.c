extern int far IsValidA();
extern unsigned char near MapA[];
void PlacePillTile(int x, int y, unsigned char value)
{
    int column=x, row=y;
    if (IsValidA(column, row) == 1) MapA[column * 64 + row] = value;
}
