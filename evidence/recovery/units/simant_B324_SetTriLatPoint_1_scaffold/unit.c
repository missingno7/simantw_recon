/* Candidate translation unit simant_B324_SetTriLatPoint_1_scaffold: composed from preserved exact-body sources
 * in MAPSYM order. Internal evidence id, not a historical filename.
 * Members: _SetTriLatPoint
 * SCAFFOLDED: unclaimed members _InitTriVars are stand-ins in POOLSTUB_TEXT (pool order only, never compared). */

struct TriLevel {
    unsigned int frac;
    int unused2;
    unsigned int weight;
};
struct Rect {
    int left;
    int top;
    int right;
    int bottom;
};
struct Point {
    int x;
    int y;
};
extern unsigned int far triWidth;
extern unsigned int far triWidthL;
extern unsigned int far triHeight;

extern int far match_position;  /* scaffold reference for pool word C11E (segment 9, SEGMENT_REPRESENTATIVE) */

void far pool_stub_InitTriVars(void);

#pragma alloc_text(POOLSTUB_TEXT, pool_stub_InitTriVars)

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _InitTriVars.
 * It only reproduces the object's selector-pool allocation order for the
 * words C11C C11E C120 C122; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_InitTriVars(void)
{
    volatile int t;

    t = (int)triWidth;
    t = match_position;
    t = (int)triWidthL;
    t = (int)triHeight;
}

void far SetTriLatPoint(struct TriLevel far *level, struct Rect far *rect, struct Point far *out)
{
    unsigned int widthTerm;
    int row;
    int x;
    unsigned long fracL;
    fracL = level->frac;
    out->y = (triHeight - 2) * (0xFFFFUL - fracL) / 65535UL + rect->top;

    widthTerm = triWidthL * fracL / 65535UL;
    row = triWidth - 2 * widthTerm;

    if (level->frac == 0xFFFF || row < 3) {
        out->x = rect->left + 2;
        return;
    }
    x = (long)(row - 3) * level->weight / (long)(0xFFFF - level->frac) + rect->right + widthTerm;
    out->x = x + 2;
}

