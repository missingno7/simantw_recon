/*
 * PickupMyRock hypothesis: only the player's non-carrying MeType values
 * 0x10 and 0x30 may pick up a rock. A plane-1 cell with tile 0x51..0x53
 * restores a hole pair when HoleMapB/R points back to x, then restores the
 * surface terrain according to TERRAINset. Underground tiles 0x30 and 0x31
 * use the target's separate random replacement and paired-hole paths. A
 * successful pickup changes MeType to 0x28 or 0x48 and plays sound 0x1e.
 * Map dimensions and the IsThisPebble tile bands are grounded in the
 * admitted IsLiftable/IsThisPebble sources; far HoleMap/TERRAINset names and
 * SRand/Zap/sound calls follow the packet bindings.
 */
extern int near MeType;
extern unsigned char near MapA[128][64];
extern unsigned char near MapB[64][64];
extern unsigned char near MapR[64][64];
extern unsigned char far HoleMapB[];
extern unsigned char far HoleMapR[];
extern unsigned int far TERRAINset;
extern int far SRand1(int range);
extern int far SRand8(void);
extern int far SRand16(void);
extern void far ZapEuMapAt(int plane, int x, int y);
extern void far myBeginSound(unsigned int a, unsigned int b, unsigned int c);

int far PickupMyRock(int plane, int x, int y)
{
    int result;
    int tile;
    int ok;
    register int value;

    if (MeType != 0x10 && MeType != 0x30)
        return 0;

    result = 0;
    tile = -1;
    if (plane <= 1)
        ok = (x >= 0 && x <= 0x7f && y >= 0 && y <= 0x3f);
    else
        ok = (x >= 0 && x <= 0x3f && y >= 0 && y <= 0x3f);
    if (ok == 1) {
        switch (plane) {
        case 0:
        case 1:
            tile = MapA[x][y];
            break;
        case 2:
            tile = MapB[x][y];
            break;
        case 3:
            tile = MapR[x][y];
            break;
        }
    }

    if (plane == 1 && tile >= 0x51 && tile <= 0x53) {
        if (x < 0x40 && HoleMapB[y] == x) {
            MapB[x][y] = 0x18;
            result = 1;
            if (TERRAINset == 0)
                MapA[x][y] = 0x50;
            else
                MapA[x][y] = SRand1(7) + 0x59;
        } else if (HoleMapR[y] == x) {
            MapR[x][y] = 0x18;
            result = 1;
            if (TERRAINset == 0)
                MapA[x][y] = 0x50;
            else
                MapA[x][y] = SRand1(7) + 0x59;
        } else {
            if (TERRAINset == 0)
                MapA[x][y] = SRand16();
            else
                MapA[x][y] = 0;
            result = 1;
        }
    } else if (plane > 1 && tile == 0x30) {
        value = SRand8();
        if (plane <= 1)
            ok = (x >= 0 && x <= 0x7f && y >= 0 && y <= 0x3f);
        else
            ok = (x >= 0 && x <= 0x3f && y >= 0 && y <= 0x3f);
        if (ok == 1) {
            switch (plane) {
            case 0:
            case 1:
                MapA[x][y] = value;
                break;
            case 2:
                MapB[x][y] = value;
                break;
            case 3:
                MapR[x][y] = value;
                break;
            }
            ZapEuMapAt(plane, x, y);
            result = 1;
        }
    } else if (plane > 1 && tile == 0x31) {
        if (plane == 2) {
            MapB[x][y] = 0x18;
            MapA[HoleMapB[x]][x] = 0x50;
        } else if (plane == 3) {
            MapR[x][y] = 0x18;
            MapA[HoleMapR[x]][x] = 0x50;
        }
        result = 1;
    }

    if (result != 0) {
        if (MeType == 0x10)
            MeType = 0x28;
        else
            MeType = 0x48;
        myBeginSound(0x1e, 0, 0x7e);
    }
    return result;
}
