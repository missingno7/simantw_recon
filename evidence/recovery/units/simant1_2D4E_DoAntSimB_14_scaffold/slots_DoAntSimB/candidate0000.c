/* Selector identity probe: use the BlistX base for the shared B-list fields. */
struct BListPlanes {
    unsigned char x[502];
    unsigned char y[502];
    unsigned char m[502];
    unsigned char t[502];
    unsigned char s[502];
};
extern struct BListPlanes far BlistX;

/*
 * Hypothesis: ListIndexB is the exclusive bound of the pending B-list.
 * Tindex is a shared cursor.  Each pass consumes one record from the
 * selected Dx8 segment, and a nonzero record attribute is handed to the
 * near DoNestAntB worker as (life, column, attribute).  The target's
 * selector loads and its push-SS/pop-DS pairs show that ListIndexB/Tindex
 * and match_position are DGROUP state while Dx8 is a separately selected
 * far list segment.
 */
extern int far ListIndexB;
extern int far Tindex;
extern unsigned char far Dx8[];
extern void far DoNestAntB(int life, int column, int attribute);

void far DoAntSimB(void)
{
    int life;
    int column;
    int attribute;

    Tindex = ListIndexB;
    while (Tindex > 0) {
        --Tindex;
        life = BlistX.x[Tindex];
        column = BlistX.y[Tindex] & 0xff;
        attribute = BlistX.t[Tindex];
        if (attribute != 0)
            DoNestAntB(life, column, attribute);
    }
}
