/* LostHeadR: same shape as LostHeadB (see LostHeadB.c for the full
 * template and evidence), against LifeR/FindInRList. Confirmed to share
 * the SAME Dx8/Dy8 direction-delta tables as the black colony (not a
 * separate Dx9/Dy9 pair as the mirror tooling's scaffold guess suggested --
 * both selector slots resolve to segment 8 offset 0/8, exact_mapsym_names
 * _Dy8/_Dx8, identical to LostHeadB). Best candidate reaches 36/41 opcodes;
 * two residual register-allocation/scheduling differences (headMarker
 * computation hoisted to the front of the function, and the final index
 * combine shifting the first-computed delta instead of the
 * second/spilled one) match LostHeadB's blocked evidence exactly. */

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
    headMarker = attr - 8;
    newX = y + (signed char)Dx8[dir];
    cell = LifeR[(newX << 6) + newY];
    if (cell == headMarker)
        return 0;
    if (FindInRList(newX, newY, headMarker) >= 0)
        return 0;
    return 1;
}
#undef LifeR
