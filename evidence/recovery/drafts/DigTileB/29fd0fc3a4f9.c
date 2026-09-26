/*
 * DigTileB(x, y): digs the black colony's tile at (x, y). If black[cell] is
 * dirt (IsItDirt) it is overwritten with SRand8(); TileTotXB += x and
 * TileTotYB += y accumulate, TilesDugB is pre-incremented, and while the
 * resulting count is positive TileMassXB/TileMassYB are recomputed as
 * TileTotXB/TileTotYB divided by that count (matches the accepted-shape
 * DigTileThemB dig-total bookkeeping, MATCH_BLOCKED on an unrelated
 * register-allocation dead-store). When the dig succeeded and the column is
 * deep enough (y > 0x35) there is a 1-in-64 chance (SRand1(0x40) == 0) of
 * also breaking into the red colony's tunnel: black[cell] is marked 0x14,
 * red[cell] is dug the same IsItDirt-gated way with its own TileTot/
 * TilesDugR/TileMass bookkeeping, the four SmoothEdgesR neighbours and
 * FixExitMapR(x, y) are applied, and black[cell] is marked 0x14 again before
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
extern unsigned char near MapB[4096];
extern unsigned char near MapR[4096];
extern long far TileTotXB;
extern long far TileTotYB;
extern int far TilesDugB;
extern int far TileMassXB;
extern int far TileMassYB;
extern long far TileTotXR;
extern long far TileTotYR;
extern int far TilesDugR;
extern int far TileMassXR;
extern int far TileMassYR;

extern int far IsItDirt(int value);
extern int far SRand8(void);
extern int far SRand1(int range);
extern void far SmoothEdgesB(int x, int y);
extern void far SmoothEdgesR(int x, int y);
extern void far FixExitMapB(int x, int y);
extern void far FixExitMapR(int x, int y);

void far DigTileB(int x, int y)
{
    int cnt;
    int cell;
    unsigned char near *black;
    unsigned char near *red;
    cell = x * 64 + y;
    black = MapB;
    red = MapR;

    if (IsItDirt(black[cell])) {
        black[cell] = (unsigned char)SRand8();
        TileTotXB += x;
        TileTotYB += y;
        cnt = ++TilesDugB;
        if (cnt > 0) {
            TileMassXB = TileTotXB / cnt;
            TileMassYB = TileTotYB / cnt;
        }

        if (y > 0x35 && SRand1(0x40) == 0) {
            black[cell] = 0x14;
            if (IsItDirt(red[cell])) {
                red[cell] = (unsigned char)SRand8();
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

            black[cell] = 0x14;
        }
    }

    SmoothEdgesB(x, y - 1);
    SmoothEdgesB(x + 1, y);
    SmoothEdgesB(x, y + 1);
    SmoothEdgesB(x - 1, y);
    FixExitMapB(x, y);
}
