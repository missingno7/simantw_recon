/* Keep the selected cell address across classification and randomization. */
extern unsigned char near MapA[];
extern int far FoodA;
extern int far IsItFood(int tile);
extern long far SRand16(void);

void far SubtractFood(void)
{
    register int row;
    register int column;
    unsigned char near * volatile cell;

    row = 0;
    while (row < 0x2000) {
        column = 0;
        while (column < 0x40) {
            if (IsItFood(*(cell = &MapA[row + column])) == 1)
                *cell = (unsigned char)SRand16();
            ++column;
        }
        row += 0x40;
    }
    FoodA = 0;
}
