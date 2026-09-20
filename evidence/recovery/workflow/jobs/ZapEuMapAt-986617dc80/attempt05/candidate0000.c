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
extern int far * near EuMap;

void far ZapEuMapAt(int plane, int y, int x)
{
    if (TileIsVisible(plane, y, x) != 1)
        return;

    if (y < 0 || y >= editWidth || x < 0 || x >= editHeight)
        return;

    EuMap[x * editWidth + y] = -1;
}
