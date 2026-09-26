/* LostTailB(x, y, attr) is LostHeadB's tail-side twin: it looks one step
 * in the OPPOSITE direction from attr's low 3 bits (dir = (attr^0xfc)&7,
 * the classic 8-direction reversal: flips only bit2, i.e. dir=(attr&7)^4)
 * through the same shared Dx8[dir]/Dy8[dir] delta tables (Dy8=Dx8+8, first
 * referenced so it gets the first ES slot, matching LostHeadB), and
 * expects tailMarker = attr + 8 (not attr-8) in the neighbour cell.
 * Returns 0 if LifeB[newX][newY]==tailMarker or
 * FindInBList(newX,newY,tailMarker)>=0, else 1.
 *
 * LostTailR is the identical shape against LifeR/FindInRList. Both reuse
 * the LostHeadB/R evidence for the shared delta tables, selector order and
 * FindIn*List calling shape; both are expected to hit the same
 * REGISTER_ALLOCATION residues (headMarker/tailMarker hoisted to the
 * front, and the final (newX<<6)+newY combine shifting the first-computed
 * delta instead of the second/spilled one) that blocked LostHeadB/R. */

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
    newY = x + (signed char)Dy8[dir];
    newX = y + (signed char)Dx8[dir];
    tailMarker = attr + 8;
    cell = LifeB[(newX << 6) + newY];
    if (cell == tailMarker)
        return 0;
    if (FindInBList(newX, newY, tailMarker) >= 0)
        return 0;
    return 1;
}
#undef LifeB

