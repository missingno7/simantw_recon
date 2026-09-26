/*
 * Hypothesis: fill the inclusive MapA rectangle with the requested terrain,
 * sprinkle occasional leg pixels, then mark each 4 by 4 corner as 0xC0.
 * MapA is the adjacent public at DGROUP 0x28E8 in this SIMONE unit.
 */
extern unsigned char near MapA[];
extern int far SRand1(int range);

void far FillMapLegs(int firstRow, int lastRow,
                     int firstColumn, int lastColumn,
                     unsigned char fillValue)
{
    int rowOffset;
    int rowCount;
    int columnStart;
    int columnCount;
    int row;
    int column;
    int run;
    unsigned char near *dst;
    unsigned char near *end;

    if (firstRow <= lastRow) {
        rowOffset = firstRow << 6;
        columnStart = firstColumn;
        columnCount = lastColumn - firstColumn + 1;
        rowCount = lastRow - firstRow + 1;
        if (firstColumn <= lastColumn)
            for (row = 0; row < rowCount; ++row) {
                memset(&MapA[rowOffset + columnStart], fillValue, columnCount);
                rowOffset += 0x40;
            }
    }

    if (firstRow <= lastRow) {
        rowOffset = firstRow << 6;
        rowCount = lastRow - firstRow + 1;
        rowOffset += 0;
        for (row = 0; row < rowCount; ++row) {
            for (column = firstColumn; column <= lastColumn; ++column) {
                if (SRand1(20) == 0)
                    MapA[rowOffset + column] = (unsigned char)(SRand1(5) + 0x38);
            }
            rowOffset += 0x40;
        }
    }

    if (firstRow + 3 >= firstRow && firstColumn + 3 >= firstColumn) {
        rowOffset = firstRow << 6;
        rowCount = 4;
        do {
            for (column = firstColumn; column <= firstColumn + 3; ++column)
                MapA[rowOffset + column] = 0xC0;
            rowOffset += 0x40;
        } while (--rowCount);
    }

    if (lastRow - 3 <= lastRow && firstColumn + 3 >= firstColumn) {
        rowOffset = (lastRow - 3) << 6;
        rowCount = 4;
        do {
            for (column = firstColumn; column <= firstColumn + 3; ++column)
                MapA[rowOffset + column] = 0xC0;
            rowOffset += 0x40;
        } while (--rowCount);
    }

    if (firstRow + 3 >= firstRow && lastColumn - 3 <= lastColumn) {
        rowOffset = firstRow << 6;
        rowCount = 4;
        do {
            for (column = lastColumn - 3; column <= lastColumn; ++column)
                MapA[rowOffset + column] = 0xC0;
            rowOffset += 0x40;
        } while (--rowCount);
    }

    if (lastRow - 3 <= lastRow && lastColumn - 3 <= lastColumn) {
        rowOffset = (lastRow - 3) << 6;
        rowCount = 4;
        do {
            for (column = lastColumn - 3; column <= lastColumn; ++column)
                MapA[rowOffset + column] = 0xC0;
            rowOffset += 0x40;
        } while (--rowCount);
    }
}
