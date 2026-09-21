/*
 * TryEatFoodB: like EatFoodB, but only when the nest cell holds food.  The
 * near MapB cell (verified near map convention) at x*64 + y is kept in a
 * stack pointer; its value is read once and must lie in 0x10..0x13.  A
 * fresh food tile (0x10) is replaced by a random byte, otherwise the cell
 * byte is decremented.  While the colony still has far FoodB, one unit is
 * consumed and EatCountB (far, as in the verified DecEatB sibling) grows
 * by 5; once it exceeds (BpopT + CastePopB[2]) >> 4 it resets and colony
 * HealthB rises toward 100.  FoodB and EatCountB are reached through
 * segment-9 selector slots 0xc362 and 0xc374.
 */
extern int far SRand8(void);
extern unsigned char near MapB[];
extern int far FoodB;
extern int far EatCountB;
extern int near BpopT;
extern int near CastePopB[];
extern int near HealthB;

void far TryEatFoodB(int x, int y)
{
    unsigned char near *cell;
    int food;

    cell = &MapB[x * 64 + y];
    food = *cell;
    if (food >= 0x10 && food <= 0x13) {
        if (food == 0x10)
            *cell = SRand8();
        else
            (*cell)--;
        if (FoodB > 0) {
            FoodB--;
            EatCountB += 5;
            if ((BpopT + CastePopB[2]) >> 4 < EatCountB) {
                EatCountB = 0;
                if (HealthB < 100)
                    HealthB++;
            }
        }
    }
}
