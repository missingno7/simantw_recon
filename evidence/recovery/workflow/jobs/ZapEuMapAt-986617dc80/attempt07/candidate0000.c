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

void far ZapEuMapAt(int plane, int x, int y)
{
    if (TileIsVisible(plane, x, y) != 1)
        goto done;
    if (x < 0)
        goto done;
    if (x >= editWidth)
        goto done;
    if (y < 0)
        goto done;
    if (y >= editHeight)
        goto done;

    EuMap[y * editWidth + x] = -1;

done:
    return;
}
