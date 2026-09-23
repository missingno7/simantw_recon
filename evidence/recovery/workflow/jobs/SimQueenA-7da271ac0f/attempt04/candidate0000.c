/* SimQueenA: copy this A-list queen's type into its LifeA cell. For queen
 * types above 0x67 (ignoring the colour bit), use its eight-way direction
 * to find the destination cell. If that cell is not the same queen moving
 * by eight ranks and no A-list entry already occupies it, remove this
 * queen by clearing the source cell and its AlistT flag. */
extern unsigned char far Dx8[];
extern unsigned char far Dy8[];
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) AlistX[];
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) AlistY[];
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) AlistT[];
extern unsigned char near LifeA[];
extern int far FindInAList(int x, int y);

void near SimQueenA(int index)
{
    int x;
    int y;
    int direction;
    int newX;
    int newY;
    int cell;
    unsigned char type;

    x = AlistX[index];
    y = AlistY[index];
    type = AlistT[index];
    LifeA[(x << 6) + y] = type;

    if ((type & 0x7f) <= 0x67)
        return;

    direction = type & 7;
    newY = y + Dy8[direction];
    newX = x + Dx8[direction];
    cell = LifeA[(newX << 6) + newY];
    if (cell - type == -8)
        return;
    if (FindInAList(newX, newY) >= 0)
        return;

    LifeA[(x << 6) + y] = 0;
    AlistT[index] = 0;
}
