/*
 * GRectInvOutline: invert a rectangular frame of the given thickness.  A
 * null rectangle does nothing; its four edges are copied to locals, and
 * for a nonzero thickness the same four bars as GBoxOutline (top and
 * bottom between the inset left/right edges, then the full-height left
 * and right bars) are inverted with GInvBox.  The right/bottom edges are
 * exclusive.
 */
struct Rect {
    int left;
    int top;
    int right;
    int bottom;
};

extern void far GInvBox(int x1, int y1, int x2, int y2);

void far GRectInvOutline(struct Rect far *rect, int thick)
{
    int x1;
    int y1;
    int x2;
    int y2;
    struct { struct Rect far *p; } h;

    h.p = rect;
    if (h.p == 0)
        return;
    x1 = h.p->left;
    y1 = h.p->top;
    x2 = h.p->right;
    y2 = h.p->bottom;
    if (thick != 0) {
        GInvBox(thick + x1, thick + y1 - 1, x2 - thick - 1, y1);
        GInvBox(thick + x1, y2 - thick, x2 - thick - 1, y2 - 1);
        GInvBox(thick + x1 - 1, y1, x1, y2 - 1);
        GInvBox(x2 - 1, y1, x2 - thick, y2 - 1);
    }
}

