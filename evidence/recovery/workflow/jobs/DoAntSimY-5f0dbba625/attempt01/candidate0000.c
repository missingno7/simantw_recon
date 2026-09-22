/*
 * DoAntSimY: per-tick simulation for the player's (yellow) ant.  Skips
 * entirely while MeMode is set (game paused/other mode).  Otherwise it
 * re-stamps the ant's yard life cell, applies the periodic health decay
 * gated by the low bits of Cycle, and (for a plane-1+ ant) penalizes
 * health further when standing on a "deep" map tile (GetMap() >= 0x4e).
 * A yellow queen (MeType 0x60) on a nest plane beyond the entrance, on a
 * quiet 16-tick boundary (!(Cycle & 0xf)), may lay an egg one tile behind
 * her (Dx8/Dy8 direction-delta tables indexed by the reversed heading)
 * when that tile is inside the nest and a 0..127 SRand128() roll does not
 * exceed her health; the matching color's PlaceEgg*/DecEat* pair runs and
 * her health drops by 5.  Finally, once health has reached zero, a
 * hundred-tick countdown (MeHealthCntDwn) triggers YellowDeath with code
 * 7 (caught in the open map, plane >= 2 and a "deep" tile) or 8
 * (otherwise).
 */
extern int near MePlane;
extern int near MeLocX;
extern int near MeLocY;
extern int near MeType;
extern int near MeDir;
extern int near MeHealth;
extern int near MeColor;
extern int far MeMode;
extern unsigned char far Cycle;
extern int far MeHealthCntDwn;
extern unsigned char far Dy8[];
extern unsigned char far Dx8[];

extern int far GetMap(int plane, int x, int y);
extern int far InNestBounds(int x, int y);
extern void far SetMyLife(int plane, int x, int y, int type, int dir, int code);
extern void far SetMyHealth(int health);
extern long far SRand128(void);
extern void far PlaceEggB(int x, int y, int flag);
extern void far PlaceEggR(int x, int y, int flag);
extern void far DecEatB(void);
extern void far DecEatR(void);
extern void far YellowDeath(int code);

void far DoAntSimY(void)
{
    int newy, newx;
    int mapval;
    int bx;

    if (MeMode != 0)
        return;

    SetMyLife(MePlane, MeLocX, MeLocY, MeType, MeDir, 0xff);

    if (!(Cycle & 0x3f))
        SetMyHealth(MeHealth - 1);

    if (MePlane >= 2) {
        mapval = GetMap(MePlane, MeLocX, MeLocY);
        if (mapval >= 0x4e)
            SetMyHealth(MeHealth - 1);
    }

    if (MeType == 0x60 && MePlane > 1 && !(Cycle & 0xf)) {
        bx = MeDir ^ 4;
        newy = MeLocY + 2 * (signed char)Dy8[bx];
        newx = MeLocX + 2 * (signed char)Dx8[bx];
        if (InNestBounds(newx, newy)) {
            if (SRand128() <= MeHealth) {
                if (MeColor == 0) {
                    PlaceEggB(newx, newy, 1);
                    DecEatB();
                } else {
                    PlaceEggR(newx, newy, 1);
                    DecEatR();
                }
                SetMyHealth(MeHealth - 5);
            }
        }
    }

    if (MeHealth <= 0) {
        if (++MeHealthCntDwn >= 100) {
            if (MePlane >= 2 && mapval >= 0x4e)
                YellowDeath(7);
            else
                YellowDeath(8);
        }
    }
}
