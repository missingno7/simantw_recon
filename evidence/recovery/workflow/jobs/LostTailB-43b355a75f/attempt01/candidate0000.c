/*
 * Hypothesis: for a B-list life at (x,y), derive its eight-way direction
 * index from the low byte of life, offset the coordinate by Dy8/Dx8, and
 * test the LifeB cell against life+8.  A matching cell is repeatedly
 * searched in the B list until FindInBList returns a negative result; this
 * drains duplicate list entries before reporting success.
 */
extern unsigned char far Dy8[];
extern unsigned char far Dx8[];
extern unsigned char near LifeB[];
extern int far FindInBList(int life, int column, int row);

int far LostTailB(int x, int y, int life)
{
    unsigned char index;
    int column;
    int row;
    int found;

    index = (unsigned char)life;
    index ^= 0xfc;
    index &= 7;
    column = Dy8[index + 8] + y;
    life += 8;
    row = Dx8[index] + x;
    if (LifeB[(row << 6) + column] != life)
        return 0;
    do {
        found = FindInBList(life, column, row);
    } while (found >= 0);
    return 1;
}
