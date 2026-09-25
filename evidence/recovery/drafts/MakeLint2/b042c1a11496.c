/*
 * MakeLint2 fills the inclusive rectangle in MapA. For each cell, a zero
 * result from SRand1(0xc8) enables a second SRand1(2) draw and stores the
 * resulting lint byte (draw+0x3e). Even an empty column range still advances
 * across every requested row.
 */
extern unsigned char near MapA[];
extern int near SRand1(unsigned int range);

void far MakeLint2(int firstRow, int lastRow,
                   int firstColumn, int lastColumn)
{
    int rowBase;
    int rowCount;
    register int column;

    if (firstRow > lastRow)
        return;
    rowBase = firstRow << 6;
    rowCount = lastRow - firstRow + 1;
    do {
        column = firstColumn;
        if (column <= lastColumn) {
            do {
                if (SRand1(0xc8) == 0)
                    MapA[rowBase + column] = SRand1(2) + 0x3e;
                ++column;
            } while (column <= lastColumn);
        }
        rowBase += 0x40;
        --rowCount;
    } while (rowCount != 0);
}
