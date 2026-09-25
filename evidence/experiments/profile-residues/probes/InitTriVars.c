/* Candidate translation unit simant_B324_InitTriVars_6_scaffold: composed from preserved exact-body sources
 * in MAPSYM order. Internal evidence id, not a historical filename.
 * Members: _InitTriVars, _OpenCasteWindow, _OpenModeWindow, _BoundPointToTri, _cvtLevels2IdealCaste
 * SCAFFOLDED: unclaimed members _win_CasteControlChanged are stand-ins in POOLSTUB_TEXT (pool order only, never compared). */

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

extern int far casteVerts;  /* scaffold reference for pool word C126 (segment 9, MAPSYM_SITE_NAME) */

void far pool_stub_win_CasteControlChanged(void);
void far OpenCasteWindow(void);
void far OpenModeWindow(void);
void far BoundPointToTri(struct Point far *pt, struct Rect far *r);
void far cvtLevels2IdealCaste(int far *ideal);

#pragma alloc_text(POOLSTUB_TEXT, pool_stub_win_CasteControlChanged)
#pragma alloc_text(RUN2_TEXT, OpenCasteWindow, OpenModeWindow)
#pragma alloc_text(RUN3_TEXT, BoundPointToTri)
#pragma alloc_text(RUN4_TEXT, cvtLevels2IdealCaste)

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
 * words C126 C128; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_win_CasteControlChanged(void)
{
    volatile int t;

    t = casteVerts;
    t = casteLevels[0];
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

