/* Candidate translation unit simtwo_3EF8_KillAntLion_1_scaffold: composed from preserved exact-body sources
 * in MAPSYM order. Internal evidence id, not a historical filename.
 * Members: _KillAntLion
 * SCAFFOLDED: unclaimed members _InitSow, _DoSow, _InitAntLions are stand-ins in POOLSTUB_TEXT (pool order only, never compared). */

extern unsigned char far LionListX[];
extern unsigned char far LionListY[];
extern unsigned char far LionListT[];
extern unsigned char far LionListM[];
extern unsigned char far LionListS[];
extern int far LionIndex;
extern void far SetMap(int plane, int x, int y, int value);

extern int far match_position;  /* scaffold reference for pool word C574 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far match_length;  /* scaffold reference for pool word C576 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far pack_buf;  /* scaffold reference for pool word C578 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far Scycle;  /* scaffold reference for pool word C57A (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far Dx8;  /* scaffold reference for pool word C57C (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far Dy8;  /* scaffold reference for pool word C57E (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far Dx9;  /* scaffold reference for pool word C580 (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far AntsEatenByLions;  /* scaffold reference for pool word C584 (segment 9, MAPSYM_SITE_NAME) */

void far pool_stub_InitSow(void);
void far pool_stub_DoSow(void);
void far pool_stub_InitAntLions(void);

#pragma alloc_text(POOLSTUB_TEXT, pool_stub_InitSow)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_DoSow)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_InitAntLions)

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _InitSow.
 * It only reproduces the object's selector-pool allocation order for the
 * words C574 C576 C578 C57A C57C; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_InitSow(void)
{
    volatile int t;

    t = match_position;
    t = match_length;
    t = pack_buf;
    t = Scycle;
    t = Dx8;
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _DoSow.
 * It only reproduces the object's selector-pool allocation order for the
 * words C57E C580; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_DoSow(void)
{
    volatile int t;

    t = Dy8;
    t = Dx9;
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _InitAntLions.
 * It only reproduces the object's selector-pool allocation order for the
 * words C582 C584 C586 C588; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_InitAntLions(void)
{
    volatile int t;

    t = (int)LionIndex;
    t = AntsEatenByLions;
    t = LionListX[0];
    t = LionListY[0];
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

