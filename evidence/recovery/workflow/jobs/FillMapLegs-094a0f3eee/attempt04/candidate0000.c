/* Fill the MapA patch, add sparse random terrain, and stamp its four legs. */
extern void near *memset(void near *destination, int value, unsigned int count);
extern unsigned char near MapA[];
extern int far SRand1(int range);

void far FillMapLegs(int firstRow, int lastRow,
                     int firstColumn, int lastColumn,
                     unsigned char fillValue)
{
    int rowOffset;
    int columnStart;
    int rowCount;
    int randomStart;
    int width;
    int run;
    int bottomRow;
    int rightColumn;
    int row;
    int column;

    if (firstRow > lastRow)
        return;
    rowOffset = firstRow << 6;
    columnStart = firstColumn;
    width = lastColumn - columnStart + 1;
    rowCount = lastRow - firstRow + 1;
    if (lastColumn >= columnStart) {
        do {
            memset(MapA + rowOffset + columnStart, fillValue, width);
            rowOffset += 0x40;
        } while (--rowCount);
    }

    rowOffset = firstRow << 6;
    randomStart = firstRow;
    rowCount = lastRow - firstRow + 1;
    for (row = 0; row < rowCount; ++row) {
        for (column = firstColumn; column <= lastColumn; ++column) {
            if (SRand1(20) == 0)
                MapA[rowOffset + column] = (unsigned char)(SRand1(5) + 0x38);
        }
        rowOffset += 0x40;
    }

    if (firstRow + 3 < firstRow || firstColumn + 3 < firstColumn)
        goto bottom_left;
    rowOffset = firstRow << 6;
    run = 4;
    rowCount = 4;
    do {
        memset(MapA + rowOffset + firstColumn, 0xC0, run);
        rowOffset += 0x40;
    } while (--rowCount);

bottom_left:
    if (lastRow - 3 > lastRow || firstColumn + 3 < firstColumn)
        goto top_right;
    bottomRow = lastRow - 3;
    rowOffset = bottomRow << 6;
    run = 4;
    rowCount = 4;
    do {
        memset(MapA + rowOffset + firstColumn, 0xC0, run);
        rowOffset += 0x40;
    } while (--rowCount);

top_right:
    if (firstRow + 3 < firstRow || lastColumn - 3 > lastColumn)
        goto bottom_right;
    rowOffset = firstRow << 6;
    rightColumn = lastColumn - 3;
    run = 4;
    rowCount = 4;
    do {
        memset(MapA + rowOffset + rightColumn, 0xC0, run);
        rowOffset += 0x40;
    } while (--rowCount);

bottom_right:
    if (lastRow - 3 > lastRow || lastColumn - 3 > lastColumn)
        return;
    bottomRow = lastRow - 3;
    rowOffset = bottomRow << 6;
    rightColumn = lastColumn - 3;
    run = 4;
    rowCount = 4;
    do {
        memset(MapA + rowOffset + rightColumn, 0xC0, run);
        rowOffset += 0x40;
    } while (--rowCount);
}
