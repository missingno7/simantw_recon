/*
 * FloodNestB updates the B-side nest cells in the shared map.  Each row
 * starts at offset three and spans the remaining 0x3d cells.  Values in the
 * flooding band 0x20..0x2d receive the flood increment; low values at or
 * below 0x13 become the full-water marker 0x50.
 */
extern unsigned char near MapB[];

void FloodNestB(void)
{
    int row;
    int cell;
    int value;
    unsigned char near *p;

    for (row = 0; row < 0x1000; row += 0x40) {
        for (cell = 3; cell < 0x40; ++cell) {
            p = MapB + row + cell;
            value = *p;
            if (value >= 0x20 && value <= 0x2d)
                *p += 0x31;
            else if (*p <= 0x13)
                *p = 0x50;
        }
    }
}


