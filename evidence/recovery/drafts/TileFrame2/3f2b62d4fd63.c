/*
 * TileFrame2(top, bottom, left, right): second frame-border variant, byte-
 * identical in size and structure to the accepted-shape TileFrame1 sibling
 * (build/grind/agentW/TileFrame1.c, MATCH_BLOCKED) with different tile
 * codes: left edge column (rows top..bottom) = 0x51, right edge column =
 * 0x54, top edge row (columns left..right) = 0x5b, bottom edge row = 0x5a,
 * each guarded the same way, and corners (top,left)=0x56,
 * (bottom,left)=0x58, (top,right)=0x57, (bottom,right)=0x59. MapA is
 * reused verbatim from the admitted MakePlugH/MakePlugV/MakeKnob/
 * MakePenny/MakeClip family in this same unit (simone:3120).
 */
extern unsigned char near MapA[];

void far TileFrame2(int top, int bottom, int left, int right)
{
    int row, col, firstRow, lastRow, firstCol, lastCol;
    firstRow = top; lastRow = bottom; firstCol = left; lastCol = right;
    for (row = firstRow; row <= lastRow; ++row)
        for (col = firstCol; col <= firstCol; ++col) MapA[(row << 6) + col] = 0x51;
    for (row = firstRow; row <= lastRow; ++row)
        for (col = lastCol; col <= lastCol; ++col) MapA[(row << 6) + col] = 0x54;
    for (row = firstRow; row <= firstRow; ++row)
        for (col = firstCol; col <= lastCol; ++col) MapA[(row << 6) + col] = 0x5b;
    for (row = lastRow; row <= lastRow; ++row)
        for (col = firstCol; col <= lastCol; ++col) MapA[(row << 6) + col] = 0x5a;
    MapA[(firstRow << 6) + firstCol] = 0x56;
    MapA[(lastRow << 6) + firstCol] = 0x58;
    MapA[(firstRow << 6) + lastCol] = 0x57;
    MapA[(lastRow << 6) + lastCol] = 0x59;
}
