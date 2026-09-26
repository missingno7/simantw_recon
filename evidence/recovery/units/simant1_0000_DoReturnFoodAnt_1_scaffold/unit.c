/* Candidate translation unit simant1_0000_DoReturnFoodAnt_1_scaffold: composed from preserved exact-body sources
 * in MAPSYM order. Internal evidence id, not a historical filename.
 * Members: _DoReturnFoodAnt
 * SCAFFOLDED: unclaimed members _DoAntSim, _DoSmells, _FeedAnts, _DoAntSimA, _DoRandAntA are stand-ins in POOLSTUB_TEXT (pool order only, never compared). */

extern unsigned char far Dx8;
#define AT(off) ((&Dx8)[off])
extern signed char far Dy8[];
extern char far TurnTab[8][8];
extern int far Barrier;
extern unsigned int far TERRAINset;
extern unsigned char near MapA[];
extern unsigned char near LifeA[];
extern int far IsValidA(int x, int y);
extern int far GetNestDir(int x, int y, int dir, int attribute);
extern int far SRand8(void);
extern void near GoInNest(int x, int y, int index);
extern void near JamScentRT(int x, int y, int scent);
extern void far JamScentBT(int x, int y, int scent);

extern int far Dx9;  /* scaffold reference for pool word C2FE (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far match_position;  /* scaffold reference for pool word C300 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far match_length;  /* scaffold reference for pool word C302 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far ModePopB;  /* scaffold reference for pool word C304 (segment 9, MAPSYM_SITE_NAME) */
extern int far ModePopR;  /* scaffold reference for pool word C306 (segment 9, MAPSYM_SITE_NAME) */
extern int far pack_buf;  /* scaffold reference for pool word C308 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far Dy9;  /* scaffold reference for pool word C30A (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far Cycle;  /* scaffold reference for pool word C30C (segment 9, MAPSYM_SITE_NAME) */
extern int far AlwaysHealthy;  /* scaffold reference for pool word C30E (segment 8, MAPSYM_SITE_NAME) */
extern int far Scycle;  /* scaffold reference for pool word C310 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far EditColumns;  /* scaffold reference for pool word C312 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far ListIndexA;  /* scaffold reference for pool word C314 (segment 9, MAPSYM_SITE_NAME) */
extern int far Tindex;  /* scaffold reference for pool word C316 (segment 9, MAPSYM_SITE_NAME) */
extern int far MiscStrs;  /* scaffold reference for pool word C31A (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far relSearchDirs;  /* scaffold reference for pool word C322 (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far LastQueenPlane;  /* scaffold reference for pool word C324 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far EditDragPnt;  /* scaffold reference for pool word C326 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far SMode;  /* scaffold reference for pool word C328 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far modeButtonState;  /* scaffold reference for pool word C32A (segment 9, SEGMENT_REPRESENTATIVE) */

void far pool_stub_DoAntSim(void);
void far pool_stub_DoSmells(void);
void far pool_stub_FeedAnts(void);
void far pool_stub_DoAntSimA(void);
void far pool_stub_DoRandAntA(void);

#pragma alloc_text(POOLSTUB_TEXT, pool_stub_DoAntSim)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_DoSmells)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_FeedAnts)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_DoAntSimA)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_DoRandAntA)

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _DoAntSim.
 * It only reproduces the object's selector-pool allocation order for the
 * words C2FE C300 C302 C304 C306 C308 C30A; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_DoAntSim(void)
{
    volatile int t;

    t = Dx9;
    t = match_position;
    t = match_length;
    t = ModePopB;
    t = ModePopR;
    t = pack_buf;
    t = Dy9;
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _DoSmells.
 * It only reproduces the object's selector-pool allocation order for the
 * words C30C; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_DoSmells(void)
{
    volatile int t;

    t = Cycle;
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _FeedAnts.
 * It only reproduces the object's selector-pool allocation order for the
 * words C30E C310 C312; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_FeedAnts(void)
{
    volatile int t;

    t = AlwaysHealthy;
    t = Scycle;
    t = EditColumns;
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _DoAntSimA.
 * It only reproduces the object's selector-pool allocation order for the
 * words C314 C316 C318 C31A C31C C31E C320 C322 C324 C326 C328 C32A; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_DoAntSimA(void)
{
    volatile int t;

    t = ListIndexA;
    t = Tindex;
    t = (int)Dx8;
    t = MiscStrs;
    t = Dy8[0];
    t = (int)Dx8;
    t = (int)TERRAINset;
    t = relSearchDirs;
    t = LastQueenPlane;
    t = EditDragPnt;
    t = SMode;
    t = modeButtonState;
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _DoRandAntA.
 * It only reproduces the object's selector-pool allocation order for the
 * words C32C C32E; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_DoRandAntA(void)
{
    volatile int t;

    t = (int)Barrier;
    t = TurnTab[0][0];
}

void near DoReturnFoodAnt(int index)
{
    int x, y;
    int hole;
    int flags;
    int tile;
    int attribute;
    int ndir;
    int nx, ny;

    x = AT(index + 0x23a4) & 0xff;
    y = AT(index + 0x278e);
    attribute = AT(index + 0x2f62);

    if (!IsValidA(x, y)) {
        hole = 0;
    } else if (TERRAINset == 0) {
        if (MapA[x * 64 + y] == 0x50)
            hole = 1;
        else
            hole = 0;
    } else {
        tile = MapA[x * 64 + y];
        if (tile < 0x80)
            hole = 0;
        else if (tile > 0x8f)
            hole = 0;
        else
            hole = 1;
    }

    if (hole) {
        GoInNest(x, y, index);
        return;
    }

    flags = attribute & 0xf8;
    ndir = GetNestDir(x, y, attribute & 7, attribute);
    nx = x + (signed char)AT(ndir);
    ny = y + Dy8[ndir];

    if (MapA[(nx << 6) + ny] > Barrier) {
        AT(index + 0x2f62) = TurnTab[attribute & 7][SRand8()] | flags;
        LifeA[(x << 6) + y] = AT(index + 0x2f62);
        return;
    }

    LifeA[(nx << 6) + ny] = ndir | flags;
    AT(index + 0x2f62) = ndir | flags;
    LifeA[(x << 6) + y] = 0;
    AT(index + 0x23a4) = nx;
    AT(index + 0x278e) = ny;

    if (AT(index + 0x334c) != 0) {
        AT(index + 0x334c)--;
        if (attribute & 0x80)
            JamScentRT(nx, ny, AT(index + 0x334c));
        else
            JamScentBT(nx, ny, AT(index + 0x334c));
    }
}

