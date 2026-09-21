/*
 * Reproduce: found a new colony near yard cell (x, y).  The target cell
 * is displaced by two random 0..3 steps and clamped to the 12x16 yard
 * population maps; landing on the same cell does nothing.  For a red
 * colony the far YMapPopR cell (otherwise YMapPopB) gains one colony,
 * and a previously empty cell also counts as a newly started colony for
 * that colour.
 */
extern unsigned char far YMapPopB[12][16];
extern unsigned char far YMapPopR[12][16];
extern int far BColoniesStarted;
extern int far RColoniesStarted;
extern int far SGSRand(int range);

void far Reproduce(int x, int y, int red)
{
    int nx;
    int ny;
    

    nx = SGSRand(4) + x;
    ny = SGSRand(4) + y;
    if (nx < 0)
        nx = 0;
    if (nx > 11)
        nx = 11;
    if (ny < 0)
        ny = 0;
    if (ny > 15)
        ny = 15;
    if (nx == x && ny == y)
        return;
    if (red) {
        struct { unsigned char far *p; } h;
        h.p = &YMapPopR[nx][ny];
        if (*h.p == 0)
            RColoniesStarted++;
        (*h.p)++;
    } else {
        hb.p = &YMapPopB[nx][ny];
        if (*hb.p == 0)
            BColoniesStarted++;
        (*hb.p)++;
    }
}
