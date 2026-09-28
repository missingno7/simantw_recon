/* Candidate translation unit simant1_2D4E_TryMoveDirB_2_scaffold: composed from preserved exact-body sources
 * in MAPSYM order. Internal evidence id, not a historical filename.
 * Members: _TryMoveDirB, _GetOutB
 * SCAFFOLDED: unclaimed members _DoAntSimB, _DoNestAntB, _RaidInB, _DoNestFightB, _SimEggB, _SimQueenB, _QueenMoveB, _LeaveNestB are stand-ins in POOLSTUB_TEXT (pool order only, never compared). */

extern char far Dx8[];
extern char far Dy8[];
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) BlistX[];
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) BlistY[];
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) BlistT[];
extern unsigned char near MapB[];
extern unsigned char near LifeB[];
extern int far MeWantFood;
extern int far Tindex;
extern int far GetOutB(int x);
extern void far DoTroph(int x, int y, int dir);
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) BlistS[];
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) BlistM[];
extern unsigned char far HoleMapB[];
extern unsigned char far ExitMapB[];
extern void far MakeNewHoleB(int x);
extern int far ExitHole(int hole, int x, int val, int mode, int stam);
extern int far SRand8(void);
extern int far SRand2(void);
extern int far IsItDirt(int tile);
extern void far DigTileThemB(int x, int count);
extern int far TryMoveDirB(int x, int y, int dir);

extern int far ListIndexB;  /* scaffold reference for pool word C34E (segment 9, MAPSYM_SITE_NAME) */
extern int __based(__segname("SIMANT_DATA_GROUP")) pool_segment_ref_SIMANT_DATA_GROUP;  /* scaffold reference for pool word C352 (based segment) */
extern int far match_position;  /* scaffold reference for pool word C354 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far match_length;  /* scaffold reference for pool word C356 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far Dx9;  /* scaffold reference for pool word C358 (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far pack_buf;  /* scaffold reference for pool word C35A (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far Scycle;  /* scaffold reference for pool word C35C (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far EditColumns;  /* scaffold reference for pool word C35E (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far MiscStrs;  /* scaffold reference for pool word C360 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far LastQueenPlane;  /* scaffold reference for pool word C362 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far EditDragPnt;  /* scaffold reference for pool word C368 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far SMode;  /* scaffold reference for pool word C36A (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far modeButtonState;  /* scaffold reference for pool word C36C (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far Dy9;  /* scaffold reference for pool word C36E (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far CurRestPlane;  /* scaffold reference for pool word C370 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far TurnTab;  /* scaffold reference for pool word C372 (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far StoreArray;  /* scaffold reference for pool word C374 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far relSearchDirs;  /* scaffold reference for pool word C376 (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far mapCursorRect;  /* scaffold reference for pool word C378 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far TileMassYB;  /* scaffold reference for pool word C37A (segment 9, MAPSYM_SITE_NAME) */
extern int far TileMassXB;  /* scaffold reference for pool word C37C (segment 9, MAPSYM_SITE_NAME) */

void far pool_stub_DoAntSimB(void);
void far pool_stub_DoNestAntB(void);
void far pool_stub_RaidInB(void);
void far pool_stub_DoNestFightB(void);
void far pool_stub_SimEggB(void);
void far pool_stub_SimQueenB(void);
void far pool_stub_QueenMoveB(void);
void far pool_stub_LeaveNestB(void);
int far GetOutB(int x);

#pragma alloc_text(POOLSTUB_TEXT, pool_stub_DoAntSimB)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_DoNestAntB)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_RaidInB)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_DoNestFightB)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_SimEggB)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_SimQueenB)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_QueenMoveB)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_LeaveNestB)
#pragma alloc_text(RUN2_TEXT, GetOutB)

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _DoAntSimB.
 * It only reproduces the object's selector-pool allocation order for the
 * words C34E C350; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_DoAntSimB(void)
{
    volatile int t;

    t = ListIndexB;
    t = (int)Tindex;
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _DoNestAntB.
 * It only reproduces the object's selector-pool allocation order for the
 * words C352 C354 C356 C358 C35A C35C C35E C360; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_DoNestAntB(void)
{
    volatile int t;

    t = pool_segment_ref_SIMANT_DATA_GROUP;
    t = match_position;
    t = match_length;
    t = Dx9;
    t = pack_buf;
    t = Scycle;
    t = EditColumns;
    t = MiscStrs;
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _RaidInB.
 * It only reproduces the object's selector-pool allocation order for the
 * words C362; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_RaidInB(void)
{
    volatile int t;

    t = LastQueenPlane;
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _DoNestFightB.
 * It only reproduces the object's selector-pool allocation order for the
 * words C364 C366; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_DoNestFightB(void)
{
    volatile int t;

    t = Dy8[0];
    t = Dx8[0];
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _SimEggB.
 * It only reproduces the object's selector-pool allocation order for the
 * words C368 C36A C36C C36E; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_SimEggB(void)
{
    volatile int t;

    t = EditDragPnt;
    t = SMode;
    t = modeButtonState;
    t = Dy9;
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _SimQueenB.
 * It only reproduces the object's selector-pool allocation order for the
 * words C370 C372 C374 C376 C378; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_SimQueenB(void)
{
    volatile int t;

    t = CurRestPlane;
    t = TurnTab;
    t = StoreArray;
    t = relSearchDirs;
    t = mapCursorRect;
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _QueenMoveB.
 * It only reproduces the object's selector-pool allocation order for the
 * words C37A C37C; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_QueenMoveB(void)
{
    volatile int t;

    t = TileMassYB;
    t = TileMassXB;
}

int far TryMoveDirB(int x, int y, int dir)
{
  int dy;
  int dx;
  if (dir < 0)
    return 0;
  dx = Dx8[dir] + x;
  dy = Dy8[dir] + y;
  if (dx > 0x3f)
    return 0;
  if (dx < 0)
    return 0;
  if (dy > 0x3f)
    return 0;
  if (dy < 1)
    return GetOutB(x);
  if (MapB[(dx << 6) + dy] >= 0x1c)
    return 0;
  if (LifeB[(dx << 6) + dy] == 0xff && MeWantFood && BlistX[Tindex] < 0x80)
  {
    LifeB[(x << 6) + y] = BlistT[Tindex] & 0xf8 | ((unsigned char) dir);
    DoTroph(x, y, dir);
  }
  LifeB[(dx << 6) + dy] = BlistT[Tindex] & 0xf8 | ((unsigned char) dir);
  LifeB[(x << 6) + y] = 0;
  BlistX[Tindex] = (unsigned char) dx;
  BlistY[Tindex] = (unsigned char) dy;
  BlistT[Tindex] = LifeB[(dx << 6) + dy];
  return 1;
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _LeaveNestB.
 * It only reproduces the object's selector-pool allocation order for the
 * words C380; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_LeaveNestB(void)
{
    volatile int t;

    t = HoleMapB[0];
}

int far GetOutB(int x)
{
    
    int raw;

    if (MapB[x << 6] == 0x18) {
        raw = BlistT[Tindex];
        BlistT[Tindex] = 0;
        if (HoleMapB[x] == 0)
            MakeNewHoleB(x);
        if (ExitHole(HoleMapB[x], x, SRand8() + (raw & 0xf8),
                      BlistM[Tindex], BlistS[Tindex]) != 0) {
            LifeB[(x << 6) + 1] = 0;
            return 1;
        }
        BlistT[Tindex] = raw;
        BlistM[Tindex] = 0;
        return 0;
    }

    if (ExitMapB[x << 6] != 0)
        ExitMapB[x << 6]--;

    if (SRand2() != 0) {
        if (x > 0 && IsItDirt(MapB[(x << 6) - 0x3f]) != 0)
            DigTileThemB(x - 1, 1);
    } else {
        if (x < 0x3f && IsItDirt(MapB[(x << 6) + 0x41]) != 0)
            DigTileThemB(x + 1, 1);
    }

    TryMoveDirB(x, 1, SRand8());
    return 0;
}

