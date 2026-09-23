/*
 * PickupMyRock revision 2: the two accepted inventory states are 0x10 and
 * 0x30. Plane 1 uses the pebble band 0x51..0x53; underground planes use
 * 0x30/0x31. Paired HoleMap entries restore the linked 0x18 entrance and
 * surface tile 0x50; TERRAINset chooses the alternate random terrain. Tile
 * 0x30 receives an SRand8 replacement and redraw. Tile 0x31 reconnects the
 * matching black/red entrance. Successful pickup sets MeType and sound.
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
    volatile int tile;
    register int replacement;

    if (MeType != 0x10 && MeType != 0x30)
        return 0;

    result = 0;
    tile = -1;
    if (plane > 1) {
        if (x >= 0 && x <= 0x3f && y >= 0 && y <= 0x3f) {
            switch (plane) {
            case 0:
            case 1: tile = MapA[x][y]; break;
            case 2: tile = MapB[x][y]; break;
            case 3: tile = MapR[x][y]; break;
            }
        }
    } else {
        if (x >= 0 && x <= 0x7f && y >= 0 && y <= 0x3f) {
            switch (plane) {
            case 0:
            case 1: tile = MapA[x][y]; break;
            case 2: tile = MapB[x][y]; break;
            case 3: tile = MapR[x][y]; break;
            }
        }
    }

    if (plane == 1 && tile >= 0x51 && tile <= 0x53) {
        if (x < 0x40 && HoleMapB[y] == x) {
            MapB[x][y] = 0x18;
            if (TERRAINset == 0)
                MapA[x][y] = 0x50;
            else {
                replacement = SRand1(7);
                MapA[x][y] = replacement + 0x59;
            }
        } else if (HoleMapR[y] == x) {
            MapR[x][y] = 0x18;
            if (TERRAINset == 0)
                MapA[x][y] = 0x50;
            else {
                replacement = SRand1(7);
                MapA[x][y] = replacement + 0x59;
            }
        } else if (TERRAINset == 0) {
            MapA[x][y] = SRand16();
        } else {
            MapA[x][y] = 0;
        }
        result = 1;
    } else if (plane > 1 && tile == 0x30) {
        replacement = SRand8();
        if (plane <= 1) {
            if (x >= 0 && x <= 0x7f && y >= 0 && y <= 0x3f) {
                switch (plane) {
                case 0:
                case 1: MapA[x][y] = replacement; break;
                case 2: MapB[x][y] = replacement; break;
                case 3: MapR[x][y] = replacement; break;
                }
                ZapEuMapAt(plane, x, y);
                result = 1;
            }
        } else if (x >= 0 && x <= 0x3f && y >= 0 && y <= 0x3f) {
            switch (plane) {
            case 0:
            case 1: MapA[x][y] = replacement; break;
            case 2: MapB[x][y] = replacement; break;
            case 3: MapR[x][y] = replacement; break;
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
