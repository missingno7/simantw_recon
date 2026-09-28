/* Candidate translation unit simtwo_3EF8_AddRandAntLion_3_scaffold: composed from preserved exact-body sources
 * in MAPSYM order. Internal evidence id, not a historical filename.
 * Members: _DoSow, _InitAntLions, _AddRandAntLion, _AddAntLion, _SetAntLion
 * SCAFFOLDED: unclaimed members _InitSow and _DoAntLions are stand-ins in POOLSTUB_TEXT (pool order only, never compared). */

extern char far Dx8[];
extern char far Dy8[];
extern unsigned char far LionListX[];
extern unsigned char far LionListY[];
extern unsigned char far LionListM[];
extern unsigned char far LionListS[];
extern unsigned char far LionListT[];
extern int far LionIndex;
extern int far SRand1(int n);
extern int far IsClear3x3(int plane, int x, int y);
extern int far IsClearTile(int plane, int x, int y);
extern void far SetMap(int plane, int x, int y, int value);

extern unsigned char near MapA[];
extern unsigned char near LifeA[128][64];
extern int far SRand4(void);
extern int far IsValidA(int x, int y);
extern struct { int v[3]; } far SowY;
extern struct { int v[3]; } far SowX;
extern struct { int v[3]; } far SowDir;
extern struct { int v[3]; } far SowSave;
#define SOWY(i) SowY.v[i]
#define SOWX(i) SowX.v[i]
#define SOWDIR(i) SowDir.v[i]
#define SOWSAVE(i) SowSave.v[i]
#define SOWTAB(i) SowTab.v[i]


extern struct { unsigned char v[8]; } far SowTab;  /* target selector reference for pool word C57C */
extern int far Dx9;  /* target selector reference for pool word C594 */
extern int far Dy9;
extern int far RAntsEaten;
extern int far BAntsEaten;  /* scaffold reference for pool word C582 (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far AntsEatenByLions;
extern int far InitialLions;  /* scaffold reference for pool word C584 (segment 9, MAPSYM_SITE_NAME) */
extern int far EditColumns;  /* scaffold reference for pool word C58A (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far MiscStrs;  /* scaffold reference for pool word C58C (segment 9, SEGMENT_REPRESENTATIVE) */

void far pool_stub_InitSow(void);
void far pool_stub_DoAntLions(void);
void SetAntLion(int index);

#pragma alloc_text(POOLSTUB_TEXT, pool_stub_InitSow)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_DoAntLions)
#pragma alloc_text(RUN2_TEXT, SetAntLion)

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _InitSow.
 * It only reproduces the object's selector-pool allocation order for the
 * words C574 C576 C578 C57A C57C; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_InitSow(void)
{
    volatile int t;

    t = SowX.v[0];
    t = SowY.v[0];
    t = SowDir.v[0];
    t = SowSave.v[0];
    t = SowTab.v[0];
}





/* Body-exact DoSow; selectors resolve in this extended unit. */
void far DoSow(void)
{
    int i;
    for (i = 0; i < 3; i++) {
        int newX;
        int newY;
        int terrain;
        if (SRand4() == 0)
            continue;
        if (SRand4() == 0) {
            SOWDIR(i) = (SOWDIR(i) + SRand1(3) - 1) & 7;
            MapA[SOWX(i) * 64 + SOWY(i)] = SOWTAB(SOWDIR(i));
        }
        newY = Dy8[SOWDIR(i)] + SOWY(i);
        newX = Dx8[SOWDIR(i)] + SOWX(i);
        if (!IsValidA(newX, newY))
            continue;
        if (LifeA[newX][newY] != 0)
            continue;
        terrain = MapA[newX * 64 + newY];
        if (terrain >= 0x10)
            continue;
        MapA[SOWX(i) * 64 + SOWY(i)] = SOWSAVE(i);
        SOWSAVE(i) = terrain;
        MapA[newX * 64 + newY] = SOWTAB(SOWDIR(i));
        SOWX(i) = newX;
        SOWY(i) = newY;
    }
}

static unsigned char near lionRing[8] = {1, 2, 4, 7, 6, 5, 3, 0};

void far InitAntLions(int count)
{
  int remaining[1];
  int lx;
  int tries;
  int x;
  int y;
  int ly;
  int value[1];
  int i;
  *(&LionIndex) = 0;
  AntsEatenByLions = 0;
  if (count > 10)
    count = 10;
  if (count > 0)
  {
    remaining[0] = count;
    do
    {
      tries = 0;
      for (;;)
      {
        x = SRand1(0x40) + SRand1(0x41);
        y = SRand1(0x20) + SRand1(0x21);
        if (IsClear3x3(1, x, y) != 1)
        {
          value[0] = IsClearTile(1, x, y);
          if (value[0] == 1)
          {
            if (tries >= 100)
              goto place;
          }
          tries++;
          if (tries >= 200)
            goto skip;
        }
        else
          goto place;
      }

      place:
      SetMap(1, x, y, 0x38);

      for (i = 0; i < 8; i += 1)
      {
        ly = y + Dy8[i];
        lx = x + Dx8[i];
        if (IsClearTile(1, lx, ly) == 1)
          SetMap(1, lx, ly, lionRing[i] + 0x30);
      }

      LionListX[*(&LionIndex)] = x;
      LionListY[*(&LionIndex)] = y;
      LionListM[*(&LionIndex)] = 0;
      LionListS[*(&LionIndex)] = 0;
      LionListT[*(&LionIndex)] = 0;
      if ((*(&LionIndex)) < 9)
        *(&LionIndex) = (*(&LionIndex)) + 1;
      skip:
      remaining[0]--;

    }
    while (remaining[0]);
  }
  InitialLions = count;
}

/* SCAFFOLD: preserve the unclaimed _DoAntLions selector order. */
void far pool_stub_DoAntLions(void)
{
    volatile int t;

    t = Dy9;
    t = Dx9;
    t = BAntsEaten;
    t = RAntsEaten;
}

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

