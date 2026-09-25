/*
 * Hypothesis: the R-tail record at index supplies its type, column and life.
 * Select the direction ((type & 7) ^ 4), add Dy8[direction+8] to the
 * R-list column and Dx8[direction] to the R-list life, raise type by 8, and
 * insert the new record with state 9 and direction 0.  This is the exact
 * R-side mirror of the preserved B-side reconstruction.
 */
extern unsigned char far RlistT[];
extern unsigned char far RlistY[];
extern signed char far Dx8[];
extern signed char far Dy8[];
extern void far AddAntToRList(int life, int column, int attribute,
                              int state, int direction);

void far MakeNewTailR(int index)
{
    AddAntToRList(
        RlistT[index + 0x4104] +
            Dx8[((RlistT[index + 0x46e6] & 7) ^ 4)],
        RlistY[index + 0x42fa] +
            Dy8[((RlistT[index + 0x46e6] & 7) ^ 4) + 8],
        RlistT[index + 0x46e6] + 8,
        9,
        0);
}
