/* Hypothesis: use the observed 128 by 64 near map shape with reversed locals. */
extern unsigned char near MapA[128][64];
extern unsigned int far TERRAINset;
extern int far FoodA;
extern int near SRand16(void);
void far PickupFoodA(int x, int y)
{
    int tile;
    int row;
    row = x;
    tile = MapA[row][y];
    if (TERRAINset == 0 && tile == 0x48) {
        MapA[row][y] = (unsigned char)SRand16();
        goto update_count;
    }
    if ((tile - 0x18) % 4 == 0) {
        MapA[row][y] = (unsigned char)((tile - 0x18) / 4);
        goto update_count;
    }
    --MapA[row][y];
update_count:
    if (FoodA <= 0)
        return;
    --FoodA;
}
