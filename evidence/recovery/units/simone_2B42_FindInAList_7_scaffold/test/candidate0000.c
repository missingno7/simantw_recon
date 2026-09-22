/* Candidate translation unit simone_2B42_FindInAList_7_scaffold: composed from preserved exact-body sources
 * in MAPSYM order. Internal evidence id, not a historical filename.
 * Members: _FindInAList, _FindInBList, _FindInRList, _AddAntToBList, _AddAntToRList, _ClearListB, _ClearListR
 * SCAFFOLDED: unclaimed members _RemoveFromAList, _ExitHole are stand-ins in POOLSTUB_TEXT (pool order only, never compared). */

extern unsigned int far AListState[];
extern unsigned char far Dx8[];
extern int far ListIndexB;
extern int far ListIndexR;
extern int far match_position[];
extern unsigned char near LifeB[];
extern unsigned char near LifeR[];

extern int far AlistX;  /* scaffold reference for pool word C424 (segment 8, MAPSYM_SITE_NAME) */
extern int far Dy8;  /* scaffold reference for pool word C42C (segment 8, MAPSYM_SITE_NAME) */
extern int far Dx9;  /* scaffold reference for pool word C42E (segment 8, SEGMENT_REPRESENTATIVE) */

void far pool_stub_RemoveFromAList(void);
void far pool_stub_ExitHole(void);
void far AddAntToBList(int life, int column, int attribute, int state, int direction);
void far AddAntToRList(int life, int column, int attribute, int state, int direction);
void ClearListB(void);
void ClearListR(void);

#pragma alloc_text(POOLSTUB_TEXT, pool_stub_RemoveFromAList)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_ExitHole)
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
    t = AListState[0];
}

int FindInAList(int firstKey, int secondKey)
{
    int index;

    index = AListState[0x4078];
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

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _ExitHole.
 * It only reproduces the object's selector-pool allocation order for the
 * words C42C C42E; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_ExitHole(void)
{
    volatile int t;

    t = Dy8;
    t = Dx9;
}

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

void far AddAntToRList(int life, int column, int attribute,
                       int state, int direction)
{
    int count;
    unsigned char far *list;

    if (match_position[0x3966] >= 500)
        return;

    list = Dx8;
    count = match_position[0x3966];

    list[count + 0x4104] = (unsigned char)life;
    list[count + 0x42fa] = (unsigned char)column;
    list[count + 0x44f0] = (unsigned char)state;
    list[count + 0x46e6] = (unsigned char)attribute;
    list[count + 0x48dc] = (unsigned char)direction;
    LifeR[(life << 6) + column] = (unsigned char)attribute;
    ++match_position[0x3966];
}

void ClearListB(void)
{
    ListIndexB = 0;
}

void ClearListR(void)
{
    ListIndexR = 0;
}

