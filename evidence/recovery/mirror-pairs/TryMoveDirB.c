/* Derived mechanically from the mirrored colony function _TryMoveDirR (tools/mirror_pairs.py):
 * colony-specific MAPSYM identifiers swapped GetOutR->GetOutB, LifeR->LifeB, MapR->MapB, RlistT->BlistT, RlistX->BlistX, RlistY->BlistY, TryMoveDirR->TryMoveDirB; constants and structure unchanged.
 * Verified only by the strict matcher; where the pair is not a pure mirror the
 * diagnostic names the asymmetry. */
extern signed char far Dy8[];
extern signed char far Dx8[];
extern unsigned char near MapB[];
extern unsigned char near LifeB[];
extern int far Tindex;
extern unsigned char far BlistT[];
extern unsigned char far BlistX[];
extern unsigned char far BlistY[];

extern int far GetOutB(int x);

int far TryMoveDirB(int x, int y, int dir)
{
    int dy, dx, cell;

    if (dir < 0)
        return 0;

    dy = Dy8[dir + 8] + y;
    dx = Dx8[dir] + x;
    if (dx > 0x3f)
        return 0;
    if (dx < 0)
        return 0;
    if (dy > 0x3f)
        return 0;
    if (dy < 1)
        return GetOutB(x);

    cell = dx * 64 + dy;
    if (MapB[cell] >= 0x1c)
        return 0;

    LifeB[cell] = (BlistT[Tindex] & 0xf8) | dir;
    LifeB[x * 64 + y] = 0;
    BlistX[Tindex] = LifeB[cell];
    BlistY[Tindex] = (unsigned char)dy;
    BlistT[Tindex] = LifeB[cell];
    return 1;
}
