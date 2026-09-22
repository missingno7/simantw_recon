/*
 * DigTileThemR(x, y): red-colony twin of DigTileThemB. Returns 0 without
 * digging when the target cell is out of the diggable interior band
 * (x == 0 or x > 62), or when an in-bounds vertical neighbour in the same
 * column (y - 1 / y + 1, checked only when in range) is not a dirt tile per
 * IsItDirt. Otherwise it carves the cell: row y == 0 seeds the nest-entrance
 * marker 0x18 into MapR and opens a new surface hole via MakeNewHoleR(x);
 * any other row gets a random dirt-tile byte from SRand8(). The dig totals
 * TileTotXR/TileTotYR accumulate x/y, TilesDugR is pre-incremented, and while
 * the resulting count is positive the running averages TileMassXR/TileMassYR
 * are recomputed as TileTotXR/TileTotYR divided by that count (32-bit
 * division via the runtime long divide). The four orthogonal neighbours are
 * re-smoothed with SmoothEdgesR and the exit-flow map is refreshed with
 * FixExitMapR before returning 1 for a successful dig. Twin of the accepted
 * DigTileThemB body (build/grind/agentW/DigTileThemB.c, MATCH_BLOCKED on an
 * unrelated register-allocation dead-store); MapR/TilesDugR/TileTotXR/
 * TileTotYR/TileMassXR/TileMassYR/MakeNewHoleR/SmoothEdgesR/FixExitMapR and
 * the (x, y) parameter order are reused verbatim from the admitted
 * FillDirtR-style declarations and the RandWorld/DigOutRNest translation
 * unit (src/recovered/wf_FillDirtR-d16ac84868.c,
 * src/recovered/wf_tu_simtwo_5AB0_RandWorld_5-2079c82816.c), and the dirt
 * band test from the admitted IsItDirt (src/recovered/wf_IsItDirt-30ab0b6cc4.c).
 */
extern int far IsItDirt(int value);
extern void far MakeNewHoleR(int x);
extern int far SRand8(void);
extern void far SmoothEdgesR(int x, int y);
extern void far FixExitMapR(int x, int y);

extern unsigned char near MapR[64][64];
extern int far TilesDugR;
extern long far TileTotXR;
extern long far TileTotYR;
extern int far TileMassXR;
extern int far TileMassYR;

int far DigTileThemR(int x, int y)
{
    int cnt;

    if (y < 0x3f) {
        if (!IsItDirt(MapR[x][y + 1]))
            return 0;
    }
    if (y > 2) {
        if (!IsItDirt(MapR[x][y - 1]))
            return 0;
    }
    if (x == 0)
        return 0;
    if (x > 0x3e)
        return 0;

    if (y == 0) {
        MapR[x][0] = 0x18;
        MakeNewHoleR(x);
    } else {
        MapR[x][y] = (unsigned char)SRand8();
    }

    TileTotXR += x;
    TileTotYR += y;
    cnt = ++TilesDugR;
    if (cnt > 0) {
        TileMassXR = TileTotXR / cnt;
        TileMassYR = TileTotYR / cnt;
    }

    SmoothEdgesR(x, y - 1);
    SmoothEdgesR(x + 1, y);
    SmoothEdgesR(x, y + 1);
    SmoothEdgesR(x - 1, y);
    FixExitMapR(x, y);

    return 1;
}
