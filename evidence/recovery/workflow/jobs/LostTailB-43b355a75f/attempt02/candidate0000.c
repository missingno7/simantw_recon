/*
 * Hypothesis: for a B-list life at (x,y), derive its eight-way direction
 * index from the low byte of life, offset the coordinate by Dy8/Dx8, and
 * test the LifeB cell against life+8.  A matching cell is repeatedly
 * searched in the B list until FindInBList returns a negative result; this
 * drains duplicate list entries before reporting success.
 */
extern signed char far Dy8[];
extern signed char far Dx8[];
extern unsigned char near LifeB[];
extern int far FindInBList(int life, int column, int row);

int far LostTailB(int x, int y, int life)
{
    int index;
    int column;
    int row;
    int found;

    index = life ^ 0xfc;
    index &= 7;
    column = Dy8[index + 8] + y;
    life += 8;
    row = Dx8[index] + x;
    if (LifeB[(row << 6) + column] != life)
        return 0;
    do {
        found = FindInBList(row, column, life);
    } while (found >= 0);
    return 1;
}
