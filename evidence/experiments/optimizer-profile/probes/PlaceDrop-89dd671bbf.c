/*
 * PlaceDrop: put drop number i at a random yard cell.  The far RxTab and
 * RyTab bytes record the column (0..127) and row (0..63); when the MapA
 * cell is open ground (code below 0xe) it becomes the drop code 0x74 and
 * the matching half-resolution scent cells in the Dx8 segment (index
 * (x/2)*32 + y/2, at offsets 0x52d2, 0x5ad2, 0x6ad2 and 0x7ad2) are
 * cleared, while the two trail scents (0x62d2 and 0x72d2) drop by 0x14
 * or to zero.
 */
extern unsigned char near MapA[];
extern unsigned char far Dx8[];
extern unsigned char far RxTab[];
extern unsigned char far RyTab[];
extern int far RRand(int range);

void far PlaceDrop(int i)
{
    int x;
    int y;
    unsigned char near *p;
    int idx;

    x = RRand(128);
    y = RRand(64);
    RxTab[i] = x;
    RyTab[i] = y;
    p = &MapA[(x << 6) + y];
    if (*p < 0xe) {
        *p = 0x74;
        idx = ((x >> 1) << 5) + (y >> 1);
        Dx8[idx + 0x52d2] = 0;
        Dx8[idx + 0x5ad2] = 0;
        if (Dx8[idx + 0x62d2] >= 0x14)
            Dx8[idx + 0x62d2] -= 0x14;
        else
            Dx8[idx + 0x62d2] = 0;
        Dx8[idx + 0x6ad2] = 0;
        if (Dx8[idx + 0x72d2] >= 0x14)
            Dx8[idx + 0x72d2] -= 0x14;
        else
            Dx8[idx + 0x72d2] = 0;
        Dx8[idx + 0x7ad2] = 0;
    }
}
