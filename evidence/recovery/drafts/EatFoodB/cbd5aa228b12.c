/*
 * EatFoodB: a B-colony ant eats at nest cell (x, y) of the near MapB map
 * (verified near map convention).  A fresh food tile (0x10) is replaced by
 * a random byte, otherwise the cell byte is decremented; the repeated cell
 * address is the compiler's common-subexpression temp kept in the frame
 * across the SRand8 call.  While the colony still has far FoodB, one unit
 * is consumed and EatCountB (far, as in the verified DecEatB sibling) grows
 * by 5; once it exceeds (BpopT + CastePopB[2]) >> 4 it resets to zero and
 * colony HealthB rises toward 100.  BpopT, HealthB and CastePopB are near
 * DGROUP words (CastePopB+4 is the MAPSYM binding of the second addend).
 * FoodB and EatCountB are reached through segment-9 selector slots 0xc362
 * and 0xc374.
 */
extern int far SRand8(void);
extern unsigned char near MapB[];
extern int far FoodB;
extern int far EatCountB;
extern int near BpopT;
extern int near CastePopB[];
extern int near HealthB;

void far EatFoodB(int x, int y)
{
    if (MapB[x * 64 + y] == 0x10)
        MapB[x * 64 + y] = SRand8();
    else
        MapB[x * 64 + y]--;
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
