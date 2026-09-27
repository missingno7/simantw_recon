/* Derived mechanically from the mirrored colony function _LostTailR (tools/mirror_pairs.py):
 * colony-specific MAPSYM identifiers swapped FindInRList->FindInBList, LifeR->LifeB, LostTailR->LostTailB; constants and structure unchanged.
 * Verified only by the strict matcher; where the pair is not a pure mirror the
 * diagnostic names the asymmetry. */
/* LostTailR: same shape as LostTailB (see LostTailB.c), against
 * LifeR/FindInRList. Shares the Dx8/Dy8 delta tables with the black
 * colony. */

extern unsigned char far Dx8[];
extern unsigned char far Dy8[];
extern unsigned char near LifeB[128][64];
extern int far FindInBList(int x, int y, int ant);

#define LifeB ((unsigned char near *)LifeB)
int far LostTailB(int x, int y, int attr)
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
    cell = LifeB[(newX << 6) + newY];
    if (cell == tailMarker)
        return 0;
    if (FindInBList(newX, newY, tailMarker) >= 0)
        return 0;
    return 1;
}
#undef LifeB



