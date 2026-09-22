/* StealFoodB looks up the black ant's target map cell MapB[(x<<6)+y] through
 * a near pointer local (matches the RaidInB/CheckNestFightB idiom in the
 * admitted simant1:2D4E unit: &MapB[(x<<6)+y] kept on the stack so the far
 * call below doesn't need to recompute the address). If the cell holds a
 * fresh food pile (0x10) it is reseeded with a random tile via SRand8();
 * otherwise the pile is simply decremented in place. FoodB is then
 * decremented while positive (never driven below zero).
 *
 * StealFoodR is the identical shape against MapR/FoodR -- confirmed
 * instruction-for-instruction identical apart from the named far/near
 * objects (same enter/frame size, same branch layout, same far call). */

extern unsigned char near MapB[];
extern int far FoodB;
extern int far SRand8(void);

void far StealFoodB(int x, int y)
{
    unsigned char near *cell;

    cell = &MapB[(x << 6) + y];
    if (*cell == 0x10)
        *cell = (unsigned char)SRand8();
    else
        (*cell)--;
    if (FoodB > 0)
        FoodB--;
}
