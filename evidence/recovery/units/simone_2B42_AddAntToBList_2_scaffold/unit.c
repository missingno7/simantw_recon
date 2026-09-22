/* Candidate translation unit simone_2B42_AddAntToBList_2_scaffold: composed from preserved exact-body sources
 * in MAPSYM order. Internal evidence id, not a historical filename.
 * Members: _AddAntToBList, _AddAntToRList
 * SCAFFOLDED: unclaimed members _RemoveFromAList, _FindInBList, _FindInRList, _ExitHole are stand-ins in POOLSTUB_TEXT (pool order only, never compared). */

extern int far match_position[];
extern unsigned char far Dx8[];
extern unsigned char near LifeB[];
extern unsigned char near LifeR[];

extern int far AlistX;  /* scaffold reference for pool word C424 (segment 8, MAPSYM_SITE_NAME) */
extern int far ListIndexA;  /* scaffold reference for pool word C426 (segment 9, MAPSYM_SITE_NAME) */
extern int far ListIndexB;  /* scaffold reference for pool word C428 (segment 9, MAPSYM_SITE_NAME) */
extern int far ListIndexR;  /* scaffold reference for pool word C42A (segment 9, MAPSYM_SITE_NAME) */
extern int far Dy8;  /* scaffold reference for pool word C42C (segment 8, MAPSYM_SITE_NAME) */
extern int far Dx9;  /* scaffold reference for pool word C42E (segment 8, SEGMENT_REPRESENTATIVE) */

void far pool_stub_RemoveFromAList(void);
void far pool_stub_FindInBList(void);
void far pool_stub_FindInRList(void);
void far pool_stub_ExitHole(void);

#pragma alloc_text(POOLSTUB_TEXT, pool_stub_RemoveFromAList)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_FindInBList)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_FindInRList)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_ExitHole)

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _RemoveFromAList.
 * It only reproduces the object's selector-pool allocation order for the
 * words C424 C426; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_RemoveFromAList(void)
{
    volatile int t;

    t = AlistX;
    t = ListIndexA;
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _FindInBList.
 * It only reproduces the object's selector-pool allocation order for the
 * words C428; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_FindInBList(void)
{
    volatile int t;

    t = ListIndexB;
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _FindInRList.
 * It only reproduces the object's selector-pool allocation order for the
 * words C42A; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_FindInRList(void)
{
    volatile int t;

    t = ListIndexR;
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

