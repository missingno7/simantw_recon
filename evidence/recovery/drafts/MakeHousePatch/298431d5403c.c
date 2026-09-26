extern int far TERRAINset;
extern int far CurGndTileID;
extern int far DROPdir;
extern unsigned char near MapA[128][64];
extern char near commandStr[];
extern void far OverlayTileSet(int type, int id);
extern void far InitAntLions(int mode);
extern void far InitPillar(void);
extern void far MakeKitchenWall(void);
extern void far MakeSink(void);
extern void far FloorTiles(void);
extern void far CarpetFloorL(void);
extern void far CarpetFloorR(void);
extern void far FillMapLegs(int x1, int y1, int x2, int y2, int tile);

void far MakeHousePatch(int patch)
{
    int row;
    int col;

    if (TERRAINset != 1) {
        CurGndTileID = 0x3e9;
        OverlayTileSet(0, 0x3e9);
        InitAntLions(0);
    }
    InitPillar();

    switch (patch) {
    default:
    case 1:
    case 16:
    case 32:
        MakeKitchenWall();
        break;
    case 0:
        MakeKitchenWall();
        MakeSink();
        break;
    case 2:
    case 3:
    case 17:
    case 18:
    case 19:
    case 33:
    case 34:
    case 35:
        FloorTiles();
        break;
    case 4:
    case 10:
    case 11:
    case 13:
    case 14:
        CarpetFloorL();
        break;
    case 5:
        CarpetFloorL();
        for (row = 24; row <= 70; ++row) {
            for (col = 20; col < 64; ++col)
                MapA[row][col] = 2;
        }
        for (row = 0; row < 3; ++row) {
            for (col = 0; col < 3; ++col)
                MapA[40 + row][45 + col] =
                    (unsigned char)commandStr[0x33c + row + col * 3];
        }
        break;
    case 6:
        CarpetFloorL();
        for (row = 24; row <= 70; ++row) {
            for (col = 0; col < 64; col += 2)
                *((unsigned int near *)&MapA[row][col]) = 0x0202;
        }
        for (row = 0; row < 3; ++row) {
            for (col = 0; col < 3; ++col)
                MapA[32 + row][20 + col] =
                    (unsigned char)commandStr[0x33c + row + col * 3];
        }
        for (row = 0; row < 3; ++row) {
            for (col = 0; col < 3; ++col) {
                if (commandStr[0x346 + row + col * 3] != 0)
                    MapA[38 + row][23 + col] =
                        (unsigned char)commandStr[0x346 + row + col * 3];
            }
        }
        break;
    case 7:
        CarpetFloorL();
        for (row = 24; row <= 70; ++row) {
            for (col = 0; col < 20; col += 2)
                *((unsigned int near *)&MapA[row][col]) = 0x0202;
            MapA[row][20] = 2;
        }
        for (row = 0; row < 3; ++row) {
            for (col = 0; col < 3; ++col) {
                if (commandStr[0x346 + row + col * 3] != 0)
                    MapA[42 + row][10 + col] =
                        (unsigned char)commandStr[0x346 + row + col * 3];
            }
        }
        break;
    case 8:
        CarpetFloorL();
        FillMapLegs(0x18, 0x36, 0x0f, 0x2d, 2);
        for (row = 0; row < 3; ++row) {
            for (col = 0; col < 3; ++col) {
                if (commandStr[0x346 + row + col * 3] != 0)
                    MapA[28 + row][34 + col] =
                        (unsigned char)commandStr[0x346 + row + col * 3];
            }
        }
        break;
    case 9:
        for (row = 0; row < 128; ++row) {
            for (col = 0; col < 64; col += 2)
                *((unsigned int near *)&MapA[row][col]) = 0x0303;
        }
        DROPdir = 2;
        break;
    case 12:
        CarpetFloorL();
        FillMapLegs(0x2d, 0x5f, 8, 0x2e, 2);
        break;
    case 15:
        CarpetFloorL();
        FillMapLegs(0x32, 0x64, 10, 0x2d, 2);
        for (row = 0; row < 3; ++row) {
            for (col = 0; col < 3; ++col)
                MapA[75 + row][34 + col] =
                    (unsigned char)commandStr[0x33c + row + col * 3];
        }
        break;
    case 20:
    case 21:
    case 22:
    case 23:
    case 24:
    case 25:
    case 26:
    case 27:
    case 28:
    case 29:
    case 30:
    case 31:
        CarpetFloorR();
        break;
    case 36:
    case 37:
        for (row = 0; row < 128; ++row) {
            for (col = 0; col < 64; col += 2)
                *((unsigned int near *)&MapA[row][col]) = 0;
        }
        DROPdir = 2;
        break;
    }
}
