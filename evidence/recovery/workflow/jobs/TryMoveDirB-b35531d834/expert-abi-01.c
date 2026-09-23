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
extern unsigned char near MapB[];
extern unsigned char near LifeB[];
extern int far MeWantFood;
extern int far Tindex;

extern int far GetOutB(int x);
extern void far DoTroph(int x, int y, int dir);

int far TryMoveDirB(int x, int y, int dir)
{
    int dy;
    int dx;
    int cell;

    if (dir >= 0) {
        dy = Dy8[dir] + y;
        dx = Dx8[dir] + x;
        if (dx <= 0x3f && dx >= 0 && dy <= 0x3f) {
            if (dy < 1)
                return GetOutB(x);

            cell = (dx << 6) + dy;
            if (MapB[cell] < 0x1c) {
                if (LifeB[cell] == 0xff && MeWantFood != 0 && ((unsigned char far *)Dx8)[Tindex + 0x3736] < 0x80) {
                    LifeB[(x << 6) + y] = (((unsigned char far *)Dx8)[Tindex + 0x3d18] & 0xf8) | (unsigned char)dir;
                    DoTroph(x, y, dir);
                }

                LifeB[cell] = (((unsigned char far *)Dx8)[Tindex + 0x3d18] & 0xf8) | (unsigned char)dir;
                LifeB[(x << 6) + y] = 0;
                ((unsigned char far *)Dx8)[Tindex + 0x3736] = (unsigned char)dx;
                ((unsigned char far *)Dx8)[Tindex + 0x392c] = (unsigned char)dy;
                ((unsigned char far *)Dx8)[Tindex + 0x3d18] = LifeB[cell];
                return 1;
            }
        }
    }
    return 0;
}

