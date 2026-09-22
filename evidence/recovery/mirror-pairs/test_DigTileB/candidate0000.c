/* Derived mechanically from the mirrored colony function _DigTileR (tools/mirror_pairs.py):
 * colony-specific MAPSYM identifiers swapped DigTileR->DigTileB, ExitMapR->ExitMapB, FixExitMapR->FixExitMapB, MapR->MapB, SmoothEdgesR->SmoothEdgesB, TileMassXR->TileMassXB, TileMassYR->TileMassYB, TileTotXR->TileTotXB, TileTotYR->TileTotYB, TilesDugR->TilesDugB; constants and structure unchanged.
 * Verified only by the strict matcher; where the pair is not a pure mirror the
 * diagnostic names the asymmetry. */
/*
 * DigTileR: dig the R-colony tile at (x, y). Only proceeds when the
 * current tile is dirt (IsItDirt, twin of _IsItDirt used by
 * src/recovered/wf_IsItDirt-30ab0b6cc4.c's caller family); on success
 * the tile becomes a random byte (SRand8) and the running dig
 * statistics (exact MAPSYM names TileTotXR/TileTotYR/TilesDugR/
 * TileMassXR/TileMassYR, far segment9 data) are updated: the X/Y totals
 * accumulate, the dug-tile count increments, and (while the count is
 * positive) the mass centre (TileMassX/YR) is recomputed as the running
 * average. The four orthogonal neighbours are then smoothed
 * (SmoothEdgesR) and the R exit map is refreshed (FixExitMapR, this
 * session's own target).
 */
extern unsigned char near MapB[64][64];
extern long far TileTotXB;
extern long far TileTotYB;
extern int far TilesDugB;
extern int far TileMassXB;
extern int far TileMassYB;

extern int far IsItDirt(int value);
extern int far SRand8(void);
extern void far SmoothEdgesB(int x, int y);
extern void far FixExitMapB(int x, int y);

void far DigTileB(int x, int y)
{
    int count;

    if (!IsItDirt(MapB[x][y]))
        return;
    MapB[x][y] = (unsigned char)SRand8();
    TileTotXB += x;
    TileTotYB += y;
    TilesDugB++;
    count = TilesDugB;
    if (count <= 0)
        return;
    TileMassXB = TileTotXB / count;
    TileMassYB = TileTotYB / count;
    SmoothEdgesB(x, y - 1);
    SmoothEdgesB(x + 1, y);
    SmoothEdgesB(x - 1, y);
    SmoothEdgesB(x, y + 1);
    FixExitMapB(x, y);
}
