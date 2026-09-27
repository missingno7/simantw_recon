/* Candidate translation unit simtwo_3EF8_AddRandAntLion_5_scaffold: composed from preserved exact-body sources
 * in MAPSYM order. Internal evidence id, not a historical filename.
 * Members: _AddRandAntLion, _AddAntLion, _SetAntLion, _FindInLionList, _KillAntLion
 * SCAFFOLDED: unclaimed members _InitSow, _DoSow, _InitAntLions are stand-ins in POOLSTUB_TEXT (pool order only, never compared). */

extern char far Dx8[];
extern char far Dy8[];
extern unsigned char far LionListX[];
extern unsigned char far LionListY[];
extern unsigned char far LionListM[];
extern unsigned char far LionListS[];
extern unsigned char far LionListT[];
extern int far LionIndex;
extern int far SRand1(int n);
extern unsigned char near MapA[128][64];
extern int far IsClear3x3(int plane, int x, int y);
extern int far IsClearTile(int plane, int x, int y);
extern void far SetMap(int plane, int x, int y, int value);

extern int far SowX[3];
extern int far SowY[3];
extern int far SowDir[3];
extern int far SowSave[3];
extern unsigned char far SowTab[8];
#define SOWX(i) SowX[i]
#define SOWY(i) SowY[i]
#define SOWDIR(i) SowDir[i]
#define SOWSAVE(i) SowSave[i]
#define SOWTAB(i) SowTab[i]
extern int far AntsEatenByLions;  /* C584 */
extern int far InitialLions;  /* C590 */
extern int far Dy9;  /* C592 */
extern int far Dx9;  /* C594 */
extern int far BAntsEaten;  /* C596 */
extern int far RAntsEaten;  /* C598 */

void far InitSow(void);
void far pool_stub_DoSow(void);
void far pool_stub_InitAntLions(void);
extern int far InitialLions;
extern int far Dy9;
extern int far Dx9;
extern int far BAntsEaten;
extern int far RAntsEaten;
void far pool_stub_DoAntLions(void);
void SetAntLion(int index);
int FindInLionList(int firstKey, int secondKey);
void far KillAntLion(int index);

#pragma alloc_text(POOLSTUB_TEXT, pool_stub_DoSow)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_InitAntLions)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_DoAntLions)
#pragma alloc_text(RUN1_TEXT, InitSow)
#pragma alloc_text(RUN2_TEXT, SetAntLion, FindInLionList, KillAntLion)

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _DoSow.
 * It only reproduces the object's selector-pool allocation order for the
 * words C57E C580; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_DoSow(void)
{
    volatile int t;

    t = Dy8[0];
    t = Dx8[0];
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _InitAntLions.
 * It only reproduces the object's selector-pool allocation order for the
 * words C582 C584 C586 C588 C58A C58C C58E; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_InitAntLions(void)
{
    volatile int t;

    t = (int)LionIndex;
    t = AntsEatenByLions;
    t = LionListX[0];
    t = LionListY[0];
    t = LionListM[0];
    t = LionListS[0];
    t = LionListT[0];
    t = InitialLions;
}

/* SCAFFOLD, not recovered source: reproduces remaining selector order only. */
void far pool_stub_DoAntLions(void)
{
    volatile int t;

    t = Dy9;
    t = Dx9;
    t = BAntsEaten;
    t = RAntsEaten;
}

void far InitSow(void)
{
    int i;
    int x;
    int y;
    unsigned char *p;

    for (i = 2; i > 0; i--) {
        x = SRand1(128);
        y = SRand1(64);
        if (MapA[x][y] < 16) {
            SOWX(i) = x;
            SOWY(i) = y;
            SOWDIR(i) = SRand1(8);
            SOWSAVE(i) = MapA[x][y];
            MapA[x][y] = SOWTAB(SOWDIR(i));
        }
    
    }
}

static unsigned char near lionRing[8] = {1, 2, 4, 7, 6, 5, 3, 0};
void far AddRandAntLion(void)
{
    int tries;
    int x, y;
    int i;
    int lx, ly;

    tries = 0;
    for (;;) {
        x = SRand1(0x40) + SRand1(0x41);
        y = SRand1(0x20) + SRand1(0x21);
        if (IsClear3x3(1, x, y) == 1)
            break;
        if (IsClearTile(1, x, y) == 1) {
            if (tries >= 100)
                break;
        }
        tries++;
        if (tries >= 200)
            return;
    }

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

void SetAntLion(int index) {
    SetMap(1,LionListX[index],LionListY[index],LionListT[index]+0x38);
}

int FindInLionList(int firstKey, int secondKey) {
 int index = LionIndex - 1;
 while (index >= 0) {
  if (LionListX[index] == firstKey) {
   if (LionListY[index] == secondKey) break;
  }
  --index;
 }
 return index;
}

void far KillAntLion(int index)
{
    int i;

    SetMap(1, LionListX[index], LionListY[index], 0x3f);
    if (LionIndex > 0) {
        LionIndex--;
        for (i = index; i < LionIndex; i++) {
            LionListX[i] = LionListX[i + 1];
            LionListY[i] = LionListY[i + 1];
            LionListT[i] = LionListT[i + 1];
            LionListM[i] = LionListM[i + 1];
            LionListS[i] = LionListS[i + 1];
        }
    }
}

