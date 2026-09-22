/* StealFoodR: same shape as StealFoodB, against MapR/FoodR instead of
 * MapB/FoodB. See StealFoodB.c for the shared template and evidence. */

extern unsigned char near MapR[];
extern int far FoodR;
extern int far SRand8(void);

void far StealFoodR(int x, int y)
{
    int xx;
    int yy;
    unsigned char near *cell;

    xx = x;
    yy = y;
    cell = &MapR[(xx << 6) + yy];
    if (*cell == 0x10)
        *cell = (unsigned char)SRand8();
    else
        (*cell)--;
    if (FoodR > 0)
        FoodR--;
}
