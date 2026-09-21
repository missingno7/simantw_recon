/*
 * InitTriVars: derive the triangle drawing variables for a window object.
 * The object's rectangle gives the far PACK triWidth (right-left), its
 * half in triWidthR and triWidthL, triHeight (bottom-top) and the long
 * fixed-point leftYSlope = height / (halfWidth << 8).  The caller's six
 * words receive the apex (left + halfWidth, top), the base-left corner
 * (left, bottom) and the base-right corner (right, bottom).
 */
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

void far InitTriVars(int object, struct TriPoints far *tri)
{
    struct WinRect rect;
    unsigned int halfWidth;
#define HALF halfWidth

    win_GetObjRect(object, &rect);
    triWidth = rect.right - rect.left;
    triWidthR = triWidthL = triWidth >> 1;
    triHeight = rect.bottom - rect.top;
    leftYSlope = (long)triHeight / ((long)HALF << 8);
    tri->apexX = HALF + rect.left;
    tri->apexY = rect.top;
    tri->leftY = tri->rightY = rect.bottom;
    tri->leftX = rect.left;
    tri->rightX = rect.right;
}
