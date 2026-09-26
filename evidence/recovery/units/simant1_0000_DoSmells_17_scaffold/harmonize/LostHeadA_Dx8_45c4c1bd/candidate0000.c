/* LostHeadA: given a dying ant's cell (x,y) and life value, check whether
 * the neighbour cell in the direction encoded by life is already the
 * "lost head" (a corpse marker) or is occupied per FindInAList. */
extern signed char far Dy8[];
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) Dx8;
extern unsigned char near LifeA[];
extern int far FindInAList(int x, int y);

int near LostHeadA(int x, int y, int life)
{
    int index;
    int column;
    int row;

    index = life & 7;
    row = x + Dx8[index];
    column = y + Dy8[index];
    if (LifeA[(row << 6) + column] - life == -8)
        return 0;
    if (FindInAList(row, column) >= 0)
        return 0;
    return 1;
}
