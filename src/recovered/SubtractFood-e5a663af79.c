extern unsigned char near MapA[];
extern int far FoodA;
extern int far IsItFood(int tile);
extern long far SRand16(void);

void far SubtractFood(void)
{
    int column, row;
    for (row = 0; row < 0x2000; row += 0x40)
        for (column = 0; column < 0x40; column++)
            if (IsItFood(MapA[row + column]) == 1)
                MapA[row + column] = (unsigned char)SRand16();
    FoodA = 0;
}
