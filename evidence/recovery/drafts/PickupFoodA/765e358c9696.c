/* Hypothesis: test tile modulo four, then use a signed shift for the remapped code. */
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
    if (TERRAINset == 0) {
        if (tile == 0x48) {
            MapA[row][y] = (unsigned char)SRand16();
            goto update_count;
        }
        goto decrement_cell;
    }
    if (tile % 4 == 0) {
        MapA[row][y] = (unsigned char)((tile - 0x18) >> 2);
        goto update_count;
    }
decrement_cell:
    --MapA[row][y];
update_count:
    if (FoodA <= 0)
        return;
    --FoodA;
}
