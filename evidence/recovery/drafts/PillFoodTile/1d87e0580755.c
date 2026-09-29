extern int far IsValidA(int x, int y);
extern int far PillDir;
extern int far PillarMap[6];
extern unsigned char near MapA[];
void far PillFoodTile(int x, int y)
{
    int row = y;
    int col = x;
    unsigned char near * volatile tile;
    if (IsValidA(col, row) == 1) {
        if (IsValidA(col, row) == 1) {
            if (PillDir & 1)
                MapA[col * 64 + row] = ((unsigned char far *)PillarMap)
                    [2 * (col % 6)];
            else
                MapA[col * 64 + row] = ((unsigned char far *)PillarMap)
                    [2 * (row % 6)];
        }
        tile = &MapA[col * 64 + row];
        if (*tile < 0x18)
            *tile = 0x4b;
    }
}
