/* Keep the baseline map idiom; bind the colony counts through their MAPSYM PACK words. */
extern int __based(__segname("PACK")) BColoniesStarted[];
extern int __based(__segname("PACK")) RColoniesStarted[];
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) YMapPopB[192];
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) YMapPopR[192];
extern int far SGSRand(int range);
void far Reproduce(int x, int y, int red)
{
    int nx;
    int ny;
    unsigned char __based(__segname("SIMANT_DATA_GROUP")) *p;
    nx = SGSRand(4) + x;
    ny = SGSRand(4) + y;
    if (nx < 0) nx = 0;
    if (nx > 11) nx = 11;
    if (ny < 0) ny = 0;
    if (ny > 15) ny = 15;
    if (nx == x && ny == y) return;
    if (red) {
        p = &YMapPopR[(nx << 4) + ny];
        if (*p == 0) ++RColoniesStarted[0];
    } else {
        p = &YMapPopB[(nx << 4) + ny];
        if (*p == 0) ++BColoniesStarted[0];
    }
    ++*p;
}
