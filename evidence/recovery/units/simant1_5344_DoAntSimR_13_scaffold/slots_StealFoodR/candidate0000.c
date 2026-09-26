/* Update the R colony map cell at x*64+y: replace the food marker with
 * SRand8's byte, otherwise decrement the cell, then reduce FoodR when positive. */
extern unsigned char near MapR[];
extern int far FoodR;
extern int far SRand8(void);

void far StealFoodR(int x, int y)
{
    if (MapR[(x << 6) + y] == 0x10)
        MapR[(x << 6) + y] = (unsigned char)SRand8();
    else
        MapR[(x << 6) + y]--;

    if (FoodR > 0)
        FoodR--;
}
