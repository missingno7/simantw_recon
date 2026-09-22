/*
 * IsClear3x3 checks a tile and its eight neighbours through IsClearTile.
 * Call-site argument order is derived from the observed push sequence
 * (compiler pushes arguments right to left): the first call pushes x, y,
 * type in that execution order, so the written call is
 * IsClearTile(type, y, x).  In the loop the far stencil arrays are added
 * cross-wise per the exact selector bindings: Dy8[index] (loaded first,
 * selector 0xc478) is added to x, and Dx8[index] (selector 0xc47a) is
 * added to y, giving IsClearTile(type, y + Dx8[index], x + Dy8[index]).
 */
extern int far IsClearTile(int plane, int x, int y);
extern signed char far Dy8[];
extern signed char far Dx8[];

int far IsClear3x3(int x, int y, int type)
{
    int index;

    if (IsClearTile(type, y, x) == 1) {
        for (index = 0; index < 8; ++index) {
            if (!IsClearTile(type, y + Dx8[index], x + Dy8[index]))
                return 0;
        }
        return 1;
    }
    return 0;
}
