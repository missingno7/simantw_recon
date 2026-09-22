/*
 * MakeNewHoleR(x): red-colony twin of MakeNewHoleB, structurally larger
 * because it inlines the DigTileR-shaped dig of row 1 instead of calling a
 * helper. Rolls roll=SRand1(31), then picks a search algorithm by
 * TERRAINset, searching rings r = 0x7e - (roll + j) % 0x20 (mirrored from
 * B's r = (roll + j) % 0x20 + 2, since the red colony's rings run from the
 * opposite edge of MapA). When TERRAINset != 0 it scans MapA[r][x] with the
 * same inline CanBeHouseHole-shaped lookup table as MakeNewHoleB, breaking
 * on the first nonzero hole code and recording LastNewHoleR[2]/
 * LastNewExitR[2] on success. When TERRAINset == 0 it instead scans the
 * same ring sequence with IsClear3x3(1, r, x), and on the first clear ring
 * marks MapA[r][x] = 0x50, records the same two position pairs, and stamps
 * the eight Dx8/Dy8 neighbours of (r, x) into MapA with the private
 * per-direction HoleValues[] table (shared with MakeNewHoleB and the
 * blocked HoleBorder draft). A ring search that exhausts all 0x22 rings
 * without success returns without digging. On success both branches
 * converge on a shared tail that writes HoleMapR[x] = (unsigned char)r,
 * then inlines the row-1 dig at MapR[x][1]: if that cell is dirt
 * (IsItDirt), it is overwritten with SRand8(), TileTotXR += x and
 * TileTotYR += 1 (the row is always 1, so the accumulation uses the
 * literal, not a variable), TilesDugR is pre-incremented, and while the
 * resulting count is positive TileMassXR/TileMassYR are recomputed as
 * TileTotXR/TileTotYR divided by that count (matches the accepted-shape
 * DigTileThemB/DigTileThemR dig-total bookkeeping, MATCH_BLOCKED on an
 * unrelated register-allocation dead-store). Regardless of the dirt check,
 * the four orthogonal neighbours of (x, 1) are re-smoothed with
 * SmoothEdgesR(x,0)/(x+1,1)/(x,2)/(x-1,1) and the exit-flow map is
 * refreshed with FixExitMapR(x, 1). Declarations for MapA/HoleMapR/Dx8/
 * Dy8/HoleValues/SRand1/IsClear3x3/IsItDirt/SRand8/SmoothEdgesR/
 * FixExitMapR/TileTotX-Y/TileMassX-Y/TilesDugR are reused verbatim from the
 * RandWorld/DigOutRNest translation unit
 * (src/recovered/wf_tu_simtwo_5AB0_RandWorld_5-2079c82816.c), the accepted
 * MakeNewHoleB draft's hypotheses (build/grind/agentW/MakeNewHoleB.c,
 * MATCH_BLOCKED) for HoleValues/LastNewHoleR/LastNewExitR (MAPSYM-named at
 * SIMANT_DATA_GROUP 33622/33630, evidence/symbols/symbols.csv), and the
 * admitted CanBeHouseHole (src/recovered/wf_CanBeHouseHole-987878d5ee.c)
 * for the inline hole-code lookup.
 */
extern unsigned char near MapA[128][64];
extern unsigned char near MapR[64][64];
extern unsigned char far HoleMapR[];
extern char far Dx8[];
extern char far Dy8[];
extern unsigned char near HoleValues[];
extern int far TERRAINset;
extern int far LastNewHoleR[2];
extern int far LastNewExitR[2];
extern long far TileTotXR;
extern long far TileTotYR;
extern int far TilesDugR;
extern int far TileMassXR;
extern int far TileMassYR;

extern int far SRand1(int range);
extern int far SRand8(void);
extern int far IsClear3x3(int kind, int row, int col);
extern int far IsItDirt(int value);
extern void far SmoothEdgesR(int x, int y);
extern void far FixExitMapR(int x, int y);

void far MakeNewHoleR(int x)
{
    int roll;
    int r;
    int hole;
    int j;
    int v;
    int k;
    int newRow;
    int newCol;
    int cnt;
    unsigned char near *cell;

    roll = SRand1(0x1f);

    if (TERRAINset != 0) {
        for (j = 0; j < 0x22; j++) {
            r = 0x7e - (roll + j) % 0x20;
            v = MapA[r][x];
            if (v == 0)
                hole = 0x86;
            else if (v == 2)
                hole = 0x8a;
            else if (v == 3)
                hole = 0x8a;
            else if (v >= 0x5e) {
                if (v < 0x62)
                    hole = v + 0x22;
                else if (v == 0x66)
                    hole = 0x85;
                else if (v == 0x68)
                    hole = 0x84;
                else
                    hole = 0;
            } else
                hole = 0;
            if (hole != 0)
                break;
        }
        if (hole != 0) {
            MapA[r][x] = (unsigned char)hole;
            LastNewHoleR[0] = r;
            LastNewHoleR[1] = x;
            LastNewExitR[0] = x;
            LastNewExitR[1] = 0;
        }
        if (j == 0x22)
            return;
        goto tail;
    }

    for (j = 0; j < 0x22; j++) {
        r = 0x7e - (roll + j) % 0x20;
        if (IsClear3x3(1, r, x))
            break;
    }
    if (j != 0x22) {
        MapA[r][x] = 0x50;
        LastNewHoleR[0] = r;
        LastNewHoleR[1] = x;
        LastNewExitR[0] = x;
        LastNewExitR[1] = 0;

        for (k = 0; k < 8; k++) {
            newRow = Dx8[k] + r;
            newCol = Dy8[k] + x;
            if (newRow < 0 || newRow > 0x7f || newCol < 0 || newCol > 0x3f)
                continue;
            if (MapA[newRow][newCol] >= 0x50)
                continue;
            MapA[newRow][newCol] = HoleValues[k];
        }
    }
    if (j == 0x22)
        return;

tail:
    HoleMapR[x] = (unsigned char)r;

    cell = &MapR[x][1];
    if (IsItDirt(*cell)) {
        *cell = (unsigned char)SRand8();
        TileTotXR += x;
        TileTotYR += 1;
        cnt = ++TilesDugR;
        if (cnt > 0) {
            TileMassXR = TileTotXR / cnt;
            TileMassYR = TileTotYR / cnt;
        }
    }

    SmoothEdgesR(x, 0);
    SmoothEdgesR(x + 1, 1);
    SmoothEdgesR(x, 2);
    SmoothEdgesR(x - 1, 1);
    FixExitMapR(x, 1);
}
