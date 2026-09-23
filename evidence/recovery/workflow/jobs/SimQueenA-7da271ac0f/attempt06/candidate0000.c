/* SimQueenA: redraw the queen from its A-list row, column, and type. For
 * high queen types, inspect the cell one direction step ahead. A matching
 * type-minus-eight successor or another A-list occupant keeps this queen;
 * otherwise clear its cell and its AlistT entry. */
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) AlistX[];
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) AlistY[];
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) AlistT[];
extern unsigned char far Dx8[];
extern unsigned char far Dy8[];
extern unsigned char near LifeA[128][64];
extern int far FindInAList(int x, int y);

void near SimQueenA(int index)
{
    int y;
    unsigned char type;
    int x;
    int direction;
    int destY;
    int destX;

    y = AlistY[index];
    type = AlistT[index];
    x = AlistX[index];
    LifeA[x][y] = type;

    if ((type & 0x7f) <= 0x67)
        return;

    direction = type & 7;
    destY = y + Dy8[direction];
    destX = x + Dx8[direction];
    if (LifeA[destX][destY] - type == -8)
        return;
    if (FindInAList(destX, destY) >= 0)
        return;

    LifeA[x][y] = 0;
    AlistT[index] = 0;
}
