/* Candidate translation unit simant1_0000_SimQueenA_1_scaffold: composed from preserved exact-body sources
 * in MAPSYM order. Internal evidence id, not a historical filename.
 * Members: _SimQueenA
 * SCAFFOLDED: unclaimed members _DoAntSim, _DoSmells, _FeedAnts, _DoAntSimA are stand-ins in POOLSTUB_TEXT (pool order only, never compared). */

extern unsigned char near LifeA[128][64];
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) AlistT[];
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) AlistX[];
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) AlistY[];
extern unsigned char far Dx8;
#define AT(off) ((&Dx8)[off])
extern char far Dy8[];
#define DY(i) Dy8[i]
#define DX(i) ((char)(&Dx8)[i])
extern int far FindInAList(int x, int y);
extern int far SMode;

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
extern int __based(__segname("SIMANT_DATA_GROUP")) pool_segment_ref_SIMANT_DATA_GROUP;  /* scaffold reference for pool word C318 (based segment) */
extern int far MiscStrs;  /* scaffold reference for pool word C31A (segment 9, SEGMENT_REPRESENTATIVE) */

void far pool_stub_DoAntSim(void);
void far pool_stub_DoSmells(void);
void far pool_stub_FeedAnts(void);
void far pool_stub_DoAntSimA(void);

#pragma alloc_text(POOLSTUB_TEXT, pool_stub_DoAntSim)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_DoSmells)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_FeedAnts)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_DoAntSimA)

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
 * words C314 C316 C318 C31A C31C C31E; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_DoAntSimA(void)
{
    volatile int t;

    t = ListIndexA;
    t = Tindex;
    t = pool_segment_ref_SIMANT_DATA_GROUP;
    t = MiscStrs;
    t = Dy8[0];
    t = (int)Dx8;
}

void near SimQueenA(int ant)
{
    int x;
    int y;
    int type;
    int nx;
    int ny;
    int dead;

    x = AlistX[ant];
    y = (unsigned char)AlistY[ant];
    type = AlistT[ant];
    LifeA[x][y] = type;
    if ((type & 0x7f) > 0x67) {
        nx = DX(type & 7) + x;
        ny = DY(type & 7) + y;
        if (LifeA[nx][ny] - type == -8)
            dead = 0;
        else if (FindInAList(nx, ny) >= 0)
            dead = 0;
        else
            dead = 1;
        if (dead) {
            LifeA[x][y] = 0;
            AlistT[ant] = 0;
        }
    }
}

