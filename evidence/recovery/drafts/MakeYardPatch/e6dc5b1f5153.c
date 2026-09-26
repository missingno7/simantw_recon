/*
 * MakeYardPatch(void): builds one randomized yard terrain patch. When
 * TERRAINset != 0 it sets CurGndTileID = 0x3e8, calls
 * OverlayTileSet(0, 0x3e8), and randomizes the entire MapA[128][64] with
 * SRand16() bytes. It then always calls AddRocks(), InitAntLions(SRand4()
 * + 1), and InitPillar(), and finally makes four passes of random-position
 * decoration placement, each attempting a fixed number of random (row,
 * col) picks (row = SRand1(0x7d) + 1, col = SRand1(0x3d) + 1) regardless
 * of success, and stamping the target cells only when every checked
 * neighbour is still below 0x18 (background/passable): 20 attempts place a
 * 2x2 object (0x20/0x21/0x22/0x23 at (row,col)/(row+1,col)/(row,col+1)/
 * (row+1,col+1)); 30 attempts place a vertical 2-tall object with two
 * random variants ((SRand1(2)+0x12)<<1 at (row,col), one more at
 * (row+1,col)); 100 attempts place a single 0x28 tile; 128 attempts place
 * a single 0x51 tile. MapA and the SRand family are reused verbatim from
 * the RandWorld/DigOutBNest-DigOutRNest translation unit
 * (src/recovered/wf_tu_simtwo_5AB0_RandWorld_5-2079c82816.c,
 * src/recovered/wf_tu_simtwo_5AB0_RandWorld_12-c7664162e4.c). CurGndTileID
 * is the exact MAPSYM name at SIMANT_DATA_GROUP 34282
 * (evidence/symbols/symbols.csv). OverlayTileSet/AddRocks/InitAntLions/
 * InitPillar are not yet recovered in this unit (simone:3120); their
 * signatures are inferred from the exact push order and argument count at
 * each call site.
 */
extern unsigned char near MapA[128][64];
extern int far TERRAINset;
extern int far CurGndTileID;

extern void far OverlayTileSet(int a, int b);
extern int far SRand16(void);
extern void far AddRocks(void);
extern int far SRand4(void);
extern void far InitAntLions(int count);
extern void far InitPillar(void);
extern int far SRand1(int range);

void far MakeYardPatch(void)
{
    int r;
    int c;
    int row;
    int col;
    int i;

    if (TERRAINset != 0) {
        CurGndTileID = 0x3e8;
        OverlayTileSet(0, 0x3e8);

        for (r = 0; r < 128; r++) {
            for (c = 0; c < 64; c++)
                MapA[r][c] = (unsigned char)SRand16();
        }
    }

    AddRocks();
    InitAntLions(SRand4() + 1);
    InitPillar();

    for (i = 0; i < 0x14; i++) {
        row = SRand1(0x7d) + 1;
        col = SRand1(0x3d) + 1;
        if (MapA[row][col] < 0x18 && MapA[row + 1][col] < 0x18 &&
            MapA[row][col + 1] < 0x18 && MapA[row + 1][col + 1] < 0x18) {
            MapA[row][col] = 0x20;
            MapA[row + 1][col] = 0x21;
            MapA[row][col + 1] = 0x22;
            MapA[row + 1][col + 1] = 0x23;
        }
    }

    for (i = 0; i < 0x1e; i++) {
        row = SRand1(0x7d) + 1;
        col = SRand1(0x3d) + 1;
        if (MapA[row][col] < 0x18 && MapA[row + 1][col] < 0x18) {
            MapA[row][col] = (unsigned char)((SRand1(2) + 0x12) << 1);
            MapA[row + 1][col] = (unsigned char)(MapA[row][col] + 1);
        }
    }

    for (i = 0; i < 0x64; i++) {
        row = SRand1(0x7d) + 1;
        col = SRand1(0x3d) + 1;
        if (MapA[row][col] < 0x18)
            MapA[row][col] = 0x28;
    }

    for (i = 0; i < 0x80; i++) {
        row = SRand1(0x7d) + 1;
        col = SRand1(0x3d) + 1;
        if (MapA[row][col] < 0x18)
            MapA[row][col] = 0x51;
    }
}
