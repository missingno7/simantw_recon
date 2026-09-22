/*
 * Hypothesis: derive the R-tail direction from the low byte of life,
 * offset the coordinate by the shared Dy8/Dx8 direction tables, and test
 * the LifeR cell against life+8.  A matching cell is retained only after
 * the repeated FindInRList(row,column,life) search has exhausted duplicates.
 */
extern signed char far Dy8[];
extern signed char far Dx8[];
extern unsigned char near LifeR[];
extern int far FindInRList(int row, int column, int life);

int far LostTailR(int x, int y, int life)
{
    int index;
    int column;
    int row;

    index = life ^ 0xfc;
    index &= 7;
    column = Dy8[index + 8] + y;
    life += 8;
    row = Dx8[index] + x;
    if (LifeR[(row << 6) + column] != life)
        return 0;
    while (FindInRList(row, column, life) >= 0) {
    }
    return 1;
}
