/* Candidate translation unit simtwo_3EF8_AddRandAntLion_3_scaffold: composed from preserved exact-body sources
 * in MAPSYM order. Internal evidence id, not a historical filename.
 * Members: _AddRandAntLion, _AddAntLion, _SetAntLion
 * SCAFFOLDED: unclaimed members _InitSow, _DoSow, _InitAntLions, _DoAntLions are stand-ins in POOLSTUB_TEXT (pool order only, never compared). */

static unsigned char near lionRing[8] = {1, 2, 4, 7, 6, 5, 3, 0};
extern char far Dx8[];
#define Dy8 ((char far *)((unsigned char far *)&Dx8 + 0x8))  /* pool word C57E: one object, MAPSYM _Dx8+8 */
extern unsigned char far LionListX[];
extern unsigned char far LionListY[];
extern unsigned char far LionListM[];
extern unsigned char far LionListS[];
extern unsigned char far LionListT[];
extern int far LionIndex;
extern int far SRand1(int n);
extern int far IsClear3x3(int plane, int y, int x);
extern int far IsClearTile(int plane, int y, int x);
extern void far SetMap(int plane, int y, int x, int value);

extern int far SowX;  /* scaffold reference for pool word C574 (segment 9, MAPSYM_SITE_NAME) */
extern int far SowY;  /* scaffold reference for pool word C576 (segment 9, MAPSYM_SITE_NAME) */
extern int far SowDir;  /* scaffold reference for pool word C578 (segment 9, MAPSYM_SITE_NAME) */
extern int far SowSave;  /* scaffold reference for pool word C57A (segment 9, MAPSYM_SITE_NAME) */
extern int far SowTab;  /* scaffold reference for pool word C57C (segment 8, MAPSYM_SITE_NAME) */
extern int far Dx9;  /* scaffold reference for pool word C582 (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far AntsEatenByLions;  /* scaffold reference for pool word C584 (segment 9, MAPSYM_SITE_NAME) */
extern int far match_position;  /* scaffold reference for pool word C58A (segment 9, MAPSYM_SITE_NAME) */
extern int far match_length;  /* scaffold reference for pool word C58C (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far InitialLions;  /* scaffold reference for pool word C590 (segment 9, MAPSYM_SITE_NAME) */
extern int far Dy9;  /* scaffold reference for pool word C592 (segment 8, MAPSYM_SITE_NAME) */
extern int far TurnTab;  /* scaffold reference for pool word C594 (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far BAntsEaten;  /* scaffold reference for pool word C596 (segment 9, MAPSYM_SITE_NAME) */
extern int far RAntsEaten;  /* scaffold reference for pool word C598 (segment 9, MAPSYM_SITE_NAME) */

void far pool_stub_InitSow(void);
void far pool_stub_DoSow(void);
void far pool_stub_InitAntLions(void);
void far pool_stub_DoAntLions(void);
void far AddAntLion(int x, int y);
void SetAntLion(int index);

#pragma alloc_text(POOLSTUB_TEXT, pool_stub_InitSow)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_DoSow)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_InitAntLions)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_DoAntLions)
#pragma alloc_text(RUN2_TEXT, AddAntLion)
#pragma alloc_text(RUN3_TEXT, SetAntLion)

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _InitSow.
 * It only reproduces the object's selector-pool allocation order for the
 * words C574 C576 C578 C57A C57C; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_InitSow(void)
{
    volatile int t;

    t = SowX;
    t = SowY;
    t = SowDir;
    t = SowSave;
    t = SowTab;
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _DoSow.
 * It only reproduces the object's selector-pool allocation order for the
 * words C57E C580; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_DoSow(void)
{
    volatile int t;

    t = Dx8[0];
    t = Dx8[0];
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _InitAntLions.
 * It only reproduces the object's selector-pool allocation order for the
 * words C582 C584 C586 C588 C58A C58C C58E C590; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_InitAntLions(void)
{
    volatile int t;

    t = Dx9;
    t = AntsEatenByLions;
    t = LionListX[0];
    t = LionListY[0];
    t = match_position;
    t = match_length;
    t = LionListT[0];
    t = InitialLions;
}

void far AddRandAntLion(void)
{
    int tries;
    int y, x;
    int i;
    int lx, ly;

    tries = 0;
    for (;;) {
        y = SRand1(0x40) + SRand1(0x41);
        x = SRand1(0x20) + SRand1(0x21);
        if (IsClear3x3(1, y, x) == 1)
            break;
        if (IsClearTile(1, y, x) == 1) {
            if (tries >= 100)
                break;
        }
        tries++;
        if (tries >= 200)
            return;
    }

    SetMap(1, y, x, 0x38);
    for (i = 0; i < 8; i++) {
        ly = y + Dy8[i];
        lx = x + Dx8[i];
        if (IsClearTile(1, ly, lx) == 1)
            SetMap(1, ly, lx, lionRing[i] + 0x30);
    }
    LionListX[LionIndex] = y;
    LionListY[LionIndex] = x;
    LionListM[LionIndex] = 0;
    LionListS[LionIndex] = 0;
    LionListT[LionIndex] = 0;
    if (LionIndex < 9)
        LionIndex++;
}

void far AddAntLion(int x, int y)
{
    int i;
    int lx;
    int ly;

    SetMap(1, x, y, 0x38);
    for (i = 0; i < 8; i++) {
        ly = y + Dy8[i];
        lx = x + Dx8[i];
        if (IsClearTile(1, lx, ly) == 1)
            SetMap(1, lx, ly, lionRing[i] + 0x30);
    }
    LionListX[LionIndex] = x;
    LionListY[LionIndex] = y;
    LionListM[LionIndex] = 0;
    LionListS[LionIndex] = 0;
    LionListT[LionIndex] = 0;
    if (LionIndex < 9)
        LionIndex++;
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _DoAntLions.
 * It only reproduces the object's selector-pool allocation order for the
 * words C592 C594 C596 C598; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_DoAntLions(void)
{
    volatile int t;

    t = Dy9;
    t = TurnTab;
    t = BAntsEaten;
    t = RAntsEaten;
}

void SetAntLion(int index) {
    SetMap(1,LionListX[index],LionListY[index],LionListT[index]+0x38);
}

