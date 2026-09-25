/* Semantic hypothesis: preserved draft; verify bindings and loop invariants against context. */
/* SpiderScan: while SMode!=5, scan for an ant near the spider by
 * casting random points on a circle around the spider's tile position.
 * The base angle is derived from the spider's facing (SpidDir-2)&7,
 * scaled to angle units (<<5); two passes scan angle base-0x20 ..
 * base+0x20 (64 angle units), each attempt picking a random radius
 * (SRand1(0xc)+1) and converting (radius,angle) to a tile offset via
 * fixed-point fracCOS/fracSIN (radius*fracCOS(angle)/32767), added to
 * the spider's own tile.  An in-range (0<=x<0x80, 0<=y<0x40) tile with
 * a nonzero LifeA byte resolves through FindAntIndex(1,x,y,terrain);
 * a non-negative result fires the laser at the tile's pixel center and,
 * with 50% odds (SRand4), removes the ant from the map (LifeA cleared,
 * its A-list attribute cleared, DeadAntHere notified with the terrain's
 * high team bit).  Returns the found index, or -1 if nothing is found
 * after both passes.
 */

extern int far SMode;
extern int near SpidDir;
extern int near SpidX;
extern int near SpidY;
extern unsigned char near LifeA[128][64];
extern unsigned char far AlistT[];

extern int SRand1(int range);
extern int far SRand4(void);
extern int far fracCOS(int angle);
extern int far fracSIN(int angle);
extern int far FindAntIndex(int list, int life, int column, int attribute);
extern void far DoLaserFire(int x, int y, int targetX, int targetY);
extern void far DeadAntHere(int x, int y, int flags);

int far SpiderScan(void)
{
    int angleBase;
    int angle;
    int angleTop;
    int spidTileX, spidTileY;
    int radius;
    int tileX, tileY;
    int terrain;
    int found;
    int outer;

    if (SMode == 5)
        return -1;

    angleBase = ((SpidDir - 2) & 7) << 5;
    spidTileX = SpidX >> 4;
    spidTileY = SpidY >> 4;
    found = -1;
    terrain = 0;
    outer = 0;

    angleTop = angleBase + 0x20;
    angle = angleBase - 0x20;
    for (outer = 0; outer < 2; outer++) {
        do {
            radius = SRand1(0xc) + 1;
            tileX = spidTileX + (int)((long)radius * fracCOS(angle) / 32767L);
            tileY = spidTileY + (int)((long)radius * fracSIN(angle) / 32767L);
            if (tileX >= 0 && tileX <= 0x7f && tileY >= 0 && tileY <= 0x3f) {
                terrain = LifeA[tileX][tileY];
                if (terrain != 0) {
                    found = FindAntIndex(1, tileX, tileY, terrain);
                    if (found >= 0)
                        goto found_one;
                }
            }
            angle++;
        } while (angle < angleTop);
        angle = angleBase - 0x20;
    }
    return found;

found_one:
    DoLaserFire(SpidX, SpidY, tileX * 16 + 7, tileY * 16 + 7);
    if (SRand4() != 0) {
        LifeA[tileX][tileY] = 0;
        AlistT[found] = 0;
        DeadAntHere(tileX, tileY, terrain & 0x80);
    }
    return found;
}
