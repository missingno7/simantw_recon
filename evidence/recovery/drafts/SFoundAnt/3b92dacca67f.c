/* SFoundAnt: find a nearby ant/target for the spider (SpidX/SpidY tile
 * coordinates).  When MeSMode==7 (player is controlling the spider),
 * scan the live A-list (ListIndexA-1 down to 0) for an ant whose
 * attribute (AlistT) is set and whose (life,column) position is within
 * 0x320 of the spider; return its A-list index.  Otherwise, when
 * MePlane==1 and MeMode==0, treat the player's own location (MeLocX/
 * MeLocY) as a target: if it is within 0x320, return -1 (the player
 * sentinel).  Otherwise probe up to 20 times: step one tile in the
 * spider's current facing (SpidDir, via the shared Dx8/Dy8 direction
 * tables), require the new tile to be valid (IsValidA) and close to the
 * spider (GetDis <= 0x190); read the terrain life byte there
 * (LifeA[x][y]) -- an occupied yellow-ant tile returns -1, an occupied
 * ordinary tile resolves through FindAntIndex and returns its result
 * when >= 0, otherwise the probe is retried (same direction, same
 * origin) up to 20 times before failing.  Failure returns -2.
 */

extern int near SpidX;
extern int near SpidY;
extern int near SpidDir;

extern int far MeSMode;
extern int far MePlane;
extern int far MeMode;
extern int far MeLocX;
extern int far MeLocY;

extern int far ListIndexA;
extern unsigned char far AlistT[];
extern unsigned char far Dx8[];
extern unsigned char far Dy8[];
extern unsigned char far LifeA[128][64];

extern unsigned long far GetDis(int x1, int y1, int x2, int y2);
extern int far IsValidA(int x, int y);
extern int far IsYellowAnt(int ant);
extern int far FindAntIndex(int list, int life, int column, int attribute);

int far SFoundAnt(void)
{
    int spidTileX;
    int spidTileY;
    int origTileY;
    int tries;
    int tileX, tileY;
    int terrain;
    int result;
    int si;

    spidTileY = SpidY >> 4;
    spidTileX = SpidX >> 4;

    if (MeSMode == 7) {
        si = ListIndexA - 1;
        while (si >= 0) {
            if (AlistT[si] != 0) {
                if (GetDis(spidTileX, spidTileY, Dx8[si + 0x23a4], Dx8[si + 0x278e]) <= 0x320)
                    return si;
            }
            si--;
        }
    }

    if (MeMode != 0)
        return 0xfffe;
    if (MePlane != 1)
        return 0xfffe;
    if (GetDis(spidTileX, spidTileY, MeLocX, MeLocY) <= 0x320)
        return 0xffff;

    origTileY = spidTileY;
    tileX = spidTileX;
    tileY = spidTileY;
    for (tries = 0; tries < 0x14; tries++) {
        tileY += (signed char)Dy8[SpidDir];
        tileX += (signed char)Dx8[SpidDir];
        if (!IsValidA(tileX, tileY))
            return 0xfffe;
        if (GetDis(spidTileX, origTileY, tileX, tileY) > 0x190)
            return 0xfffe;
        terrain = LifeA[tileX][tileY];
        if (terrain != 0) {
            if (IsYellowAnt(terrain))
                return 0xffff;
            result = FindAntIndex(1, tileX, tileY, terrain);
            if (result >= 0)
                return result;
        }
    }
    return 0xfffe;
}
