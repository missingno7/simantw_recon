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
extern void near DoNestAntB(int life, int column, int attribute);

void far DoAntSimB(void)
{
    int life;
    int column;
    int attribute;

    Tindex = ListIndexB;
    while (Tindex > 0) {
        --Tindex;
        life = Dx8[Tindex + 0x3736];
        column = Dx8[Tindex + 0x392c] & 0xff;
        attribute = Dx8[Tindex + 0x3d18];
        if (attribute != 0)
            DoNestAntB(life, column, attribute);
    }
}
