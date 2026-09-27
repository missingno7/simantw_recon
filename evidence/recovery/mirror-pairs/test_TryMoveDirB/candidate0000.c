/* Derived mechanically from the mirrored colony function _TryMoveDirR (tools/mirror_pairs.py):
 * colony-specific MAPSYM identifiers swapped GetOutR->GetOutB, LifeR->LifeB, MapR->MapB, RlistX->BlistX, TryMoveDirR->TryMoveDirB; constants and structure unchanged.
 * Verified only by the strict matcher; where the pair is not a pure mirror the
 * diagnostic names the asymmetry. */
struct RListPlanes {
    unsigned char x[502];
    unsigned char y[502];
    unsigned char m[502];
    unsigned char t[502];
    unsigned char s[502];
};
extern struct RListPlanes far BlistX;
extern signed char far Dy8[];
extern signed char far Dx8[];
extern unsigned char near MapB[];
extern unsigned char near LifeB[];
extern int far Tindex;




extern int near GetOutB(int x);

/* Keep the signed direction guard; a negative direction exits, while zero and positive directions read the red displacement tables. The target reaches its local GetOutR path with a direct same-segment near call. */
int far TryMoveDirB(int x, int y, int dir)
{
    int dy, dx;
    volatile int cell;

    if (dir < 0)
        return 0;

    dy = Dy8[dir] + y;
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

    LifeB[cell] = (BlistX.t[Tindex] & 0xf8) | dir;
    LifeB[x * 64 + y] = 0;
    BlistX.x[Tindex] = LifeB[cell];
    BlistX.y[Tindex] = (unsigned char)dy;
    BlistX.t[Tindex] = LifeB[cell];
    return 1;
}


