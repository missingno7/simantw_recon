/* Candidate translation unit simant1_2D4E_MakeNewTailB_1_scaffold: composed from preserved exact-body sources
 * in MAPSYM order. Internal evidence id, not a historical filename.
 * Members: _MakeNewTailB
 * SCAFFOLDED: unclaimed members _DoAntSimB, _DoNestAntB, _RaidInB, _DoNestFightB are stand-ins in POOLSTUB_TEXT (pool order only, never compared). */

struct BListPlanes {
    unsigned char x[502];
    unsigned char y[502];
    unsigned char m[502];
    unsigned char t[502];
    unsigned char s[502];
};
extern struct BListPlanes far BlistX;
extern signed char far Dx8[];
extern signed char far Dy8[];
extern void far AddAntToBList(int, int, int, int, int);

extern int far ListIndexB;  /* scaffold reference for pool word C34E (segment 9, MAPSYM_SITE_NAME) */
extern int far Tindex;  /* scaffold reference for pool word C350 (segment 9, MAPSYM_SITE_NAME) */
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

    t = *(int far *)&BlistX;
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

void far MakeNewTailB(int index)
{
    unsigned char type;
    int direction;
    int life;
    int column;

    type = BlistX.t[index];
    direction = type & 7;
    direction ^= 4;
    life = BlistX.x[index] + (signed char)Dx8[direction];
    column = BlistX.y[index] + (signed char)Dy8[direction];
    AddAntToBList(life, column, type + 8, 9, 0);
}

