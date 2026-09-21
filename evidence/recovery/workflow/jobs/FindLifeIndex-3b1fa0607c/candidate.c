/*
 * FindLifeIndex: search one ant list (same field layout and list
 * selection as FindAntIndex/SetAntIndex: A-list list<=1
 * match_position[0x4078], B-list list==2 match_position[0x4cea],
 * otherwise R-list match_position[0x3966]; per-list life/column/
 * attribute offsets 0x23a4/0x278e/0x2f62, 0x3736/0x392c/0x3d18 and
 * 0x4104/0x42fa/0x46e6) from the newest entry down for one whose life
 * and column fields equal the given pair and whose attribute field,
 * masked, falls in [low, high]. Returns the matching index, or -1 when
 * exhausted.
 */
extern int far match_position[];
extern unsigned char far Dx8;
#define ATP(off) (&Dx8 + (off))

int far FindLifeIndex(int list, int matchLife, int matchColumn, int low, int high, int mask)
{
    unsigned char far *lifeArr;
    unsigned char far *columnArr;
    unsigned char far *attrArr;
    int count;
    int i;
    int masked;

    if (list <= 1) {
        count = match_position[0x4078];
        lifeArr = ATP(0x23a4);
        columnArr = ATP(0x278e);
        attrArr = ATP(0x2f62);
    } else if (list == 2) {
        count = match_position[0x4cea];
        lifeArr = ATP(0x3736);
        columnArr = ATP(0x392c);
        attrArr = ATP(0x3d18);
    } else {
        count = match_position[0x3966];
        lifeArr = ATP(0x4104);
        columnArr = ATP(0x42fa);
        attrArr = ATP(0x46e6);
    }
    for (i = count - 1; i >= 0; i--) {
        masked = attrArr[i] & mask;
        if (lifeArr[i] == matchLife && columnArr[i] == matchColumn &&
            masked >= low && masked <= high)
            break;
    }
    return i;
}
