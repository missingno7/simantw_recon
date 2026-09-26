/* LostHeadR(x, y, attr) checks whether the red ant's expected "head"
 * marker is still present one step away in the direction encoded by the
 * low 3 bits of attr. dir = attr & 7 indexes the two small direction-delta
 * tables that sit at the very start of the shared Dx8 object: Dx8[dir] is
 * the signed X delta, and the immediately following named site Dy8[dir]
 * (Dx8+8, its own MAPSYM name/selector) is the signed Y delta -- both are
 * sign-extended bytes (cbw). newY is computed from Dy8 before newX from
 * Dx8, matching first-reference selector-pool order (Dy8 gets the first ES
 * slot, Dx8 the second). headMarker = attr - 8 is the ant id/head marker
 * expected in the neighbour cell.
 *
 * If LifeR[newX][newY] already equals headMarker, the head is still there
 * (return 0). Otherwise FindInRList(newX, newY, headMarker) does a slower
 * search of the red ant list for that marker; found (>=0) still counts
 * as "not lost" (return 0), only a failed search returns 1 ("lost").
 *
 * LostHeadR is the identical shape against Dx9/Dy9 (see reconstruction:
 * DoNestFightB's scaffold references the pool words Dy8@C364/Dx9@C366
 * immediately after Dx8/Dy8, i.e. Dx9/Dy9 are the red-list's own
 * direction-delta tables) and LifeR/FindInRList. */

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
    newY = (signed char)Dy8[dir];
    newX = x + (signed char)Dx8[dir];
    newY += y;
    headMarker = attr - 8;
    cell = LifeR[(newX << 6) + newY];
    if (cell == headMarker)
        return 0;
    if (FindInRList(newX, newY, headMarker) >= 0)
        return 0;
    return 1;
}
#undef LifeR



