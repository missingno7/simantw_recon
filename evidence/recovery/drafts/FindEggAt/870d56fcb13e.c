/* Read the selected life plane and its compact list before asking FindLifeIndex for the matching egg record. */
extern int far FindLifeIndex(int list, int life, int column, int low, int high, int mask);
extern int far GetAntIndex(int list, int index, int far *life, int far *column, int far *attribute, int far *state, int far *direction);
extern int far ListIndexA;
extern int far ListIndexB;
extern int far ListIndexR;
extern unsigned char near LifeA[];
extern unsigned char near LifeB[];
extern unsigned char near LifeR[];
extern unsigned char far Dx8;
#define AT(off) ((&Dx8)[off])

int far FindEggAt(int far *outIndex, int which, int life, int column)
{
    int index;
    int tag;
    unsigned char far * volatile lifeList;
    unsigned char far * volatile columnList;
    unsigned char far * volatile attributeList;
    int cell;
    int direction;
    int state;
    int attribute;
    int eggColumn;

    index = -1;
    if (which <= 1) {
        if (life < 0) goto fail;
        if (life > 127) goto fail;
        if (column < 0) goto fail;
        if (column > 63) goto fail;
    } else {
        if (life < 0) goto fail;
        if (life > 63) goto fail;
        if (column < 0) goto fail;
        if (column > 63) goto fail;
    }
    if (which <= 0) goto fail;
    if (which == 1) {
        cell = LifeA[(life << 6) + column]; index = ListIndexA;
        lifeList = (&Dx8) + 0x23a4; columnList = (&Dx8) + 0x278e; attributeList = (&Dx8) + 0x2f62;
    } else if (which == 2) {
        cell = LifeB[(life << 6) + column]; index = ListIndexB;
        lifeList = (&Dx8) + 0x3736; columnList = (&Dx8) + 0x392c; attributeList = (&Dx8) + 0x3d18;
    } else if (which == 3) {
        cell = LifeR[(life << 6) + column]; index = ListIndexR;
        lifeList = (&Dx8) + 0x4104; columnList = (&Dx8) + 0x42fa; attributeList = (&Dx8) + 0x46e6;
    } else goto fail;
    if (cell == 0) goto fail;
    tag = cell;
    tag &= 0x7f;
    if (tag < 1 || tag > 7) goto fail;
    if (cell == 0xff || cell == 0xfe) goto fail;
    --index;
    while (index >= 0 && (lifeList[index] != life || columnList[index] != column || attributeList[index] != cell)) --index;
    index = FindLifeIndex(which, life, column, 1, 7, 0x7f);
    if (index < 0) goto fail;
    GetAntIndex(which, index, &cell, &eggColumn, &attribute, &state, &direction);
    *outIndex = index;
    return cell;
fail:
    *outIndex = index;
    return index;
}
