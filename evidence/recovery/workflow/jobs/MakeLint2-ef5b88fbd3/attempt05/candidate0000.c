/*
 * Hypothesis: walk the inclusive rectangular MapA region row by row.  Each
 * cell receives a lint value only on the zero result of SRand1(0xc8); the
 * value is the observed two-way random result plus 0x3e.
 *
 * ABI-only replay: the two verified SRand1 callers cited in the reissue
 * evidence declare this cross-routine entry far, and the target's two
 * same-segment PUSH CS/CALL sequences are consistent with LINK lowering a
 * far call. The earlier four candidates all declared SRand1 near.
 */
extern unsigned char near MapA[];
extern int far SRand1(unsigned int range);

void far MakeLint2(int firstRow, int lastRow,
                   int firstColumn, int lastColumn)
{
    struct LintState {
        int rowBase;
        int rowCount;
    } state;
    register int column;

    if (firstRow <= lastRow) {
        state.rowBase = firstRow << 6;
        state.rowCount = lastRow - firstRow + 1;
        column = firstColumn;
        do {
            if (column <= lastColumn) {
                do {
                    if (SRand1(0xc8) == 0)
                        MapA[state.rowBase + column] = SRand1(2) + 0x3e;
                    ++column;
                } while (column <= lastColumn);
            }
            state.rowBase += 0x40;
            --state.rowCount;
            column = firstColumn;
        } while (state.rowCount != 0);
    }
}
