/*
 * Hypothesis: the life value selects one of eight signed Dx8/Dy8 offsets.
 * The adjusted row and column address LifeB; a matching life-8 marker or an
 * existing B-list entry means the head was not lost, otherwise return one.
 */
extern signed char far Dx8[];
extern signed char far Dy8[];
extern unsigned char near LifeB[];
extern int far FindInBList(int firstKey, int secondKey, int thirdKey);

int far LostHeadB(int x, int y, int life)
{
    int index;
    int row;
    int column;

    index = life & 7;
    column = y + Dy8[index + 8];
    row = x + Dx8[index];
    if (LifeB[(row << 6) + column] == life - 8)
        return 0;
    if (FindInBList(row, column, life - 8) >= 0)
        return 0;
    return 1;
}
