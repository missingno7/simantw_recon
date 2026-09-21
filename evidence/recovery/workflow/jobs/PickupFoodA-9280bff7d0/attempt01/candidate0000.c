/*
 * Hypothesis: x*64+y selects the food cell in the private MapA band at
 * 0x28e8.  A zero TERRAINset 0x48 tile, or any tile congruent to 0x18
 * modulo four, is replaced with SRand16; all other food cells lose one
 * unit and the far FoodA total is decremented while positive.
 */
extern unsigned char near MapA[];
extern unsigned int far TERRAINset;
extern unsigned int far FoodA;
extern long SRand16(void);

void far PickupFoodA(int x, int y)
{
    unsigned char near *cell;
    int tile;

    cell = &MapA[x * 64 + y + 0x28e8];
    tile = *cell;
    if (TERRAINset == 0 && tile == 0x48) {
        *cell = (unsigned char)SRand16();
        return;
    }
    if ((tile - 0x18) % 4 == 0) {
        *cell = (unsigned char)SRand16();
        return;
    }
    --*cell;
    if (FoodA > 0)
        --FoodA;
}
