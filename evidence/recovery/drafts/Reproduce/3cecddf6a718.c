extern int __based(__segname("PACK")) BColoniesStarted[];
extern int __based(__segname("PACK")) RColoniesStarted[];
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) YMapPopB[192];
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) YMapPopR[192];
extern int far SGSRand(int range);
void far Reproduce(int x, int y, int red)
{
    int nx;
    int ny;
    unsigned char far *pRed;
    unsigned char far *pBlue;
    nx = SGSRand(4) + x;
    ny = SGSRand(4) + y;
    if (nx < 0) nx = 0;
    if (nx > 11) nx = 11;
    if (ny < 0) ny = 0;
    if (ny > 15) ny = 15;
    if (nx == x && ny == y) return;
    if (red) {
        pRed = (unsigned char far *)&YMapPopR[(nx << 4) + ny];
        if (*pRed == 0) ++RColoniesStarted[0];
    } else {
        pBlue = (unsigned char far *)&YMapPopB[(nx << 4) + ny];
        if (*pBlue == 0) ++BColoniesStarted[0];
    }
    if (red) ++*pRed;
    else ++*pBlue;
}
