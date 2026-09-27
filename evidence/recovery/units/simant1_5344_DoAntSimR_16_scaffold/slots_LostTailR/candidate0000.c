extern char far Dx8[];
extern char far Dy8[];
extern unsigned char near LifeR[];
extern int far FindInRList(int x, int y, int ant);

int far LostTailR(int x, int y, int attr)
{
    int dir;
    int newY;
    int tailMarker;
    int newX;
    unsigned char cell;

    dir = (attr ^ 0xfc) & 7;
    newY = (signed char)Dy8[dir];
    newX = x + (signed char)Dx8[dir];
    newY += y;
    tailMarker = attr + 8;
    cell = ((unsigned char near *)LifeR)[(newX << 6) + newY];
    if (cell == tailMarker)
        return 0;
    if (FindInRList(newX, newY, tailMarker) >= 0)
        return 0;
    return 1;
}




