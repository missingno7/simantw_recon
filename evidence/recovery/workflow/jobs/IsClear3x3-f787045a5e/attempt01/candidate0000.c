/*
 * Hypothesis: the center tile must return exactly one from IsClearTile;
 * then each of the eight signed Dx8/Dy8 stencil offsets must also pass the
 * same predicate.  The first coordinate is fixed, the second adds Dx8,
 * and the third adds Dy8 at the observed +8 table displacement.
 */
extern int near IsClearTile(int x, int y, int type);
extern signed char far Dx8[];
extern signed char far Dy8[];

int far IsClear3x3(int x, int y, int type)
{
    int index;

    if (IsClearTile(x, y, type) != 1)
        return 0;
    for (index = 0; index < 8; ++index) {
        if (!IsClearTile(x, y + Dx8[index],
                        type + Dy8[index + 8]))
            return 0;
    }
    return 1;
}
