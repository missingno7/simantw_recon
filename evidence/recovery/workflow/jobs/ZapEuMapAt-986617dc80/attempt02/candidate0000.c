/*
 * Hypothesis: after TileIsVisible accepts the plane/coordinate triple, this
 * routine bounds-checks the edit-map coordinates and marks the corresponding
 * word invalid.  editWidth and editHeight are the packet's exact MAPSYM
 * bindings.  The far map pointer at DS:0x1442 has no MAPSYM name, so it is
 * represented as an ordinary far-pointer declaration rather than a literal
 * address or invented address arithmetic.
 */
extern int near editWidth;
extern int near editHeight;
extern int far TileIsVisible(int plane, int x, int y);
extern int far EuMap[];

void far ZapEuMapAt(int plane, int x, int y)
{
    register int xReg;

    xReg = x;
    if (TileIsVisible(plane, xReg, y) != 1)
        return;

    if (xReg < 0 || xReg >= editWidth || y < 0 || y >= editHeight)
        return;

    EuMap[y * editWidth + xReg] = -1;
}
