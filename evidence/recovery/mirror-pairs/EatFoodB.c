/* Derived mechanically from the mirrored colony function _EatFoodR (tools/mirror_pairs.py):
 * colony-specific MAPSYM identifiers swapped CastePopR->CastePopB, DecEatR->DecEatB, EatCountR->EatCountB, EatFoodR->EatFoodB, FoodR->FoodB, HealthR->HealthB, MapR->MapB, RpopT->BpopT; constants and structure unchanged.
 * Verified only by the strict matcher; where the pair is not a pure mirror the
 * diagnostic names the asymmetry. */
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
extern unsigned char near MapB[];
extern int far FoodB;
extern int far EatCountB;
extern int near BpopT;
extern int near CastePopB[];
extern int near HealthB;

void far EatFoodB(int x, int y)
{
    unsigned char near *cell;

    cell = &MapB[x * 64 + y];
    if (*cell == 0x10)
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
