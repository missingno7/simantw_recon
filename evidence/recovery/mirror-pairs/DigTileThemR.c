/* Derived mechanically from the mirrored colony function _DigTileThemB (tools/mirror_pairs.py):
 * colony-specific MAPSYM identifiers swapped DigOutBNest->DigOutRNest, DigTileThemB->DigTileThemR, ExitMapB->ExitMapR, FillDirtB->FillDirtR, FixExitMapB->FixExitMapR, MakeNewHoleB->MakeNewHoleR, MapB->MapR, SmoothEdgesB->SmoothEdgesR, TileMassXB->TileMassXR, TileMassYB->TileMassYR, TileTotXB->TileTotXR, TileTotYB->TileTotYR, TilesDugB->TilesDugR; constants and structure unchanged.
 * Verified only by the strict matcher; where the pair is not a pure mirror the
 * diagnostic names the asymmetry. */
/*
 * DigTileThemB(x, y): AI-nest digging helper for the black colony. Returns 0
 * without digging when the target cell is out of the diggable interior band
 * (x == 0 or x > 62), or when an in-bounds vertical neighbour in the same
 * column (y - 1 / y + 1, checked only when in range) is not a dirt tile per
 * IsItDirt. Otherwise it carves the cell: row y == 0 seeds the nest-entrance
 * marker 0x18 into MapB and opens a new surface hole via MakeNewHoleB(x);
 * any other row gets a random dirt-tile byte from SRand8(). The dig totals
 * TileTotXB/TileTotYB accumulate x/y, TilesDugB is pre-incremented, and while
 * the resulting count is positive the running averages TileMassXB/TileMassYB
 * are recomputed as TileTotXB/TileTotYB divided by that count (32-bit
 * division via the runtime long divide). The four orthogonal neighbours are
 * re-smoothed with SmoothEdgesB and the exit-flow map is refreshed with
 * FixExitMapB before returning 1 for a successful dig. Twin of DigTileThemR;
 * MapB/TilesDugB/TileTotXB/TileTotYB/TileMassXB/TileMassYB/MakeNewHoleB and
 * the (x, y) parameter order are reused verbatim from the admitted
 * FillDirtB and the RandWorld/DigOutBNest translation unit
 * (src/recovered/wf_FillDirtB-b73109489f.c,
 * src/recovered/wf_tu_simtwo_5AB0_RandWorld_5-2079c82816.c), and the dirt
 * band test from the admitted IsItDirt (src/recovered/wf_IsItDirt-30ab0b6cc4.c).
 */
extern unsigned char near MapR[64][64];
extern int far TilesDugR;
extern long far TileTotXR;
extern long far TileTotYR;
extern int far TileMassXR;
extern int far TileMassYR;

extern int far IsItDirt(int value);
extern void far MakeNewHoleR(int x);
extern int far SRand8(void);
extern void far SmoothEdgesR(int x, int y);
extern void far FixExitMapR(int x, int y);

int far DigTileThemR(int x, int y)
{
    int cnt;

    if (y < 0x3f) {
        if (!IsItDirt(MapR[x][y + 1]))
            goto bad;
    }
    if (y > 2) {
        if (!IsItDirt(MapR[x][y - 1]))
            goto bad;
    }
    if (x == 0)
        goto bad;
    if (x > 0x3e)
        goto bad;

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

bad:
    return 0;
}
