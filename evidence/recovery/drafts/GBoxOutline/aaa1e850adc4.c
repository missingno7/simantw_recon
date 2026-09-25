/*
 * GBoxOutline: draw a rectangular frame of the given thickness in the
 * current foreground colour.  Nothing is drawn for a zero thickness.  The
 * frame is four GBoxFill bars given by their corner pairs: the top bar
 * between the inset left/right edges from y1 down thick-1 rows, the bottom
 * bar over the last thick rows above y2, then the full-height left and
 * right bars.  The x2/y2 edges are exclusive, so bars end at x2-1/y2-1.
 * MSC shares x1+thick, x2-thick(-1), thick and y2-1 between the calls.
 */
extern int near _foreColor;
extern void far GBoxFill(int x1, int y1, int x2, int y2, int color);

void far GBoxOutline(int x1, int y1, int x2, int y2, int thick)
{
    if (thick != 0) {
        GBoxFill(thick + x1, thick + y1 - 1, x2 - thick - 1, y1, _foreColor);
        GBoxFill(thick + x1, y2 - thick, x2 - thick - 1, y2 - 1, _foreColor);
        GBoxFill(thick + x1 - 1, y1, x1, y2 - 1, _foreColor);
        GBoxFill(x2 - 1, y1, x2 - thick, y2 - 1, _foreColor);
    }
}
