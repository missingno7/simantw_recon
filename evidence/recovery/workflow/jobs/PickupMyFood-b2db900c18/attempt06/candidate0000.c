/* Hypothesis from the MAPSYM call destination and admitted neighbors:
 * a valid food tile on the surface invokes PickupFoodA(x,y). With no active
 * MeWantFood request, eligible MeType values (0x10 or 0x30) also seed the
 * B-team scent from the last new-hole coordinates; otherwise the accepted
 * food mutation updates the plane map and its food counter. */
extern unsigned char near MapA[128][64];
extern unsigned char near MapB[64][64];
extern unsigned char near MapR[64][64];
extern int near MeType;
extern int near MeScent;
extern int far MeWantFood;
extern int far MeDis;
extern int far MePrevDis;
extern int far LastNewHoleB;
extern int far LastNewHoleR;
extern int far FoodB;
extern int far FoodR;
extern int far MeFoodInType;
extern int far IsValidLocation(int plane, int x, int y);
extern int far IsItFood(int tile);
extern int far PickupFoodA(int x, int y);
extern int far GetDis(int x1, int y1, int x2, int y2);
extern void far JamScentBT(int x, int y, int scent);
extern int far SRand8(void);
extern void far ZapEuMapAt(int plane, int x, int y);
extern void far myBeginSound(unsigned int sound, unsigned int a, unsigned int b);

int far PickupMyFood(int plane, int x, int y)
{
    int tile;
    int scentMode;

    tile = -1;
    if (IsValidLocation(plane, x, y) != 1)
        return 0;

    switch (plane) {
    case 0:
    case 1:
        tile = *((int near *)((char near *)&MapA[0][y] + (x << 6)));
        break;
    case 2:
        tile = *((int near *)((char near *)&MapB[0][y] + (x << 6)));
        break;
    case 3:
        tile = MapR[x][y];
        break;
    default:
        return 0;
    }

    if (tile < 0)
        return 0;
    if (plane <= 1) {
        if (IsItFood(tile) == 0)
            return 0;
    } else if (tile < 0x10 || tile > 0x13) {
        return 0;
    }

    if (MeWantFood != 0)
        scentMode = 1;
    else if (MeType == 0x10 || MeType == 0x30)
        scentMode = 0;
    else
        return 0;

    if (plane <= 1) {
        PickupFoodA(x, y);
        if (scentMode == 0) {
            MeScent = 0xc8;
            MeDis = GetDis(x, y, LastNewHoleR, LastNewHoleB);
            MePrevDis = MeDis + 1;
            JamScentBT(x, y, MeScent);
        }
    } else {
        if (plane <= 1) {
            if (x >= 0 && x <= 0x7f && y >= 0 && y <= 0x3f)
                tile = MapA[x][y];
        } else if (x >= 0 && x <= 0x3f && y >= 0 && y <= 0x3f) {
            if (plane == 2)
                tile = MapB[x][y];
            else
                tile = MapR[x][y];
        }
            if (tile == 0x10)
                tile = SRand8();
            else
                --tile;

            if (plane <= 1) {
                if (x >= 0 && x <= 0x7f && y >= 0 && y <= 0x3f)
                    MapA[x][y] = (unsigned char)tile;
            } else if (x >= 0 && x <= 0x3f && y >= 0 && y <= 0x3f) {
                if (plane == 2)
                    MapB[x][y] = (unsigned char)tile;
                else
                    MapR[x][y] = (unsigned char)tile;
            }
            ZapEuMapAt(plane, x, y);
        if (plane == 2) {
            if (FoodB > 0)
                --FoodB;
        } else if (FoodR > 0) {
            --FoodR;
        }
    }

    if (scentMode != 0)
        MeFoodInType = 0;
    else {
        myBeginSound(0x1d, 0, 0x7e);
        MeType += 8;
    }
    return 1;
}

