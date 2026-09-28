extern unsigned char near MapR[64][64];
extern int far FoodR;
extern int far SRand8(void);

void far PickupFoodR(int x, int y)
{
    int changed;
    unsigned char near * volatile cell;
    int value;

    changed = 0;
    cell = &MapR[x][y];
    value = *cell;
    if (value == 0x10) {
        MapR[x][y] = (unsigned char)SRand8();
        changed = 1;
    } else if (value >= 0x11 && value <= 0x13) {
        --MapR[x][y];
        changed = 1;
    }
    if (--changed == 0 && FoodR > 0)
        --FoodR;
}
