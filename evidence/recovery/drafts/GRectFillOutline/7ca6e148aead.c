/*
 * GRectFillOutline: fill a rectangle in the background colour, then frame
 * it with a nonzero-thickness foreground border using the same four
 * GBoxFill bars as the admitted GBoxFillOutline/GRectOutline (top and
 * bottom bars between the inset left/right edges, then the full-height
 * left and right bars).  A null rectangle pointer does nothing.  The
 * right/bottom edges are exclusive.
 */
struct Rect {
    int left;
    int top;
    int right;
    int bottom;
};

extern int near _backColor;
extern int near _foreColor;
extern void far GBoxFill(int x1, int y1, int x2, int y2, int color);

void far GRectFillOutline(struct Rect far *rect, int thick)
{
    int x1;
    int y1;
    int x2;
    int y2;

    if (rect == 0)
        return;
    GBoxFill(rect->left, rect->top, rect->right, rect->bottom, _backColor);
    x1 = rect->left;
    y1 = rect->top;
    x2 = rect->right;
    y2 = rect->bottom;
    if (thick != 0) {
        GBoxFill(thick + x1, thick + y1 - 1, x2 - thick - 1, y1, _foreColor);
        GBoxFill(thick + x1, y2 - thick, x2 - thick - 1, y2 - 1, _foreColor);
        GBoxFill(thick + x1 - 1, y1, x1, y2 - 1, _foreColor);
        GBoxFill(x2 - 1, y1, x2 - thick, y2 - 1, _foreColor);
    }
}
