/*
 * GRectOutline: fill a rectangular frame of the given thickness.  A
 * null rectangle does nothing; its four edges are copied to locals, and
 * for a nonzero thickness the same four bars as GBoxOutline (top and
 * bottom between the inset left/right edges, then the full-height left
 * and right bars) are filled with GBoxFill in the current foreground colour.  The right/bottom edges are
 * exclusive.
 */
struct Rect {
    int left;
    int top;
    int right;
    int bottom;
};

extern int near _foreColor;
extern void far GBoxFill(int x1, int y1, int x2, int y2, int color);

void far GRectOutline(struct Rect far *rect, int thick)
{
    int x1;
    int y1;
    int x2;
    int y2;
    struct Rect far *p;

    p = rect;
    if (p == 0)
        return;
    x1 = p->left;
    y1 = p->top;
    x2 = p->right;
    y2 = p->bottom;
    if (thick != 0) {
        GBoxFill(thick + x1, thick + y1 - 1, x2 - thick - 1, y1, _foreColor);
        GBoxFill(thick + x1, y2 - thick, x2 - thick - 1, y2 - 1, _foreColor);
        GBoxFill(thick + x1 - 1, y1, x1, y2 - 1, _foreColor);
        GBoxFill(x2 - 1, y1, x2 - thick, y2 - 1, _foreColor);
    }
}

