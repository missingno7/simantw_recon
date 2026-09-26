/* Candidate translation unit simant1_5344_GetOutR_1_scaffold: composed from preserved exact-body sources
 * in MAPSYM order. Internal evidence id, not a historical filename.
 * Members: _GetOutR
 * SCAFFOLDED: unclaimed members _DoAntSimR, _DoNestAntR, _RaidInR, _DoNestFightR, _SimEggR, _SimQueenR, _QueenMoveR are stand-ins in POOLSTUB_TEXT (pool order only, never compared). */

extern int far Tindex;
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) RlistT[];
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) RlistS[];
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) RlistM[];
extern unsigned char near MapR[];
extern unsigned char far HoleMapR[];
extern unsigned char near LifeR[];
extern unsigned char far ExitMapR[];
extern void far MakeNewHoleR(int x);
extern int far ExitHole(int hole, int x, int val, int mode, int stam);
extern int far SRand8(void);
extern int far SRand2(void);
extern int far IsItDirt(int tile);
extern void far DigTileThemR(int x, int count);
extern int far TryMoveDirR(int x, int y, int dir);

extern int far ListIndexR;  /* scaffold reference for pool word C382 (segment 9, MAPSYM_SITE_NAME) */
extern int __based(__segname("SIMANT_DATA_GROUP")) pool_segment_ref_SIMANT_DATA_GROUP;  /* scaffold reference for pool word C386 (based segment) */
extern int far match_position;  /* scaffold reference for pool word C388 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far match_length;  /* scaffold reference for pool word C38A (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far Dx8;  /* scaffold reference for pool word C38C (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far pack_buf;  /* scaffold reference for pool word C38E (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far Scycle;  /* scaffold reference for pool word C390 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far EditColumns;  /* scaffold reference for pool word C392 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far MiscStrs;  /* scaffold reference for pool word C394 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far Dy8;  /* scaffold reference for pool word C396 (segment 8, MAPSYM_SITE_NAME) */
extern int far Dx9;  /* scaffold reference for pool word C398 (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far LastQueenPlane;  /* scaffold reference for pool word C39A (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far EditDragPnt;  /* scaffold reference for pool word C39C (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far Dy9;  /* scaffold reference for pool word C39E (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far SMode;  /* scaffold reference for pool word C3A0 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far TurnTab;  /* scaffold reference for pool word C3A2 (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far modeButtonState;  /* scaffold reference for pool word C3A4 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far TileMassYR;  /* scaffold reference for pool word C3A6 (segment 9, MAPSYM_SITE_NAME) */
extern int far TileMassXR;  /* scaffold reference for pool word C3A8 (segment 9, MAPSYM_SITE_NAME) */

void far pool_stub_DoAntSimR(void);
void far pool_stub_DoNestAntR(void);
void far pool_stub_RaidInR(void);
void far pool_stub_DoNestFightR(void);
void far pool_stub_SimEggR(void);
void far pool_stub_SimQueenR(void);
void far pool_stub_QueenMoveR(void);

#pragma alloc_text(POOLSTUB_TEXT, pool_stub_DoAntSimR)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_DoNestAntR)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_RaidInR)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_DoNestFightR)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_SimEggR)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_SimQueenR)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_QueenMoveR)

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _DoAntSimR.
 * It only reproduces the object's selector-pool allocation order for the
 * words C382 C384; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_DoAntSimR(void)
{
    volatile int t;

    t = ListIndexR;
    t = (int)Tindex;
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _DoNestAntR.
 * It only reproduces the object's selector-pool allocation order for the
 * words C386 C388 C38A C38C C38E C390 C392; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_DoNestAntR(void)
{
    volatile int t;

    t = pool_segment_ref_SIMANT_DATA_GROUP;
    t = match_position;
    t = match_length;
    t = Dx8;
    t = pack_buf;
    t = Scycle;
    t = EditColumns;
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _RaidInR.
 * It only reproduces the object's selector-pool allocation order for the
 * words C394; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_RaidInR(void)
{
    volatile int t;

    t = MiscStrs;
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _DoNestFightR.
 * It only reproduces the object's selector-pool allocation order for the
 * words C396 C398; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_DoNestFightR(void)
{
    volatile int t;

    t = Dy8;
    t = Dx9;
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _SimEggR.
 * It only reproduces the object's selector-pool allocation order for the
 * words C39A C39C C39E; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_SimEggR(void)
{
    volatile int t;

    t = LastQueenPlane;
    t = EditDragPnt;
    t = Dy9;
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _SimQueenR.
 * It only reproduces the object's selector-pool allocation order for the
 * words C3A0 C3A2 C3A4; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_SimQueenR(void)
{
    volatile int t;

    t = SMode;
    t = TurnTab;
    t = modeButtonState;
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _QueenMoveR.
 * It only reproduces the object's selector-pool allocation order for the
 * words C3A6 C3A8; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_QueenMoveR(void)
{
    volatile int t;

    t = TileMassYR;
    t = TileMassXR;
}

int far GetOutR(int x)
{
    
    int raw;

    if (MapR[x << 6] == 0x18) {
        raw = RlistT[Tindex];
        RlistT[Tindex] = 0;
        if (HoleMapR[x] == 0)
            MakeNewHoleR(x);
        if (ExitHole(HoleMapR[x], x, SRand8() + (raw & 0xf8),
                      RlistM[Tindex], RlistS[Tindex]) != 0) {
            LifeR[(x << 6) + 1] = 0;
            return 1;
        }
        RlistT[Tindex] = raw;
        RlistM[Tindex] = 0;
        return 0;
    }

    if (ExitMapR[x << 6] != 0)
        ExitMapR[x << 6]--;

    if (SRand2() != 0) {
        if (x > 0 && IsItDirt(MapR[(x << 6) - 0x3f]) != 0)
            DigTileThemR(x - 1, 1);
    } else {
        if (x < 0x3f && IsItDirt(MapR[(x << 6) + 0x41]) != 0)
            DigTileThemR(x + 1, 1);
    }

    TryMoveDirR(x, 1, SRand8());
    return 0;
}

