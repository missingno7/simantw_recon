/* Clear map grids, pheromone grids, A/B/R list fields, and population maps. */
extern unsigned char near MapA[];
extern unsigned char near LifeA[];
extern unsigned char near MapB[];
extern unsigned char near MapR[];
extern unsigned char near LifeB[];
extern unsigned char near LifeR[];
extern unsigned char far ExitMapB[];
extern unsigned char far ExitMapR[];
extern unsigned int far AlistS[];
extern unsigned int far AlistM[];
extern unsigned int far AlistT[];
extern unsigned int far RlistS[];
extern unsigned int far RlistM[];
extern unsigned int far RlistT[];
extern unsigned int far BlistS[];
extern unsigned int far BlistM[];
extern unsigned int far BlistT[];
extern unsigned char far PherMapA[];
extern unsigned char far PherMapF[];
extern unsigned char far PherMapBN[];
extern unsigned char far PherMapBT[];
extern unsigned char far PherMapRN[];
extern unsigned char far PherMapRT[];
extern unsigned char far YMapPopB[];
extern unsigned char far YMapPopR[];
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
    for (i = 0; i < 500; ++i) AlistS[i] = 0;
    for (i = 0; i < 500; ++i) AlistM[i] = 0;
    for (i = 0; i < 500; ++i) AlistT[i] = 0;
    for (i = 0; i < 250; ++i) RlistS[i] = 0;
    for (i = 0; i < 250; ++i) RlistM[i] = 0;
    for (i = 0; i < 250; ++i) RlistT[i] = 0;
    for (i = 0; i < 250; ++i) BlistS[i] = 0;
    for (i = 0; i < 250; ++i) BlistM[i] = 0;
    for (i = 0; i < 250; ++i) BlistT[i] = 0;
    for (row = 0; row < 0xc0; row += 0x10) {
        for (col = 0; col < 0x10; ++col) {
            YMapPopB[row + col] = 0;
            YMapPopR[row + col] = 0;
        }
    }
}
