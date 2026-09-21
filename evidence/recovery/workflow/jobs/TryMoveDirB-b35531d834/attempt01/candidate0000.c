/*
 * TryMoveDirB: attempt to step a black ant at (x,y) along Dx8/Dy8[dir].
 * Returns 0 immediately for dir<0 or an out-of-[0,63] stepped X, or an
 * out-of-range (>63) stepped Y. A stepped Y below 1 instead defers to
 * GetOutB(x) (near call; same-segment far call rewritten by LINK).
 * Otherwise, once the destination cell (MapB[nx*64+ny] < 0x1c) is
 * walkable: if the source cell is still marked free (LifeB==0xff) and
 * MeWantFood is set and this ant's B-list slot (Tindex) is not full
 * (BlistX[Tindex]<0x80), the slot's direction nibble is refreshed and
 * DoTroph(x,y,dir) is invoked. Either way, the B-list slot's direction
 * nibble is (re)written, the ant's tracked position moves from
 * LifeB[x*64+y] to LifeB[nx*64+ny], and BlistX/BlistY record the new
 * (nx,ny); returns 1.
 */
extern char far Dx8[];
extern char far Dy8[];
extern unsigned char near MapB[];
extern unsigned char near LifeB[];
extern int far MeWantFood;
extern int far Tindex;
extern unsigned char far BlistX[];
extern unsigned char far BlistY[];
extern unsigned char far BlistT[];

extern int near GetOutB(int x);
extern void far DoTroph(int x, int y, int dir);

int far TryMoveDirB(int x, int y, int dir)
{
    int nx;
    int ny;
    int cell;
    int origin;
    unsigned char slot;

    if (dir < 0)
        return 0;

    ny = Dy8[dir] + y;
    nx = Dx8[dir] + x;
    if (nx > 0x3f || nx < 0)
        return 0;
    if (ny > 0x3f)
        return 0;
    if (ny < 1)
        return GetOutB(x);

    cell = (nx << 6) + ny;
    if (MapB[cell] >= 0x1c)
        return 0;

    if (LifeB[cell] == 0xff && MeWantFood != 0 && BlistX[Tindex] < 0x80) {
        slot = (BlistT[Tindex] & 0xf8) | (unsigned char)dir;
        origin = (x << 6) + y;
        LifeB[origin] = slot;
        DoTroph(x, y, dir);
    }

    slot = (BlistT[Tindex] & 0xf8) | (unsigned char)dir;
    LifeB[cell] = slot;
    LifeB[(x << 6) + y] = 0;
    BlistX[Tindex] = (unsigned char)nx;
    BlistY[Tindex] = (unsigned char)ny;
    BlistT[Tindex] = LifeB[cell];
    return 1;
}
