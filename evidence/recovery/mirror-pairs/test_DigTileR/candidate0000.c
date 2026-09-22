/* Derived mechanically from the mirrored colony function _DigTileB (tools/mirror_pairs.py):
 * colony-specific MAPSYM identifiers swapped DigOutBNest->DigOutRNest, DigTileB->DigTileR, DigTileThemB->DigTileThemR, ExitMapB->ExitMapR, FixExitMapB->FixExitMapR, MapB->MapR, SmoothEdgesB->SmoothEdgesR, TileMassXB->TileMassXR, TileMassYB->TileMassYR, TileTotXB->TileTotXR, TileTotYB->TileTotYR, TilesDugB->TilesDugR; constants and structure unchanged.
 * Verified only by the strict matcher; where the pair is not a pure mirror the
 * diagnostic names the asymmetry. */
/*
 * DigTileB(x, y): digs the black colony's tile at (x, y). If MapB[x][y] is
 * dirt (IsItDirt) it is overwritten with SRand8(); TileTotXB += x and
 * TileTotYB += y accumulate, TilesDugB is pre-incremented, and while the
 * resulting count is positive TileMassXB/TileMassYB are recomputed as
 * TileTotXB/TileTotYB divided by that count (matches the accepted-shape
 * DigTileThemB dig-total bookkeeping, MATCH_BLOCKED on an unrelated
 * register-allocation dead-store). When the dig succeeded and the column is
 * deep enough (y > 0x35) there is a 1-in-64 chance (SRand1(0x40) == 0) of
 * also breaking into the red colony's tunnel: MapB[x][y] is marked 0x14,
 * MapR[x][y] is dug the same IsItDirt-gated way with its own TileTot/
 * TilesDugR/TileMass bookkeeping, the four SmoothEdgesR neighbours and
 * FixExitMapR(x, y) are applied, and MapB[x][y] is marked 0x14 again before
 * falling into the always-run tail: the four SmoothEdgesB neighbours and
 * FixExitMapB(x, y). When the initial cell was not dirt, every step above
 * is skipped and only the SmoothEdgesB/FixExitMapB tail runs. Declarations
 * for MapB/MapR/IsItDirt/SRand8/SRand1/SmoothEdgesB/SmoothEdgesR/
 * FixExitMapB/FixExitMapR/TileTotX-Y/TileMassX-Y/TilesDug for both colonies
 * are reused verbatim from the RandWorld/DigOutBNest-DigOutRNest
 * translation unit (src/recovered/wf_tu_simtwo_5AB0_RandWorld_5-2079c82816.c)
 * and the accepted-shape DigTileThemB/DigTileThemR drafts
 * (build/grind/agentW/DigTileThemB.c, DigTileThemR.c, both MATCH_BLOCKED).
 */
extern unsigned char near MapR[64][64];
extern unsigned char near MapR[64][64];
extern long far TileTotXR;
extern long far TileTotYR;
extern int far TilesDugR;
extern int far TileMassXR;
extern int far TileMassYR;
extern long far TileTotXR;
extern long far TileTotYR;
extern int far TilesDugR;
extern int far TileMassXR;
extern int far TileMassYR;

extern int far IsItDirt(int value);
extern int far SRand8(void);
extern int far SRand1(int range);
extern void far SmoothEdgesR(int x, int y);
extern void far SmoothEdgesR(int x, int y);
extern void far FixExitMapR(int x, int y);
extern void far FixExitMapR(int x, int y);

void far DigTileR(int x, int y)
{
    int cnt;

    if (IsItDirt(MapR[x][y])) {
        MapR[x][y] = (unsigned char)SRand8();
        TileTotXR += x;
        TileTotYR += y;
        cnt = ++TilesDugR;
        if (cnt > 0) {
            TileMassXR = TileTotXR / cnt;
            TileMassYR = TileTotYR / cnt;
        }

        if (y > 0x35 && SRand1(0x40) == 0) {
            MapR[x][y] = 0x14;
            if (IsItDirt(MapR[x][y])) {
                MapR[x][y] = (unsigned char)SRand8();
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

            MapR[x][y] = 0x14;
        }
    }

    SmoothEdgesR(x, y - 1);
    SmoothEdgesR(x + 1, y);
    SmoothEdgesR(x, y + 1);
    SmoothEdgesR(x - 1, y);
    FixExitMapR(x, y);
}
