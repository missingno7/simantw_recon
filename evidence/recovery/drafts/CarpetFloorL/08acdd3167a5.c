/*
 * CarpetFloorL: lay out the indoor (L) terrain.  The near MapA yard is
 * filled row by row (64 bytes per row): rows 0..20 with tile 0x64, row
 * 21 with 0x7a, rows 22..23 with 0x7b and rows 23..127 with 0x03; each
 * row fill is a 64-byte memset.  Then every cell of rows 23..127 has a
 * 1-in-200 chance of becoming tile 0x3e or 0x3f.  Finally a horizontal
 * outlet is made at (2, 25) and DROPdir is set to 1.
 */
extern unsigned char near MapA[128][64];
extern int far DROPdir;

extern int far SRand1(int range);
extern void far MakeOutletH(int x, int y);
extern void far *far memset(void far *dest, int value, unsigned count);

void far CarpetFloorL(void)
{
    unsigned char near *row;
    int off;
    int i;

    for (row = MapA[0]; row <= MapA[20]; row += 64)
        memset(row, 0x64, 64);
    for (row = MapA[21]; row <= MapA[21]; row += 64)
        memset(row, 0x7a, 64);
    for (row = MapA[22]; row <= MapA[23]; row += 64)
        memset(row, 0x7b, 64);
    for (row = MapA[23]; row <= MapA[127]; row += 64)
        memset(row, 0x03, 64);
    for (off = 23 * 64; off <= 127 * 64; off += 64) {
        for (i = 0; i <= 63; i++) {
            if (SRand1(200) == 0)
                MapA[0][off + i] = SRand1(2) + 0x3e;
        }
    }
    MakeOutletH(2, 25);
    DROPdir = 1;
}
