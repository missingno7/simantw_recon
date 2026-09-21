/*
 * IsPointInIsoTri: test whether a far point lies inside the isoceles
 * triangle inscribed in a far rectangle whose apex is at the bottom
 * centre (same triangle geometry as BoundPointToTri). Returns nonzero
 * if the point's y is within [top, bottom) and its x is bounded by the
 * left edge (apex to top-left corner) and the right edge (apex to
 * top-right corner), each computed with a 32-bit product and the
 * runtime long division.
 */
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
    long edge1;
    long edge2;

    top = r->top;
    bottom = r->bottom;
    right = r->right;
    left = r->left;
    mid = (right + left) / 2;
    x = pt->x;
    y = pt->y;
    if (y < bottom && y >= top) {
        edge1 = LDIV(left - mid, y - bottom, bottom - top) + left;
        if (edge1 > x || (edge2 = LDIV(mid - right, y - top, top - bottom) + mid) < x)
            return 0;
        return 1;
    }
    return 0;
}
