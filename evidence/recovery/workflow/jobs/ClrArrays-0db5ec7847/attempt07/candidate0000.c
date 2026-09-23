/* Clear map grids, pheromone grids, A/B/R list fields, and population maps. */
extern unsigned char near MapA[];
extern unsigned char near LifeA[];
extern unsigned char near MapB[];
extern unsigned char near MapR[];
extern unsigned char near LifeB[];
extern unsigned char near LifeR[];
extern unsigned char far Dx8;
#define AT(off) ((&Dx8)[off])
void far ClrArrays(void)
{
    int col;
    int row;
    int i;
    unsigned int far *words;
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
            AT(row + col + 0x3a4) = 0;
            AT(row + col + 0x13a4) = 0;
            LifeB[row + col] = 0;
            LifeR[row + col] = 0;
        }
    }
    for (row = 0; row < 0x800; row += 0x20) {
        for (col = 0; col < 0x20; ++col) {
            AT(row + col + 0x52d2) = 0;
            AT(row + col + 0x5ad2) = 0;
            AT(row + col + 0x62d2) = 0;
            AT(row + col + 0x6ad2) = 0;
            AT(row + col + 0x72d2) = 0;
            AT(row + col + 0x7ad2) = 0;
        }
    }
    words = (unsigned int far *)&Dx8;
    words += 0x334c / 2;
    for (i = 0; i < 500; ++i) *words++ = 0;
    words = (unsigned int far *)&Dx8;
    words += 0x2b78 / 2;
    for (i = 0; i < 500; ++i) *words++ = 0;
    words = (unsigned int far *)&Dx8;
    words += 0x2f62 / 2;
    for (i = 0; i < 500; ++i) *words++ = 0;
    words = (unsigned int far *)&Dx8;
    words += 0x48dc / 2;
    for (i = 0; i < 250; ++i) *words++ = 0;
    words = (unsigned int far *)&Dx8;
    words += 0x44f0 / 2;
    for (i = 0; i < 250; ++i) *words++ = 0;
    words = (unsigned int far *)&Dx8;
    words += 0x46e6 / 2;
    for (i = 0; i < 250; ++i) *words++ = 0;
    words = (unsigned int far *)&Dx8;
    words += 0x3f0e / 2;
    for (i = 0; i < 250; ++i) *words++ = 0;
    words = (unsigned int far *)&Dx8;
    words += 0x3b22 / 2;
    for (i = 0; i < 250; ++i) *words++ = 0;
    words = (unsigned int far *)&Dx8;
    words += 0x3d18 / 2;
    for (i = 0; i < 250; ++i) *words++ = 0;
    for (row = 0; row < 0xc0; row += 0x10) {
        for (col = 0; col < 0x10; ++col) {
            AT(row + col + 0xa4) = 0;
            AT(row + col + 0x164) = 0;
        }
    }
}
