/* Candidate translation unit simant1_2D4E_KillTailB_2_scaffold: composed from preserved exact-body sources
 * in MAPSYM order. Internal evidence id, not a historical filename.
 * Members: _KillTailB, _LostHeadB
 * SCAFFOLDED: unclaimed members _DoAntSimB, _DoNestAntB, _RaidInB, _DoNestFightB are stand-ins in POOLSTUB_TEXT (pool order only, never compared). */

extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) BlistT[];
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) BlistY[];
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) BlistX[];
extern unsigned char far Dx8[];
extern unsigned char far Dy8[];
extern unsigned char near LifeB[128][64];
extern int far FindInBList(int x, int y, int ant);

extern int far ListIndexB;  /* scaffold reference for pool word C34E (segment 9, MAPSYM_SITE_NAME) */
extern int far Tindex;  /* scaffold reference for pool word C350 (segment 9, MAPSYM_SITE_NAME) */
extern int far BlistS;  /* scaffold reference for pool word C352 (segment 8, MAPSYM_SITE_NAME) */
extern int far match_position;  /* scaffold reference for pool word C354 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far match_length;  /* scaffold reference for pool word C356 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far Dx9;  /* scaffold reference for pool word C358 (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far pack_buf;  /* scaffold reference for pool word C35A (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far Scycle;  /* scaffold reference for pool word C35C (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far EditColumns;  /* scaffold reference for pool word C35E (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far MiscStrs;  /* scaffold reference for pool word C360 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far LastQueenPlane;  /* scaffold reference for pool word C362 (segment 9, SEGMENT_REPRESENTATIVE) */

void far pool_stub_DoAntSimB(void);
void far pool_stub_DoNestAntB(void);
void far pool_stub_RaidInB(void);
void far pool_stub_DoNestFightB(void);

#pragma alloc_text(POOLSTUB_TEXT, pool_stub_DoAntSimB)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_DoNestAntB)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_RaidInB)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_DoNestFightB)

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _DoAntSimB.
 * It only reproduces the object's selector-pool allocation order for the
 * words C34E C350; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_DoAntSimB(void)
{
    volatile int t;

    t = ListIndexB;
    t = Tindex;
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _DoNestAntB.
 * It only reproduces the object's selector-pool allocation order for the
 * words C352 C354 C356 C358 C35A C35C C35E C360; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_DoNestAntB(void)
{
    volatile int t;

    t = BlistS;
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

#define LifeB ((unsigned char near *)LifeB)  /* shape view of the unit declaration for this member only */
void KillTailB(int tail)
{
    unsigned char direction;
    unsigned int row;

    BlistT[tail] = 0;
    direction = BlistY[tail];
    row = *(unsigned int far *)(BlistX + tail);
    row &= 0xff;
    row <<= 6;
    LifeB[row + direction] = 0;
}
#undef LifeB

int far LostHeadB(int x, int y, int attr)
{
    int dir;
    int newY;
    int headMarker;
    int newX;
    unsigned char cell;
    dir = attr & 7;
    newY = (signed char)Dy8[dir];
    newX = x + (signed char)Dx8[dir];
    newY += y;
    headMarker = attr - 8;
    cell = ((unsigned char near *)LifeB)[(newX << 6) + newY];
    if (cell == headMarker)
        return 0;
    if (FindInBList(newX, newY, headMarker) >= 0)
        return 0;
    return 1;
}

