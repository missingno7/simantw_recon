extern unsigned char near MapB[64][64];
extern int far FoodB;
extern int far SRand8(void);

void far PickupFoodB(int x, int y)
{
    unsigned char near *cell;
    int value;
    int changed;

    cell = &MapB[x][y];
    value = *cell;
    changed = 0;
    if (value == 0x10) {
        *cell = (unsigned char)SRand8();
        changed = 1;
    } else if (value >= 0x11 && value <= 0x13) {
        --*cell;
        changed = 1;
    }
    if (changed == 1 && FoodB > 0)
        --FoodB;
}
