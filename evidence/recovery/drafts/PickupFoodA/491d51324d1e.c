/*
 * Hypothesis: the map cell is retained as a near pointer in the local frame.
 * Empty terrain plus tile 0x48 randomizes it; tiles satisfying the signed
 * (tile-0x18)%4 test are converted and stored, while other tiles are lowered.
 * A positive FoodA total is decremented after every cell update.
 */
extern unsigned char near MapA[];
extern unsigned int far TERRAINset;
extern int far FoodA;
extern int near SRand16(void);

void far PickupFoodA(int x, int y)
{
    unsigned char near *cell;
    int tile;

    cell = &MapA[(x << 6) + y];
    tile = *cell;
    if (TERRAINset == 0 && tile == 0x48) {
        *cell = (unsigned char)SRand16();
        goto update_count;
    }
    if ((tile - 0x18) % 4 == 0) {
        *cell = (unsigned char)((tile - 0x18) / 4);
        goto update_count;
    }
    --*cell;
update_count:
    if (FoodA > 0)
        --FoodA;
}
