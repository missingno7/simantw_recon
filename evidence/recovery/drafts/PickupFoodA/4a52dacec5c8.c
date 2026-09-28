extern unsigned char near MapA[128][64];
extern unsigned int far TERRAINset;
extern int far FoodA;
extern int far SRand16(void);
void far PickupFoodA(int x, int y)
{
    unsigned char near * volatile cell;
    volatile int tile;
    cell = &MapA[x][y];
    tile = *cell;
    if (TERRAINset == 0) {
        if (tile == 0x48) {
            *cell = (unsigned char)SRand16();
            goto update_count;
        }
        goto decrement_cell;
    }
    if (tile % 4 == 0) {
        *cell = (unsigned char)((tile - 0x18) >> 2);
        goto update_count;
    }
decrement_cell:
    --*cell;
update_count:
    if (FoodA <= 0)
        return;
    --FoodA;
}