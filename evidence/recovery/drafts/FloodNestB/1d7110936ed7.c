/*
 * FloodNestB visits every B-side nest-map row in 64-byte steps and skips
 * the first three columns. MapB's MAPSYM base is DGROUP:48E8; indexing
 * from its first byte preserves the target's byte-offset walk.
 */
extern unsigned char near MapB[64][64];

void FloodNestB(void)
{
    int row;
    int cell;
    int value;
    unsigned char near *p;

    for (row = 0; row < 0x1000; row += 0x40) {
        for (cell = 3; cell < 0x40; ++cell) {
            p = &MapB[0][0] + row + cell;
            value = *p;
            if (value >= 0x20 && value <= 0x2d)
                *p += 0x31;
            else if (*p <= 0x13)
                *p = 0x50;
        }
    }
}
