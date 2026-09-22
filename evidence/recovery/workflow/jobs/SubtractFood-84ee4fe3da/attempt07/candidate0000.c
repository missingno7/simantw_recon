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
    unsigned char near * volatile cell;
    register int column;
    register int row;

    row = 0;
    while (row < 0x2000) {
        column = 0;
        while (column < 0x40) {
            cell = &MapA[row + column];
            if (IsItFood(*cell) != 1)
                return;
            *cell = (unsigned char)SRand16();
            ++column;
        }
        row += 0x40;
    }
    FoodA = 0;
}
