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
extern unsigned char near MapR[64][64];
extern long far TileTotXR;
extern long far TileTotYR;
extern int far TilesDugR;
extern int far TileMassXR;
extern int far TileMassYR;

extern int far IsItDirt(int value);
extern int far SRand8(void);
extern void far SmoothEdgesR(int x, int y);
extern void far FixExitMapR(int x, int y);

void far DigTileR(int x, int y)
{
    int count;

    if (!IsItDirt(MapR[x][y]))
        return;
    MapR[x][y] = (unsigned char)SRand8();
    TileTotXR += x;
    TileTotYR += y;
    TilesDugR++;
    count = TilesDugR;
    if (count <= 0)
        return;
    TileMassXR = (int)(TileTotXR / (long)count);
    TileMassYR = (int)(TileTotYR / (long)count);
    SmoothEdgesR(x, y - 1);
    SmoothEdgesR(x + 1, y);
    SmoothEdgesR(x - 1, y);
    SmoothEdgesR(x, y + 1);
    FixExitMapR(x, y);
}
