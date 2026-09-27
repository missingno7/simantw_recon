/* Candidate translation unit simant_B324_IsPointInIsoTri_1_scaffold: composed from preserved exact-body sources
 * in MAPSYM order. Internal evidence id, not a historical filename.
 * Members: _IsPointInIsoTri
 * SCAFFOLDED: claimed members in 1 code runs; no pool stand-ins were needed. */

struct Point { int x; int y; };
struct Rect { int left; int top; int right; int bottom; };
#define LDIV(a, b, c) ((long)(a) * (b) / (long)(c))




int far IsPointInIsoTri(struct Point far *pt, struct Rect far *r)
{
    int top;
    int bottom;
    int right;
    int left;
    int mid;
    int x;
    int y;
    long edge;

    top = r->top;
    bottom = r->bottom;
    right = r->right;
    left = r->left;
    mid = (right + left) / 2;
    x = pt->x;
    y = pt->y;
    if (y >= bottom || y < top)
        return 0;
    edge = LDIV(left - mid, y - bottom, bottom - top) + left;
    if (edge > x)
        return 0;
    edge = LDIV(mid - right, y - top, top - bottom) + mid;
    if (edge < x)
        return 0;
    return 1;
}

