/*
 * Hypothesis: this inserts one B-list record when the shared B-list count
 * is below its observed 500-entry limit.  The record is stored in the
 * selected Dx8 segment at the five byte fields shown by the target.  The
 * same coordinate pair indexes the near LifeB grid with a 64-byte row
 * stride; the third argument is both the record kind and the cell value.
 * The target restores DGROUP after selecting Dx8, so the far declarations
 * and the final grid/count operations are intentionally kept distinct.
 */
extern int far match_position[];
extern unsigned char far Dx8[];
extern unsigned char near LifeB[];

void far AddAntToBList(int life, int column, int attribute,
                       int state, int direction)
{
    int count;
    unsigned char far *list;

    if (match_position[0x4cea] >= 500)
        return;

    list = Dx8;
    count = match_position[0x4cea];

    list[count + 0x3736] = (unsigned char)life;
    list[count + 0x392c] = (unsigned char)column;
    list[count + 0x3b22] = (unsigned char)state;
    list[count + 0x3d18] = (unsigned char)attribute;
    list[count + 0x3f0e] = (unsigned char)direction;
    LifeB[(life << 6) + column] = (unsigned char)attribute;
    ++match_position[0x4cea];
}
