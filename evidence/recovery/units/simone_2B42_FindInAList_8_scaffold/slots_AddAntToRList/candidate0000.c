/*
 * Unit review: PACK words reached as match_position[K] are the public
 * symbols match_position[0x3966] -> ListIndexR (one selector word per symbol in the object).
 *
 * Hypothesis: this inserts one R-list record while the shared R-list count
 * is below the observed 500-entry limit.  Dx8 is selected once and the
 * five argument bytes are copied to the listed record fields.  The same
 * coordinates update the near LifeR grid with a 64-byte row stride, and
 * the R-list count is then incremented.
 */
extern int far match_position[];
extern int far ListIndexR;
extern unsigned char far Dx8[];
extern unsigned char near LifeR[];

void far AddAntToRList(int life, int column, int attribute,
                       int state, int direction)
{
    int count;
    unsigned char far *list;

    if (ListIndexR >= 500)
        return;

    list = Dx8;
    count = ListIndexR;

    list[count + 0x4104] = (unsigned char)life;
    list[count + 0x42fa] = (unsigned char)column;
    list[count + 0x44f0] = (unsigned char)state;
    list[count + 0x46e6] = (unsigned char)attribute;
    list[count + 0x48dc] = (unsigned char)direction;
    LifeR[(life << 6) + column] = (unsigned char)attribute;
    ++ListIndexR;
}
