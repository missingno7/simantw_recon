/* Candidate translation unit simtwo_3EF8_FindInLionList_1_scaffold: composed from preserved exact-body sources
 * in MAPSYM order. Internal evidence id, not a historical filename.
 * Members: _FindInLionList
 * SCAFFOLDED: unclaimed members _InitSow, _DoSow, _InitAntLions are stand-ins in POOLSTUB_TEXT (pool order only, never compared). */

extern int far LionIndex;
extern unsigned char far LionListX[];
extern unsigned char far LionListY[];

extern int far match_position;  /* scaffold reference for pool word C574 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far match_length;  /* scaffold reference for pool word C576 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far pack_buf;  /* scaffold reference for pool word C578 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far Scycle;  /* scaffold reference for pool word C57A (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far Dx8;  /* scaffold reference for pool word C57C (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far Dy8;  /* scaffold reference for pool word C57E (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far Dx9;  /* scaffold reference for pool word C580 (segment 8, SEGMENT_REPRESENTATIVE) */

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
 * words C582; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_InitAntLions(void)
{
    volatile int t;

    t = (int)LionIndex;
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

