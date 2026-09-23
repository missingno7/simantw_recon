/*
 * Fill the MapA rectangle, sprinkle randomized cells, then stamp the four
 * corners. The target uses byte runs for the solid fills and SRand1 for
 * occasional terrain values.
 */
extern unsigned char near MapA[];
extern int far SRand1(int range);

void far FillMapLegs(int firstRow, int lastRow,
                     int firstColumn, int lastColumn,
                     unsigned char fillValue)
{
    int rowOffset;
    int columnStart;
    int height;
    int randomHeight;
    int width;
    int four;
    int bottomRow;
    int rightColumn;
    int row;
    int column;
    unsigned char near *destination;

    if (firstRow <= lastRow) {
        rowOffset = firstRow << 6;
        columnStart = firstColumn;
        width = lastColumn - columnStart + 1;
        height = lastRow - firstRow + 1;
        if (lastColumn >= columnStart) {
            do {
                destination = MapA + rowOffset + columnStart;
                for (column = 0; column < width; ++column)
                    *destination++ = fillValue;
                rowOffset += 0x40;
            } while (--height);
        }
    }

    if (firstRow <= lastRow) {
        rowOffset = firstRow << 6;
        randomHeight = lastRow - firstRow + 1;
        for (row = 0; row < randomHeight; ++row) {
            for (column = firstColumn; column <= lastColumn; ++column) {
                if (SRand1(20) == 0)
                    MapA[rowOffset + column] = (unsigned char)(SRand1(5) + 0x38);
            }
            rowOffset += 0x40;
        }
    }

    if (firstRow + 3 >= firstRow && firstColumn + 3 >= firstColumn) {
        rowOffset = firstRow << 6;
        four = 4;
        height = 4;
        do {
            destination = MapA + rowOffset + firstColumn;
            for (column = 0; column < four; ++column)
                *destination++ = 0xC0;
            rowOffset += 0x40;
        } while (--height);
    }

    if (lastRow - 3 <= lastRow && firstColumn + 3 >= firstColumn) {
        bottomRow = lastRow - 3;
        rowOffset = bottomRow << 6;
        four = 4;
        height = 4;
        do {
            destination = MapA + rowOffset + firstColumn;
            for (column = 0; column < four; ++column)
                *destination++ = 0xC0;
            rowOffset += 0x40;
        } while (--height);
    }

    if (firstRow + 3 >= firstRow && lastColumn - 3 <= lastColumn) {
        rowOffset = firstRow << 6;
        rightColumn = lastColumn - 3;
        four = 4;
        height = 4;
        do {
            destination = MapA + rowOffset + rightColumn;
            for (column = 0; column < four; ++column)
                *destination++ = 0xC0;
            rowOffset += 0x40;
        } while (--height);
    }

    if (lastRow - 3 <= lastRow && lastColumn - 3 <= lastColumn) {
        bottomRow = lastRow - 3;
        rowOffset = bottomRow << 6;
        rightColumn = lastColumn - 3;
        four = 4;
        height = 4;
        do {
            destination = MapA + rowOffset + rightColumn;
            for (column = 0; column < four; ++column)
                *destination++ = 0xC0;
            rowOffset += 0x40;
        } while (--height);
    }
}
