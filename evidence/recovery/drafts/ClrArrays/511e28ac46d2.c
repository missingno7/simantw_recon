/* Clear map grids, pheromone grids, A/B/R list fields, and population maps. */
extern unsigned char near MapA[];
extern unsigned char near LifeA[];
extern unsigned char near MapB[];
extern unsigned char near MapR[];
extern unsigned char near LifeB[];
extern unsigned char near LifeR[];
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) ExitMapB[4096];
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) ExitMapR[4096];
extern unsigned int __based(__segname("SIMANT_DATA_GROUP")) AlistS[500];
extern unsigned int __based(__segname("SIMANT_DATA_GROUP")) AlistM[500];
extern unsigned int __based(__segname("SIMANT_DATA_GROUP")) AlistT[500];
extern unsigned int __based(__segname("SIMANT_DATA_GROUP")) RlistS[250];
extern unsigned int __based(__segname("SIMANT_DATA_GROUP")) RlistM[250];
extern unsigned int __based(__segname("SIMANT_DATA_GROUP")) RlistT[250];
extern unsigned int __based(__segname("SIMANT_DATA_GROUP")) BlistS[250];
extern unsigned int __based(__segname("SIMANT_DATA_GROUP")) BlistM[250];
extern unsigned int __based(__segname("SIMANT_DATA_GROUP")) BlistT[250];
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) PherMapA[2048];
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) PherMapF[2048];
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) PherMapBN[2048];
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) PherMapBT[2048];
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) PherMapRN[2048];
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) PherMapRT[2048];
extern unsigned char far YMapPopB[192];
extern unsigned char far YMapPopR[192];
extern unsigned char far Dx8[];
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
            ExitMapB[row + col] = 0;
            ExitMapR[row + col] = 0;
            LifeB[row + col] = 0;
            LifeR[row + col] = 0;
        }
    }
    for (row = 0; row < 0x800; row += 0x20) {
        for (col = 0; col < 0x20; ++col) {
            PherMapA[row + col] = 0;
            PherMapF[row + col] = 0;
            PherMapBN[row + col] = 0;
            PherMapBT[row + col] = 0;
            PherMapRN[row + col] = 0;
            PherMapRT[row + col] = 0;
        }
    }
    for (i = 0; i < 500; ++i) ((unsigned int far *)Dx8)[i + 0x19a6] = 0;
    for (i = 0; i < 500; ++i) ((unsigned int far *)Dx8)[i + 0x15bc] = 0;
    for (i = 0; i < 500; ++i) ((unsigned int far *)Dx8)[i + 0x17b1] = 0;
    for (i = 0; i < 250; ++i) ((unsigned int far *)Dx8)[i + 0x246e] = 0;
    for (i = 0; i < 250; ++i) ((unsigned int far *)Dx8)[i + 0x2278] = 0;
    for (i = 0; i < 250; ++i) ((unsigned int far *)Dx8)[i + 0x2373] = 0;
    for (i = 0; i < 250; ++i) ((unsigned int far *)Dx8)[i + 0x1f87] = 0;
    for (i = 0; i < 250; ++i) ((unsigned int far *)Dx8)[i + 0x1d91] = 0;
    for (i = 0; i < 250; ++i) ((unsigned int far *)Dx8)[i + 0x1e8c] = 0;
    for (row = 0; row < 0xc0; row += 0x10) {
        for (col = 0; col < 0x10; ++col) {
            YMapPopB[row + col] = 0;
            YMapPopR[row + col] = 0;
        }
    }
}

