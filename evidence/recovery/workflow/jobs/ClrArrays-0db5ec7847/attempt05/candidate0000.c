/* Clear map grids, pheromone grids, A/B/R list fields, and population maps. */
struct Dx8Data {
    unsigned char gap0000[0x00a4];
    unsigned char yMapPopB[0x00c0];
    unsigned char yMapPopR[0x00c0];
    unsigned char gap0224[0x0180];
    unsigned char exitMapB[0x1000];
    unsigned char exitMapR[0x1000];
    unsigned char AlistX[1000];
    unsigned char gap278c[2];
    unsigned char AlistY[1000];
    unsigned char gap2b76[2];
    unsigned char AlistM[1000];
    unsigned char gap2f60[2];
    unsigned char AlistT[1000];
    unsigned char gap334a[2];
    unsigned int AlistS[500];
    unsigned char gap3734[0x03ee];
    unsigned int BlistM[250];
    unsigned char gap3d16[2];
    unsigned int BlistT[250];
    unsigned char gap3f0c[2];
    unsigned int BlistS[250];
    unsigned char gap4102[0x03ee];
    unsigned int RlistM[250];
    unsigned char gap46e4[2];
    unsigned int RlistT[250];
    unsigned char gap48da[2];
    unsigned int RlistS[250];
    unsigned char gap4ad0[0x0802];
    unsigned char PherMapA[0x0800];
    unsigned char PherMapF[0x0800];
    unsigned char PherMapBN[0x0800];
    unsigned char PherMapBT[0x0800];
    unsigned char PherMapRN[0x0800];
    unsigned char PherMapRT[0x0800];
};
extern struct Dx8Data far Dx8;
extern unsigned char near MapA[];
extern unsigned char near LifeA[];
extern unsigned char near MapB[];
extern unsigned char near MapR[];
extern unsigned char near LifeB[];
extern unsigned char near LifeR[];

void far ClrArrays(void)
{
    int col;
    int row;
    int i;

    for (row = 0; row < 0x2000; row += 0x40) {
        for (col = 0; col < 0x40; ++col) {
            MapA[row + col] = 0;
            LifeA[row + col] = 0;
        }
    }
    for (row = 0; row < 0x1000; row += 0x40) {
        for (col = 0; col < 0x40; ++col) {
            MapB[row + col] = 0;
            MapR[row + col] = 0;
            Dx8.exitMapB[row + col] = 0;
            Dx8.exitMapR[row + col] = 0;
            LifeB[row + col] = 0;
            LifeR[row + col] = 0;
        }
    }
    for (row = 0; row < 0x800; row += 0x20) {
        for (col = 0; col < 0x20; ++col) {
            Dx8.PherMapA[row + col] = 0;
            Dx8.PherMapF[row + col] = 0;
            Dx8.PherMapBN[row + col] = 0;
            Dx8.PherMapBT[row + col] = 0;
            Dx8.PherMapRN[row + col] = 0;
            Dx8.PherMapRT[row + col] = 0;
        }
    }
    for (i = 0; i < 500; ++i) Dx8.AlistS[i] = 0;
    for (i = 0; i < 500; ++i) Dx8.AlistM[i] = 0;
    for (i = 0; i < 500; ++i) Dx8.AlistT[i] = 0;
    for (i = 0; i < 250; ++i) Dx8.RlistS[i] = 0;
    for (i = 0; i < 250; ++i) Dx8.RlistM[i] = 0;
    for (i = 0; i < 250; ++i) Dx8.RlistT[i] = 0;
    for (i = 0; i < 250; ++i) Dx8.BlistS[i] = 0;
    for (i = 0; i < 250; ++i) Dx8.BlistM[i] = 0;
    for (i = 0; i < 250; ++i) Dx8.BlistT[i] = 0;
    for (row = 0; row < 0xc0; row += 0x10) {
        for (col = 0; col < 0x10; ++col) {
            Dx8.yMapPopB[row + col] = 0;
            Dx8.yMapPopR[row + col] = 0;
        }
    }
}
