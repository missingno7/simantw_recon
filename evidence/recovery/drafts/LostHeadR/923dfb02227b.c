/* LostHeadR checks the red colony's neighboring cell for the head marker,
 * then searches the red ant list if the direct map cell does not match.
 * Both signed direction deltas come from their separately named Dx8/Dy8
 * tables; Dy8 is already based at its own byte offset. */
extern unsigned char far Dx8[];
extern unsigned char far Dy8[];
extern unsigned char near LifeR[128][64];
extern int far FindInRList(int x, int y, int ant);

#define LifeR ((unsigned char near *)LifeR)
int far LostHeadR(int x, int y, int attr)
{
    int dir;
    int newY;
    int headMarker;
    int newX;
    unsigned char cell;

    dir = attr & 7;
    newY = x + (signed char)Dy8[dir];
    newX = y + (signed char)Dx8[dir];
    headMarker = attr - 8;
    cell = LifeR[(newX << 6) + newY];
    if (cell == headMarker)
        return 0;
    if (FindInRList(newX, newY, headMarker) >= 0)
        return 0;
    return 1;
}
#undef LifeR
