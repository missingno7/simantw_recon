/*
 * Hypothesis: ListIndexR is the exclusive bound of the pending R-list.
 * Tindex is a shared cursor.  Each pass consumes one record from the
 * selected Dx8 segment, and a nonzero record attribute is handed to the
 * far DoNestAntR worker as (life, column, attribute).  The selector loads
 * and explicit DS restoration show that the list segment is separate from
 * DGROUP while the indexed Tindex state remains live across the call.
 */
struct RListPlanes {
    unsigned char x[502];
    unsigned char y[502];
    unsigned char m[502];
    unsigned char t[502];
    unsigned char s[502];
};
extern struct RListPlanes far RlistX;
extern int far ListIndexR;
extern int far Tindex;
extern void far DoNestAntR(int life, int column, int attribute);

void far DoAntSimR(void)
{
    int life;
    int column;
    int attribute;

    Tindex = ListIndexR;
    while (Tindex > 0) {
        --Tindex;
        life = RlistX.x[Tindex];
        column = RlistX.y[Tindex] & 0xff;
        attribute = RlistX.t[Tindex];
        if (attribute != 0)
            DoNestAntR(life, column, attribute);
    }
}
