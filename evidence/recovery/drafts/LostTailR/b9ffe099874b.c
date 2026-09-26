/* LostTailR: same shape as LostTailB (see LostTailB.c), against
 * LifeR/FindInRList. Shares the Dx8/Dy8 delta tables with the black
 * colony. */

extern unsigned char far Dx8[];
extern unsigned char far Dy8[];
extern unsigned char near LifeR[128][64];
extern int far FindInRList(int x, int y, int ant);

#define LifeR ((unsigned char near *)LifeR)
int far LostTailR(int x, int y, int attr)
{
    int dir;
    int newY;
    int tailMarker;
    int newX;
    unsigned char cell;

    dir = (attr ^ 0xfc) & 7;
    newY = x + (signed char)Dy8[dir];
    newX = y + (signed char)Dx8[dir];
    tailMarker = attr + 8;
    cell = LifeR[(newX << 6) + newY];
    if (cell == tailMarker)
        return 0;
    if (FindInRList(newX, newY, tailMarker) >= 0)
        return 0;
    return 1;
}
#undef LifeR

