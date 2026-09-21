/*
 * BoundPointToTri: clamp a far point into the triangle inscribed in a
 * far rectangle whose apex is at the bottom centre.  The y coordinate
 * is first clamped to [top, bottom-1].  The left edge runs from the
 * bottom-centre apex to the top-left corner: at height y it lies at
 * left + (left - mid) * (y - bottom) / (bottom - top), computed with a
 * 32-bit product and the runtime long division.  If the point is left
 * of it, x is moved onto the edge; otherwise the right edge, from the
 * apex to the top-right corner, mid + (mid - right) * (y - top) /
 * (top - bottom), bounds x from the right.  The clamped point is
 * stored back.
 */
struct Point { int x; int y; };
struct Rect { int left; int top; int right; int bottom; };

#define LDIV(a, b, c) ((long)(a) * (long)(b) / (long)(c))

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
    if (LDIV(left - mid, y - bottom, bottom - top) + left > x)
        x = LDIV(left - mid, y - bottom, bottom - top) + left;
    else if (LDIV(mid - right, y - top, top - bottom) + mid < x)
        x = LDIV(mid - right, y - top, top - bottom) + mid;
    pt->x = x;
    pt->y = y;
}
