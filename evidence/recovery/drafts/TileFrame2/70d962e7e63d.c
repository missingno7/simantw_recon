extern unsigned char near MapA[];

void far TileFrame2(int top, int bottom, int left, int right)
{
    int rowBase, columnBase, rowCount, row, column, currentRow, firstTop, lastRow;
    int leftWidth, rightWidth, topWidth, bottomWidth;
    firstTop = top; lastRow = bottom;
    if (firstTop <= lastRow) {
        currentRow = firstTop; rowBase = currentRow << 6; columnBase = left; rowCount = lastRow - currentRow + 1;
        leftWidth = left - left + 1;
        if (rowCount > 0) do {
            column = 0;
            if (leftWidth > 0) do { MapA[rowBase + columnBase + column] = 0x51; } while (++column < leftWidth);
            ++currentRow; rowBase += 0x40;
        } while (--rowCount);
    }
    firstTop = top; lastRow = bottom;
    if (firstTop <= lastRow) {
        currentRow = firstTop; rowBase = currentRow << 6; columnBase = right; rowCount = lastRow - currentRow + 1;
        rightWidth = right - right + 1;
        if (rowCount > 0) do {
            column = 0;
            if (rightWidth > 0) do { MapA[rowBase + columnBase + column] = 0x54; } while (++column < rightWidth);
            ++currentRow; rowBase += 0x40;
        } while (--rowCount);
    }
    if (left <= right) {
        rowBase = firstTop << 6; columnBase = left; rowCount = firstTop - firstTop + 1;
        topWidth = right - left + 1;
        if (rowCount > 0) do {
            column = 0;
            if (topWidth > 0) do { MapA[rowBase + columnBase + column] = 0x5b; } while (++column < topWidth);
            ++currentRow; rowBase += 0x40;
        } while (--rowCount);
        rowBase = lastRow << 6; columnBase = left; rowCount = lastRow - lastRow + 1;
        bottomWidth = right - left + 1;
        if (rowCount > 0) do {
            column = 0;
            if (bottomWidth > 0) do { MapA[rowBase + columnBase + column] = 0x5a; } while (++column < bottomWidth);
            ++currentRow; rowBase += 0x40;
        } while (--rowCount);
    }
    MapA[(firstTop << 6) + left] = 0x56;
    MapA[(lastRow << 6) + left] = 0x58;
    MapA[(firstTop << 6) + right] = 0x57;
    MapA[(lastRow << 6) + right] = 0x59;
}
