/*
 * PickupMyRock revision 1: MeType 0x10/0x30 gates attempts. Plane 1 accepts
 * map tiles 0x51..0x53 and restores linked holes plus terrain; planes 2/3
 * accept 0x30/0x31, using random replacement for 0x30 and restoring the
 * paired surface hole for 0x31. Success changes MeType and plays sound 0x1e.
 * The map extents, tile bands, far hole maps, TERRAINset, random functions,
 * redraw call and sound call follow the packet and verified siblings.
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

    if (MeType != 0x10 && MeType != 0x30)
        return 0;

    result = 0;
    tile = -1;
    if (plane <= 1) {
        if (x >= 0 && x <= 0x7f && y >= 0 && y <= 0x3f) {
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
    } else {
        if (x >= 0 && x <= 0x3f && y >= 0 && y <= 0x3f) {
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
        if (plane <= 1) {
            if (x >= 0 && x <= 0x7f && y >= 0 && y <= 0x3f) {
                switch (plane) {
                case 0:
                case 1: MapA[x][y] = SRand8(); break;
                case 2: MapB[x][y] = SRand8(); break;
                case 3: MapR[x][y] = SRand8(); break;
                }
                ZapEuMapAt(plane, x, y);
                result = 1;
            }
        } else if (x >= 0 && x <= 0x3f && y >= 0 && y <= 0x3f) {
            switch (plane) {
            case 0:
            case 1: MapA[x][y] = SRand8(); break;
            case 2: MapB[x][y] = SRand8(); break;
            case 3: MapR[x][y] = SRand8(); break;
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
