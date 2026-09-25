/*
 * Hypothesis: ListIndexR is the exclusive bound of the pending R-list.
 * Tindex is a shared cursor.  Each pass consumes one record from the
 * selected Dx8 segment, and a nonzero record attribute is handed to the
 * far DoNestAntR worker as (life, column, attribute).  The selector loads
 * and explicit DS restoration show that the list segment is separate from
 * DGROUP while the indexed Tindex state remains live across the call.
 */
extern int far ListIndexR;
extern int far Tindex;
extern unsigned char far Dx8[];
extern void far DoNestAntR(int life, int column, int attribute);

void far DoAntSimR(void)
{
    int life;
    int column;
    int attribute;

    Tindex = ListIndexR;
    while (Tindex > 0) {
        --Tindex;
        life = Dx8[Tindex + 0x4104];
        column = Dx8[Tindex + 0x42fa] & 0xff;
        attribute = Dx8[Tindex + 0x46e6];
        if (attribute != 0)
            DoNestAntR(life, column, attribute);
    }
}
