/*
 * Hypothesis: walk the 0x2000-byte MapA in rows of 0x40.  Each byte must be
 * food; accepted bytes are replaced with the low byte of SRand16().  The
 * historical routine stops at the first non-food byte and, after a complete
 * pass, clears the far FoodA word.  MapA and FoodA use the exact symbol-map
 * placements evidenced for the computed DS base and segment-9 object.
 */
extern unsigned char near MapA[];
extern int far FoodA;
extern int far IsItFood(int tile);
extern long far SRand16(void);

void far SubtractFood(void)
{
    register int row;
    register int column;
    unsigned char near *cell;

    for (row = 0; row < 0x2000; row += 0x40) {
        for (column = 0; column < 0x40; ++column) {
            cell = &MapA[row + column];
            if (IsItFood(*cell) != 1)
                return;
            *cell = (unsigned char)SRand16();
        }
    }
    FoodA = 0;
}
