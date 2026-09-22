/* Candidate translation unit simone_2B42_FindInAList_7_scaffold: composed from preserved exact-body sources
 * in MAPSYM order. Internal evidence id, not a historical filename.
 * Members: _FindInAList, _FindInBList, _FindInRList, _AddAntToBList, _AddAntToRList, _ClearListB, _ClearListR
 * SCAFFOLDED: unclaimed members _RemoveFromAList are stand-ins in POOLSTUB_TEXT (pool order only, never compared). */

extern int far ListIndexA;
extern unsigned char far Dx8[];
extern int far ListIndexB;
extern int far ListIndexR;
extern int far match_position[];
extern unsigned char near LifeB[];
extern unsigned char near LifeR[];

extern int far AlistX;  /* scaffold reference for pool word C424 (segment 8, MAPSYM_SITE_NAME) */

void far pool_stub_RemoveFromAList(void);
void far AddAntToBList(int life, int column, int attribute, int state, int direction);
void far AddAntToRList(int life, int column, int attribute, int state, int direction);
void ClearListB(void);
void ClearListR(void);

#pragma alloc_text(POOLSTUB_TEXT, pool_stub_RemoveFromAList)
#pragma alloc_text(RUN2_TEXT, AddAntToBList, AddAntToRList)
#pragma alloc_text(RUN3_TEXT, ClearListB, ClearListR)

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _RemoveFromAList.
 * It only reproduces the object's selector-pool allocation order for the
 * words C424 C426; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_RemoveFromAList(void)
{
    volatile int t;

    t = AlistX;
    t = (int)ListIndexA;
}

int FindInAList(int firstKey, int secondKey)
{
    int index;

    index = ListIndexA;
    while (index > 0) {
        --index;
        if (Dx8[index + 0x23a4] == firstKey &&
            Dx8[index + 0x278e] == secondKey &&
            Dx8[index + 0x2f62] != 0)
            return index;
    }
    return -1;
}

int FindInBList(int firstKey, int secondKey, int thirdKey)
{
    int index;

    index = ListIndexB;
    while (index > 0) {
        --index;
        if (Dx8[index + 0x3736] == firstKey &&
            Dx8[index + 0x392c] == secondKey &&
            Dx8[index + 0x3d18] == thirdKey)
            return index;
    }
    return -1;
}

int FindInRList(int firstKey, int secondKey, int thirdKey)
{
    int index;

    index = ListIndexR;
    while (index > 0) {
        --index;
        if (Dx8[index + 0x4104] == firstKey &&
            Dx8[index + 0x42fa] == secondKey &&
            Dx8[index + 0x46e6] == thirdKey)
            return index;
    }
    return -1;
}

void far AddAntToBList(int life, int column, int attribute,
                       int state, int direction)
{
    int count;
    unsigned char far *list;

    if (ListIndexB >= 500)
        return;

    list = Dx8;
    count = ListIndexB;

    list[count + 0x3736] = (unsigned char)life;
    list[count + 0x392c] = (unsigned char)column;
    list[count + 0x3b22] = (unsigned char)state;
    list[count + 0x3d18] = (unsigned char)attribute;
    list[count + 0x3f0e] = (unsigned char)direction;
    LifeB[(life << 6) + column] = (unsigned char)attribute;
    ++ListIndexB;
}

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

void ClearListB(void)
{
    ListIndexB = 0;
}

void ClearListR(void)
{
    ListIndexR = 0;
}

