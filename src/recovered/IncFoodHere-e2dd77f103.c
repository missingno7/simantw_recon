/* i11_target_assignment_order: store tile first, increment above threshold, otherwise substitute the low-band threshold. */
/* i05_amt_nested: use threshold-first nested branches for the amount decision. */
/*
 * IncFoodHere: experimental tool that adds food at map cell (x, y) on
 * the current MapPlane, gated by the tile value at that cell against a
 * per-plane clearance threshold (0x48 for A planes 0/1, 0x10
 * otherwise).  Holding CONTROL widens the acceptance band (tile within
 * threshold..threshold+3, amount SRand1(8)); otherwise the band is
 * threshold..threshold+2 and the amount is size-based (tile+1 when the
 * tile already meets the threshold, else the tile itself once it is at
 * least 0x18, else the threshold).  On A planes the amount is drawn
 * from FoodA when available; when FoodA is empty a MapPlane==2 check
 * (unreachable here, since MapPlane is already known to be 0 or 1) and
 * an R-food fallback both exist as dead code, so the practical
 * behaviour draws from FoodR once FoodA runs out, without ever
 * blocking placement.  Any other plane skips the supply check
 * entirely.  The tile is then set and the matching supply (FoodA for
 * 0/1, FoodB for 2, FoodR otherwise) incremented back; the function
 * returns 1, or 0 from either early band check.
 */
extern int near MapPlane;
extern int far match_position[];
extern int far FoodA;
extern int far FoodB;
extern int far FoodR;

extern int far pascal GetAsyncKeyState(unsigned int key);
extern int far GetMap(int plane, int x, int y);
extern int far SRand1(int range);
extern void far SetMap(int plane, int x, int y, int value);

int far IncFoodHere(int x, int y)
{
    int tile;
    volatile int amt;
    int threshold;

    if (MapPlane == 1 || MapPlane == 0)
        threshold = 0x48;
    else
        threshold = 0x10;

    tile = GetMap(MapPlane, x, y);

    if (GetAsyncKeyState(0x11) & 0x8000) {
        if (tile < threshold)
            return 0;
        if (threshold + 3 < tile)
            return 0;
        amt = SRand1(8);

        if (MapPlane == 1 || MapPlane == 0) {
            if (FoodA > 0) {
                FoodA--;
            } else if (MapPlane == 2) {
                if (FoodB > 0)
                    FoodB--;
            } else {
                if (FoodR > 0)
                    FoodR--;
            }
        }
    } else {
        if (threshold + 2 < tile)
            return 0;
        if (tile < threshold) {
            amt = tile;
            if (tile < 0x18)
                amt = threshold;
        } else {
            amt = tile;
            ++amt;
        }

        if (MapPlane == 1 || MapPlane == 0)
            FoodA++;
        else if (MapPlane == 2)
            FoodB++;
        else
            FoodR++;
    }

    SetMap(MapPlane, x, y, amt);
    return 1;
}
