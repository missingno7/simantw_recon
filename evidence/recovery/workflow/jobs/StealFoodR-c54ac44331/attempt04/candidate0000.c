/* StealFoodR: same shape as StealFoodB, against MapR/FoodR instead of
 * MapB/FoodB. See StealFoodB.c for the shared template and evidence. */

extern unsigned char near MapR[];
extern int far FoodR;
extern int far SRand8(void);

void far StealFoodR(int x, int y)
{
    int index;

    index = (x << 6) + y;
    if (MapR[index] == 0x10)
        MapR[index] = (unsigned char)SRand8();
    else
        MapR[index]--;
    if (FoodR > 0)
        FoodR--;
}
