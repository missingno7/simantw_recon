/*
 * TryEatFoodR: like EatFoodR, but only when the nest cell holds food.  The
 * near MapR cell (verified near map convention) at x*64 + y is kept in a
 * stack pointer; its value is read once and must lie in 0x10..0x13.  A
 * fresh food tile (0x10) is replaced by a random byte, otherwise the cell
 * byte is decremented.  While the colony still has far FoodR, one unit is
 * consumed and EatCountR (far, as in the verified DecEatR sibling) grows
 * by 5; once it exceeds (RpopT + CastePopR[2]) >> 4 it resets and colony
 * HealthR rises toward 100.  FoodR and EatCountR are reached through
 * segment-9 selector slots 0xc394 and 0xc3a4.
 */
extern int far SRand8(void);
extern unsigned char near MapR[];
extern int far FoodR;
extern int far EatCountR;
extern int near RpopT;
extern int near CastePopR[];
extern int near HealthR;

void far TryEatFoodR(int x, int y)
{
    unsigned char near *cell;
    int food;

    cell = &MapR[x * 64 + y];
    food = *cell;
    if (food >= 0x10 && food <= 0x13) {
        if (food == 0x10)
            *cell = SRand8();
        else
            (*cell)--;
        if (FoodR > 0) {
            FoodR--;
            EatCountR += 5;
            if ((RpopT + CastePopR[2]) >> 4 < EatCountR) {
                EatCountR = 0;
                if (HealthR < 100)
                    HealthR++;
            }
        }
    }
}
