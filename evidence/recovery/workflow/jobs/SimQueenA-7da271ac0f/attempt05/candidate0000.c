/* SimQueenA: redraw the A-list queen in LifeA. For high queen types, use
 * the low three type bits as a direction and read the adjacent destination.
 * If that cell is not the matching queen eight ranks ahead and no A-list
 * entry occupies it, clear this queen's LifeA cell and its AlistT flag. */
extern unsigned char far Dx8[];
extern unsigned char far Dy8[];
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) AlistT[];
extern unsigned char near LifeA[];
extern int far FindInAList(int x, int y);

void near SimQueenA(int index)
{
    int y;
    int x;
    int destY;
    int destX;
    int direction;
    int cell;
    unsigned char type;

    y = Dx8[index + 0x278e] & 0xff;
    type = Dx8[index + 0x2f62];
    x = Dx8[index + 0x23a4];
    LifeA[(x << 6) + y] = type;

    if ((type & 0x7f) <= 0x67)
        return;

    direction = type & 7;
    destY = y + Dy8[direction];
    destX = x + Dx8[direction];
    cell = LifeA[(destX << 6) + destY];
    if (cell - type == -8)
        return;
    if (FindInAList(destX, destY) >= 0)
        return;

    LifeA[(x << 6) + y] = 0;
    AlistT[index] = 0;
}
