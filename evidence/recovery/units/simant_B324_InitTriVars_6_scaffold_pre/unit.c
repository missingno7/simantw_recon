/* Candidate translation unit simant_B324_InitTriVars_6_scaffold_pre: composed from preserved exact-body sources
 * in MAPSYM order. Internal evidence id, not a historical filename.
 * Members: _InitTriVars, _OpenCasteWindow, _OpenModeWindow, _BoundPointToTri, _cvtLevels2IdealCaste, _initControls
 * SCAFFOLDED: unclaimed members _win_CasteControlChanged, _win_ModeControlChanged, _UpdateCasteWindow, _UpdateModeWindow, _ProcCasteEvent are stand-ins in POOLSTUB_TEXT (pool order only, never compared). */

struct WinRect {
    int left;
    int top;
    int right;
    int bottom;
};
struct TriPoints {
    int apexX;
    int apexY;
    int leftX;
    int leftY;
    int rightX;
    int rightY;
};
extern unsigned int far triWidth;
extern unsigned int far triWidthR;
extern unsigned int far triWidthL;
extern unsigned int far triHeight;
extern long far leftYSlope;
extern void far win_GetObjRect(int object, struct WinRect far *rect);
struct BitmapSize {
    int width;
    int height;
};
extern unsigned char near displayType;
extern int near modeBitmap;
extern unsigned int near casteBitmap;
extern void far win_Recalc(int window);
extern void far gr_BitMapSize(struct BitmapSize far *size, int bitmap);
extern long far BitmapImageSize(int width, int height, int depth);
extern unsigned int far mem_Alloc(unsigned long bytes, int kind, char far *name);
extern void far win_CasteControlChanged(void);
extern void far win_MakeObjInvisible(int object);
extern void far win_Open(int window);
extern void far UpdateCasteWindow(void);
extern void far win_MakeGroupInvisible(int window, int group);
extern void far win_ModeControlChanged(void);
extern void far UpdateModeWindow(void);
struct Point { int x; int y; };
struct Rect { int left; int top; int right; int bottom; };
#define LDIV(a, b, c) ((long)(a) * (b) / (long)(c))
extern volatile unsigned int far casteLevels[];
#define HUNDRED 100UL
#define FIFTY 50UL
extern struct BitmapSize far knobSize;
extern int far ModeAuto;
extern int far CasteAuto;
extern int far ShowPercentMode;
extern int far ShowPercentCaste;
extern int far modeButtonState;
extern int far casteButtonState;
extern int far modeLevels[3];
extern int far modeLevelDefaults[3];
extern int far modeSetLevels[][3];
extern int far casteLevelDefaults[3];
extern int far casteSetLevels[][3];
extern int far IdealCaste[];

extern int far casteVerts;  /* scaffold reference for pool word C126 (segment 9, MAPSYM_SITE_NAME) */
extern int far casteKnobPnt;  /* scaffold reference for pool word C12A (segment 9, MAPSYM_SITE_NAME) */
extern int far casteAnimHandle;  /* scaffold reference for pool word C12C (segment 9, MAPSYM_SITE_NAME) */
extern int far modeVerts;  /* scaffold reference for pool word C12E (segment 9, MAPSYM_SITE_NAME) */
extern int far match_position;  /* scaffold reference for pool word C130 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far modeKnobPnt;  /* scaffold reference for pool word C132 (segment 9, MAPSYM_SITE_NAME) */
extern int far modeAnimHandle;  /* scaffold reference for pool word C134 (segment 9, MAPSYM_SITE_NAME) */
extern int far match_length;  /* scaffold reference for pool word C136 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far casteAnimObj;  /* scaffold reference for pool word C138 (segment 9, MAPSYM_SITE_NAME) */
extern int far modeAnimObj;  /* scaffold reference for pool word C13A (segment 9, MAPSYM_SITE_NAME) */
extern int far Dx8;  /* scaffold reference for pool word C13E (segment 8, SEGMENT_REPRESENTATIVE) */

void far pool_stub_win_CasteControlChanged(void);
void far pool_stub_win_ModeControlChanged(void);
void far pool_stub_UpdateCasteWindow(void);
void far pool_stub_UpdateModeWindow(void);
void far pool_stub_ProcCasteEvent(void);
void far OpenCasteWindow(void);
void far OpenModeWindow(void);
void far BoundPointToTri(struct Point far *pt, struct Rect far *r);
void far cvtLevels2IdealCaste(int far *ideal);
void far initControls(void);

#pragma alloc_text(POOLSTUB_TEXT, pool_stub_win_CasteControlChanged)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_win_ModeControlChanged)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_UpdateCasteWindow)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_UpdateModeWindow)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_ProcCasteEvent)
#pragma alloc_text(RUN2_TEXT, OpenCasteWindow, OpenModeWindow)
#pragma alloc_text(RUN3_TEXT, BoundPointToTri)
#pragma alloc_text(RUN4_TEXT, cvtLevels2IdealCaste)
#pragma alloc_text(RUN5_TEXT, initControls)

void far InitTriVars(int object, struct TriPoints far *tri)
{
    struct WinRect rect;
    unsigned int halfWidth;
#define HALF halfWidth

    win_GetObjRect(object, &rect);
    triWidth = rect.right - rect.left;
    halfWidth = triWidth >> 1;
    triWidthR = halfWidth;
    triWidthL = halfWidth;
    triHeight = rect.bottom - rect.top;
    leftYSlope = ((long)HALF << 8) / (long)triHeight;
    tri->apexX = HALF + rect.left;
    tri->apexY = rect.top;
    tri->leftY = tri->rightY = rect.bottom;
    tri->leftX = rect.left;
    tri->rightX = rect.right;
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _win_CasteControlChanged.
 * It only reproduces the object's selector-pool allocation order for the
 * words C126 C128 C12A C12C; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_win_CasteControlChanged(void)
{
    volatile int t;

    t = casteVerts;
    t = casteLevels[0];
    t = casteKnobPnt;
    t = casteAnimHandle;
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _win_ModeControlChanged.
 * It only reproduces the object's selector-pool allocation order for the
 * words C12E C130 C132 C134; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_win_ModeControlChanged(void)
{
    volatile int t;

    t = modeVerts;
    t = match_position;
    t = modeKnobPnt;
    t = modeAnimHandle;
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _UpdateCasteWindow.
 * It only reproduces the object's selector-pool allocation order for the
 * words C136 C138; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_UpdateCasteWindow(void)
{
    volatile int t;

    t = match_length;
    t = casteAnimObj;
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _UpdateModeWindow.
 * It only reproduces the object's selector-pool allocation order for the
 * words C13A; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_UpdateModeWindow(void)
{
    volatile int t;

    t = modeAnimObj;
}

void far OpenCasteWindow(void)
{
    long bytes;
    struct BitmapSize size;

    win_Recalc(0x1300);
    if (modeBitmap == 0) {
        gr_BitMapSize(&size, 0x120c);
        casteBitmap = mem_Alloc((((displayType & 1) == 0)
                                     ? BitmapImageSize(size.width, size.height, 4)
                                     : BitmapImageSize(size.width, size.height, 1)) + 4,
                                1, "castebuf");
    }
    win_CasteControlChanged();
    win_MakeObjInvisible(0x1302);
    win_Open(0x1300);
    UpdateCasteWindow();
    win_MakeGroupInvisible(0x1300, 4);
}

#define modeBitmap (*(unsigned int near *)&modeBitmap)  /* shape view of the unit declaration for this member only */
void far OpenModeWindow(void)
{
    long bytes;
    struct BitmapSize size;

    win_Recalc(0x1200);
    if (modeBitmap == 0) {
        gr_BitMapSize(&size, 0x11f8);
        modeBitmap = mem_Alloc((((displayType & 1) == 0)
                                     ? BitmapImageSize(size.width, size.height, 4)
                                     : BitmapImageSize(size.width, size.height, 1)) + 4,
                                1, "modebuf");
    }
    win_ModeControlChanged();
    win_MakeObjInvisible(0x1202);
    win_Open(0x1200);
    UpdateModeWindow();
    win_MakeGroupInvisible(0x1200, 4);
}
#undef modeBitmap

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _ProcCasteEvent.
 * It only reproduces the object's selector-pool allocation order for the
 * words C13C C13E C140; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_ProcCasteEvent(void)
{
    volatile int t;

    t = (int)CasteAuto;
    t = Dx8;
    t = IdealCaste[0];
}

void far BoundPointToTri(struct Point far *pt, struct Rect far *r)
{
    int top;
    int bottom;
    int right;
    int left;
    int mid;
    int x;
    int y;
    int edge;
    int save;

    top = r->top;
    bottom = r->bottom - 1;
    right = r->right;
    left = r->left;
    mid = (right + left) / 2;
    x = pt->x;
    y = pt->y;
    if (y > bottom)
        y = bottom;
    else if (y < top)
        y = top;
    edge = LDIV(left - mid, y - bottom, bottom - top) + left;
    if (edge > x)
        x = edge;
    else {
        edge = LDIV(mid - right, y - top, top - bottom) + mid;
        if (edge < x)
            x = edge;
    }
    pt->x = x;
    pt->y = y;
}

void far cvtLevels2IdealCaste(int far *ideal)
{
    ideal[0] = (HUNDRED * casteLevels[1] + 0x3fff) / 0xffff;
    ideal[1] = (HUNDRED * casteLevels[2] + 0x3fff) / 0xffff;
    ideal[2] = (FIFTY * casteLevels[0] + 0x3fff) / 0xffff;
    ideal[3] = (FIFTY * casteLevels[0] + 0x3fff) / 0xffff;
}

#define casteLevels ((unsigned int far *)casteLevels)  /* shape view of the unit declaration for this member only */
void far initControls(void)
{
    struct WinRect rect;
    int i;

    gr_BitMapSize(&knobSize, 0x578);
    win_GetObjRect(0x120d, &rect);

    ModeAuto = 1;
    CasteAuto = 1;
    ShowPercentMode = 1;
    ShowPercentCaste = 1;
    modeButtonState = 0xffff;
    casteButtonState = 0xffff;

    for (i = 0; i < 3; i++) {
        modeLevels[i] = modeLevelDefaults[i];
        modeSetLevels[0][i] = modeLevelDefaults[i];
        casteLevels[i] = casteLevelDefaults[i];
        casteSetLevels[0][i] = casteLevelDefaults[i];
    }

    win_ModeControlChanged();
    win_CasteControlChanged();

    IdealCaste[0] = (HUNDRED * casteLevels[1] + 0x3fff) / 0xffff;
    IdealCaste[1] = (HUNDRED * casteLevels[2] + 0x3fff) / 0xffff;
    IdealCaste[2] = (FIFTY * casteLevels[0] + 0x3fff) / 0xffff;
    IdealCaste[3] = (FIFTY * casteLevels[0] + 0x3fff) / 0xffff;
}
#undef casteLevels

