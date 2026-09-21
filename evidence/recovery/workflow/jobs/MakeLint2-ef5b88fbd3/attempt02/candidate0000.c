/*
 * Hypothesis: walk the inclusive rectangular MapA region row by row.  Each
 * cell receives a lint value only on the zero result of SRand1(0xc8); the
 * value is the observed two-way random result plus 0x3e.
 */
extern unsigned char near MapA[];
extern int near SRand1(unsigned int range);

void far MakeLint2(int firstRow, int lastRow,
                   int firstColumn, int lastColumn)
{
    int rowBase;
    int rowCount;
    register int column;

    if (lastRow < firstRow)
        return;
    rowBase = firstRow << 6;
    rowCount = lastRow - firstRow + 1;
    column = firstColumn;
    do {
        if (column <= lastColumn) {
            do {
                if (SRand1(0xc8) == 0)
                    MapA[rowBase + column] = SRand1(2) + 0x3e;
                ++column;
            } while (column <= lastColumn);
        }
        rowBase += 0x40;
        --rowCount;
        column = firstColumn;
    } while (rowCount != 0);
}
