/*
 * EatFoodR: a R-colony ant eats at nest cell (x, y).  The near MapR cell
 * (verified near map convention) is kept in a stack pointer across the
 * SRand8 call: a fresh food tile (0x10) is replaced by a random byte,
 * otherwise the cell byte is decremented.  While the colony still has
 * far FoodR, one unit is consumed and EatCountR (far, as in the verified
 * DecEatR sibling) grows by 5; once it exceeds (RpopT + CastePopR[2]) >> 4
 * it resets to zero and colony HealthR rises toward 100.  RpopT, HealthR
 * and CastePopR are near DGROUP words (CastePopR+4 is the MAPSYM binding of
 * the second addend).  FoodR and EatCountR are reached through segment-9
 * selector slots 0xc394 and 0xc3a4.
 */
extern int far SRand8(void);
extern unsigned char near MapR[];
extern int far FoodR;
extern int far EatCountR;
extern int near RpopT;
extern int near CastePopR[];
extern int near HealthR;

void far EatFoodR(int x, int y)
{
    unsigned char near *cell;

    cell = &MapR[x * 64 + y];
    if (*cell == 0x10)
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
