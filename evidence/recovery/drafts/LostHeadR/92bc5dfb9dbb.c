/*
 * Hypothesis: this is the R-team twin of LostHeadB.  The life value selects
 * signed Dx8/Dy8 offsets, the adjusted row/column probes LifeR for life-8,
 * and FindInRList confirms whether the corresponding list entry remains.
 */
extern signed char far Dx8[];
extern signed char far Dy8[];
extern unsigned char near LifeR[];
extern int far FindInRList(int firstKey, int secondKey, int thirdKey);

int far LostHeadR(int x, int y, int life)
{
    int index;
    int row;
    int column;

    index = life & 7;
    column = y + Dy8[index + 8];
    life -= 8;
    row = x + Dx8[index];
    if (LifeR[(row << 6) + column] == life)
        return 0;
    if (FindInRList(row, column, life) >= 0)
        return 0;
    return 1;
}
