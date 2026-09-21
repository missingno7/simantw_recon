/*
 * GBoxFillOutline: fill a rectangle in the background colour and, for a
 * nonzero thickness, frame it in the foreground colour with the same four
 * GBoxFill bars as GBoxOutline (top and bottom bars between the inset
 * left/right edges, then the full-height left and right bars).  The
 * x2/y2 edges are exclusive.
 */
extern int near _backColor;
extern int near _foreColor;
extern void far GBoxFill(int x1, int y1, int x2, int y2, int color);

void far GBoxFillOutline(int x1, int y1, int x2, int y2, int thick)
{
    GBoxFill(x1, y1, x2, y2, _backColor);
    if (thick != 0) {
        GBoxFill(thick + x1, thick + y1 - 1, x2 - thick - 1, y1, _foreColor);
        GBoxFill(thick + x1, y2 - thick, x2 - thick - 1, y2 - 1, _foreColor);
        GBoxFill(thick + x1 - 1, y1, x1, y2 - 1, _foreColor);
        GBoxFill(x2 - 1, y1, x2 - thick, y2 - 1, _foreColor);
    }
}
