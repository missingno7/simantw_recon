/*
 * FindEggAt (SIMONE_MODULE, unit simone:5AD2, profile "og"; my ant
 * object). Same shape and same LifeA/LifeB/LifeR/ListIndexA/B/R bindings
 * as _FindLifeAt (confirmed by identical calls list and identical
 * direct_data_bindings in this packet) -- see that candidate's notes for
 * the unresolved coordinate-validation/mask-selection prelude. The one
 * confirmed difference from _FindLifeAt: the FindLifeIndex call's "high"
 * constant is 7 here (push 0x7f; push 7; push 1) instead of 0x7f,
 * narrowing the accepted attribute range to [1,7] -- consistent with
 * selecting an egg-only attribute band rather than the broader default.
 * This is a best-effort, lower-confidence first pass capturing only the
 * well-evidenced tail (FindLifeIndex + GetAntIndex calls and the far
 * out-parameter store), exactly as with _FindLifeAt.
 */

extern int far FindLifeIndex(int list, int matchLife, int matchColumn, int low, int high, int mask);
extern int far GetAntIndex(int list, int index, int far *life, int far *column,
                            int far *attribute, int far *state, int far *direction);

extern int far ListIndexA;
extern int far ListIndexB;
extern int far ListIndexR;
extern unsigned char near LifeA[];
extern unsigned char near LifeB[];
extern unsigned char near LifeR[];
extern unsigned char far Dx8[];

int far FindEggAt(int far *outIndex, int which, int x, int y)
{
    int list;
    int count;
    int index;
    int cell;
    unsigned char far *colList;
    unsigned char far *rowList;
    unsigned char far *valueList;
    int idx;
    int column;
    int attribute;
    int state;
    int direction;

    list = which;
    if (x < 0 || y < 0 || y > 63) goto fail;
    switch (which) {
    case 1:
        if (x > 127) goto fail;
        cell = LifeA[(x << 6) + y];
        count = ListIndexA; colList = Dx8 + 0x23a4; rowList = Dx8 + 0x278e; valueList = Dx8 + 0x2f62;
        break;
    case 2:
        if (x > 63) goto fail;
        cell = LifeB[(x << 6) + y];
        count = ListIndexB; colList = Dx8 + 0x3736; rowList = Dx8 + 0x392c; valueList = Dx8 + 0x3d18;
        break;
    case 3:
        if (x > 63) goto fail;
        cell = LifeR[(x << 6) + y];
        count = ListIndexR; colList = Dx8 + 0x4104; rowList = Dx8 + 0x42fa; valueList = Dx8 + 0x46e6;
        break;
    default:
        goto fail;
    }
    if (cell == 0 || cell == 0xfe || cell == 0xff || (cell & 0x7f) < 1 || (cell & 0x7f) > 7) goto fail;
    index = count - 1;
    while (index >= 0 && (colList[index] != x || rowList[index] != y || valueList[index] != cell)) --index;
    idx = FindLifeIndex(list, x, y, 1, 7, 0x7f);
    if (idx < 0) goto fail;

    GetAntIndex(list, idx, &cell, &column, &attribute, &state, &direction);
    *outIndex = idx;
    return cell;
fail:
    *outIndex = -1;
    return -1;
}
