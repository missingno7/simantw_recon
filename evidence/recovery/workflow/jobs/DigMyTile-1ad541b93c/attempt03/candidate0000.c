/*
 * DigMyTile(type, x, y): digs the tile at (x, y) for the ant's own colony
 * (type == 2 selects the black colony's MapB/MakeNewHoleB/DigTileB path,
 * anything else selects the red colony's MapR/MakeNewHoleR path, which
 * inlines DigTileR-shaped digging rather than calling it, mirroring the
 * accepted-shape MakeNewHoleR draft). IsItDigable(type, x, y) gates the
 * whole function: a false result returns immediately without touching any
 * map. For row y <= 1 both colonies first seed the surface nest-entrance
 * marker 0x18 at (x, 0) and open a new hole via MakeNewHoleB(x)/
 * MakeNewHoleR(x); when y != 1 that alone is the whole operation and the
 * function returns without digging further. Otherwise (y == 1, or y > 1
 * directly): the black path calls DigTileB(x, y) and returns; the red path
 * inlines the dig itself -- if MapR[x][y] is dirt (IsItDirt) it is
 * overwritten with SRand8(), TileTotXR += x and TileTotYR += y accumulate,
 * TilesDugR is pre-incremented, and while the resulting count is positive
 * TileMassXR/TileMassYR are recomputed as TileTotXR/TileTotYR divided by
 * that count (matches the accepted-shape DigTileThemR/MakeNewHoleR dig-total
 * bookkeeping, both MATCH_BLOCKED on an unrelated register-allocation
 * dead-store); the four orthogonal neighbours are re-smoothed with
 * SmoothEdgesR and the exit-flow map is refreshed with FixExitMapR
 * regardless of whether the cell was dirt. Declarations for MapB/MapR/
 * DigTileB/MakeNewHoleB/MakeNewHoleR/IsItDirt/SRand8/SmoothEdgesR/
 * FixExitMapR/TileTotX-Y/TileMassX-Y/TilesDugR are reused verbatim from the
 * RandWorld/DigOutBNest-DigOutRNest translation unit
 * (src/recovered/wf_tu_simtwo_5AB0_RandWorld_5-2079c82816.c) and the
 * accepted-shape MakeNewHoleB/MakeNewHoleR drafts
 * (build/grind/agentW/MakeNewHoleB.c, MakeNewHoleR.c, both MATCH_BLOCKED).
 * IsItDigable is not yet recovered in this unit (simone:16AE); its
 * signature is inferred from the exact 3-argument push order at the call
 * site (type, x, y).
 */
extern unsigned char near MapB[64][64];
extern unsigned char near MapR[64][64];
extern long far TileTotXR;
extern long far TileTotYR;
extern int far TilesDugR;
extern int far TileMassXR;
extern int far TileMassYR;

extern int far IsItDigable(int type, int x, int y);
extern void far MakeNewHoleB(int x);
extern void far MakeNewHoleR(int x);
extern void far DigTileB(int x, int y);
extern int far IsItDirt(int value);
extern int far SRand8(void);
extern void far SmoothEdgesR(int x, int y);
extern void far FixExitMapR(int x, int y);

void far DigMyTile(int type, int x, int y)
{
    int cnt;
    unsigned char near *cell;

    if (!IsItDigable(type, x, y))
        return;

    if (type == 2) {
        if (y <= 1) {
            MapB[x][0] = 0x18;
            MakeNewHoleB(x);
            if (y != 1)
                return;
        }
        DigTileB(x, y);
        return;
    }

    if (y <= 1) {
        cell = &MapR[x][0];
        *cell = 0x18;
        MakeNewHoleR(x);
        if (y != 1)
            return;

        cell = &MapR[x][0] + y;
        if (IsItDirt(*cell)) {
            *cell = (unsigned char)SRand8();
            TileTotXR += x;
            TileTotYR += y;
            cnt = ++TilesDugR;
            if (cnt > 0) {
                TileMassXR = TileTotXR / cnt;
                TileMassYR = TileTotYR / cnt;
            }
        }

        SmoothEdgesR(x, y - 1);
        SmoothEdgesR(x + 1, y);
        SmoothEdgesR(x, y + 1);
        SmoothEdgesR(x - 1, y);
        FixExitMapR(x, y);
        return;
    }

    cell = &MapR[x][y];
    if (IsItDirt(*cell)) {
        *cell = (unsigned char)SRand8();
        TileTotXR += x;
        TileTotYR += y;
        cnt = ++TilesDugR;
        if (cnt > 0) {
            TileMassXR = TileTotXR / cnt;
            TileMassYR = TileTotYR / cnt;
        }
    }

    SmoothEdgesR(x, y - 1);
    SmoothEdgesR(x + 1, y);
    SmoothEdgesR(x, y + 1);
    SmoothEdgesR(x - 1, y);
    FixExitMapR(x, y);
}
