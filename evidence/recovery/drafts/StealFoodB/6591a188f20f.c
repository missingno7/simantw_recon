/* Update the B colony map cell at x*64+y: replace the food marker with
 * SRand8's byte, otherwise decrement the cell, then reduce FoodB when positive. */
extern unsigned char near MapB[];
extern int far FoodB;
extern int far SRand8(void);

void far StealFoodB(int x, int y)
{
    if (MapB[(x << 6) + y] == 0x10)
        MapB[(x << 6) + y] = (unsigned char)SRand8();
    else
        MapB[(x << 6) + y]--;

    if (FoodB > 0)
        FoodB--;
}
