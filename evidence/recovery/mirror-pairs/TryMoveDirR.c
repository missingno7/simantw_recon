/* Derived mechanically from the mirrored colony function _TryMoveDirB (tools/mirror_pairs.py):
 * colony-specific MAPSYM identifiers swapped BlistT->RlistT, BlistX->RlistX, BlistY->RlistY, GetOutB->GetOutR, LifeB->LifeR, MapB->MapR, TryMoveDirB->TryMoveDirR; constants and structure unchanged.
 * Verified only by the strict matcher; where the pair is not a pure mirror the
 * diagnostic names the asymmetry. */
/*
 * TryMoveDirB: attempt to step a black ant at (x,y) along Dx8/Dy8[dir].
 * Returns 0 immediately for dir<0 or an out-of-[0,63] stepped X, or an
 * out-of-range (>63) stepped Y. A stepped Y below 1 instead defers to
 * GetOutB(x) (far call; same-segment far call rewritten by LINK).
 * Otherwise, once the destination cell (MapB[nx*64+ny] < 0x1c) is
 * walkable: if the source cell is still marked free (LifeB==0xff) and
 * MeWantFood is set and this ant's B-list slot (Tindex) is not full
 * (Dx8[Tindex+0x3736]<0x80), the slot's direction nibble is refreshed and
 * DoTroph(x,y,dir) is invoked. Either way, the B-list slot's direction
 * nibble is (re)written, the ant's tracked position moves from
 * LifeB[x*64+y] to LifeB[nx*64+ny], and BlistX/BlistY record the new
 * (nx,ny); returns 1.
 */
extern char far Dx8[];
extern char far Dy8[];
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) RlistX[];
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) RlistY[];
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) RlistT[];
extern unsigned char near MapR[];
extern unsigned char near LifeR[];
extern int far MeWantFood;
extern int far Tindex;

extern int near GetOutR(int x);
extern void far DoTroph(int x, int y, int dir);

int far TryMoveDirR(int x, int y, int dir)
{
    int dy;
    int dx;
    struct { int value; } cell;

    if (dir < 0) return 0;
    dy = Dy8[dir] + y;
    dx = Dx8[dir] + x;
    if (dx > 0x3f) return 0;
    if (dx < 0) return 0;
    if (dy > 0x3f) return 0;
    if (dy < 1) return GetOutR(x);
    cell.value = (dx << 6) + dy;
    if (MapR[cell.value] >= 0x1c) return 0;
    if (LifeR[cell.value] == 0xff && MeWantFood != 0 && RlistX[Tindex] < 0x80) {
        LifeR[(x << 6) + y] = (RlistT[Tindex] & 0xf8) | (unsigned char)dir;
        DoTroph(x, y, dir);
    }
    LifeR[cell.value] = (RlistT[Tindex] & 0xf8) | (unsigned char)dir;
    LifeR[(x << 6) + y] = 0;
    RlistX[Tindex] = (unsigned char)dx;
    RlistY[Tindex] = (unsigned char)dy;
    RlistT[Tindex] = LifeR[cell.value];
    return 1;
}



