/*
 * CreateNewHole(x, y): places a hole directly at MapA[x][y] (x is the row,
 * y the column, matching MakeNewHoleB/R's internal r/x roles) instead of
 * searching a ring like MakeNewHoleB/R do; out-of-range coordinates
 * (x < 1, x > 126, y < 1, y > 62) are rejected with no effect. When
 * TERRAINset != 0 the cell is simply marked 0x59; otherwise it is marked
 * 0x50 and the eight Dx8/Dy8 neighbours are stamped with the private
 * per-direction HoleValues[] table wherever in bounds and not already
 * >= 0x50 (identical shape to MakeNewHoleB/R's fallback neighbour stamp).
 * The hole is then committed to one colony by row: x < 0x40 is the black
 * colony (HoleMapB[y] = x; DigTileB(y, 1); LastNewHoleB[2] = {x, y};
 * LastNewExitB[2] = {y, 0}); x >= 0x40 is the red colony, which inlines the
 * DigTileR-shaped dig of row 1 at MapR[y][1] instead of calling it
 * (matches the accepted-shape MakeNewHoleR/DigMyTile tails): IsItDirt-gated
 * overwrite with SRand8(), TileTotXR += y and TileTotYR += 1 (row is
 * always 1), TilesDugR pre-increment, conditional TileMassXR/TileMassYR
 * division, SmoothEdgesR(y,0)/(y+1,1)/(y,2)/(y-1,1), FixExitMapR(y, 1),
 * then LastNewHoleR[2] = {x, y}; LastNewExitR[2] = {y, 0}. Declarations for
 * MapA/HoleMapB/HoleMapR/Dx8/Dy8/HoleValues/DigTileB/IsItDirt/SRand8/
 * SmoothEdgesR/FixExitMapR/TileTotX-Y/TileMassX-Y/TilesDugR are reused
 * verbatim from the RandWorld/DigOutBNest-DigOutRNest translation unit
 * (src/recovered/wf_tu_simtwo_5AB0_RandWorld_5-2079c82816.c) and the
 * accepted-shape MakeNewHoleB/MakeNewHoleR/DigTileB drafts
 * (build/grind/agentW/MakeNewHoleB.c, MakeNewHoleR.c, DigTileB.c, all
 * MATCH_BLOCKED on the same unrelated register-allocation dead-store).
 */
extern unsigned char near MapA[128][64];
extern unsigned char near MapR[64][64];
extern unsigned char far HoleMapB[];
extern unsigned char far HoleMapR[];
extern char far Dx8[];
extern char far Dy8[];
extern unsigned char near HoleValues[];
extern int far TERRAINset;
extern int far LastNewHoleB[2];
extern int far LastNewExitB[2];
extern int far LastNewHoleR[2];
extern int far LastNewExitR[2];
extern long far TileTotXR;
extern long far TileTotYR;
extern int far TilesDugR;
extern int far TileMassXR;
extern int far TileMassYR;

extern void far DigTileB(int x, int y);
extern int far IsItDirt(int value);
extern int far SRand8(void);
extern void far SmoothEdgesR(int x, int y);
extern void far FixExitMapR(int x, int y);

void far CreateNewHole(int x, int y)
{
    int newRow;
    int newCol;
    int k;
    int cnt;
    unsigned char near *cell;

    if (x < 1)
        return;
    if (x >= 0x7f)
        return;
    if (y < 1)
        return;
    if (y >= 0x3f)
        return;

    if (TERRAINset != 0) {
        MapA[x][y] = 0x59;
    } else {
        MapA[x][y] = 0x50;
        for (k = 0; k < 8; k++) {
            newRow = Dx8[k] + x;
            newCol = Dy8[k] + y;
            if (newRow < 0 || newRow > 0x7f || newCol < 0 || newCol > 0x3f)
                continue;
            if (MapA[newRow][newCol] >= 0x50)
                continue;
            MapA[newRow][newCol] = HoleValues[k];
        }
    }

    if (x < 0x40) {
        HoleMapB[y] = (unsigned char)x;
        DigTileB(y, 1);
        LastNewHoleB[0] = x;
        LastNewHoleB[1] = y;
        LastNewExitB[0] = y;
        LastNewExitB[1] = 0;
        return;
    }

    HoleMapR[y] = (unsigned char)x;

    cell = &MapR[y][1];
    if (IsItDirt(*cell)) {
        *cell = (unsigned char)SRand8();
        TileTotXR += y;
        TileTotYR += 1;
        cnt = ++TilesDugR;
        if (cnt > 0) {
            TileMassXR = TileTotXR / cnt;
            TileMassYR = TileTotYR / cnt;
        }
    }

    SmoothEdgesR(y, 0);
    SmoothEdgesR(y + 1, 1);
    SmoothEdgesR(y, 2);
    SmoothEdgesR(y - 1, 1);
    FixExitMapR(y, 1);

    LastNewHoleR[0] = x;
    LastNewHoleR[1] = y;
    LastNewExitR[0] = y;
    LastNewExitR[1] = 0;
}
