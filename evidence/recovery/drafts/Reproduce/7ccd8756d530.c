/* Keep both map-cell far pointers live across each color-counter update. */
extern int __based(__segname("PACK")) BColoniesStarted[];
extern int __based(__segname("PACK")) RColoniesStarted[];
extern unsigned char far YMapPopB[12][16];
extern unsigned char far YMapPopR[12][16];
extern int far SGSRand(int range);
void far Reproduce(int x, int y, int red)
{
    int nx;
    int ny;
    unsigned char far * volatile redCell;
    unsigned char far * volatile blueCell;
    nx = SGSRand(4) + x;
    ny = SGSRand(4) + y;
    if (nx < 0) nx = 0;
    if (nx > 11) nx = 11;
    if (ny < 0) ny = 0;
    if (ny > 15) ny = 15;
    if (nx == x && ny == y) return;
    if (red) {
        redCell = &YMapPopR[nx][ny];
        if (*redCell == 0) ++RColoniesStarted[0];
        ++*redCell;
    } else {
        blueCell = &YMapPopB[nx][ny];
        if (*blueCell == 0) ++BColoniesStarted[0];
        ++*blueCell;
    }
}
