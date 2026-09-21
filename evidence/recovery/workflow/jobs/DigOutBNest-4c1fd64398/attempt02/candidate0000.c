/*
 * DigOutBNest: dig out the black nest entrance tunnel.
 *
 * The nest's fixed surface entry tile (x=0x20, y=1) is dug immediately
 * (DigTileB).  If count is nonzero the tunnel then random-walks: each
 * step picks a new octant direction near the previous one (SRand1(5)
 * biased by dir, folded into 0..7 via -3 & 7), steps one Dx8/Dy8 cell,
 * and clamps the candidate cell to the playable yard interior [1,0x3e].
 * Clamping on X forces the next direction toward 2 (east) or 6 (west);
 * clamping on Y overrides that with 4 (south) or 0 (north).  The step
 * is committed only when DigTileThemB (claim/dig the neighbour's tile)
 * reports success (1); on success, once the tunnel reaches the surface
 * row (y==1) a surface hole is opened at that column if HoleMapB does
 * not already have one there (MakeNewHoleB).  The walk repeats until
 * count reaches zero, whether or not each individual step succeeded.
 */
extern char far Dx8[];
extern char far Dy8[];
extern unsigned char far HoleMapB[];

extern void far DigTileB(int x, int y);
extern int far DigTileThemB(int x, int y);
extern void far MakeNewHoleB(int x);
extern int far SRand1(int range);

void far DigOutBNest(int count)
{
    int dir, x, y, newX, newY, carry;

    dir = 4;
    y = 1;
    x = 0x20;
    DigTileB(x, y);
    if (count == 0)
        return;
    for (;;) {
        dir = (SRand1(5) + dir - 3) & 7;
        newX = x + Dx8[dir];
        newY = y + Dy8[dir];
        if (newX < 1) {
            newX = 1;
            dir = 2;
        } else if (newX > 0x3e) {
            newX = 0x3e;
            dir = 6;
        }
        if (newY < 2) {
            carry = 4;
            newY = 1;
        } else {
            carry = dir;
            if (newY > 0x3e) {
                newY = 0x3e;
                carry = 0;
            }
        }
        if (DigTileThemB(newX, newY) == 1) {
            x = newX;
            y = newY;
            if (y == 1 && HoleMapB[x] == 0)
                MakeNewHoleB(x);
        }
        if (--count == 0)
            break;
        dir = carry;
    }
}
