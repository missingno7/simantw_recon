/* Derived mechanically from the mirrored colony function _EatFoodB (tools/mirror_pairs.py):
 * colony-specific MAPSYM identifiers swapped BpopT->RpopT, CastePopB->CastePopR, DecEatB->DecEatR, EatCountB->EatCountR, EatFoodB->EatFoodR, FoodB->FoodR, HealthB->HealthR, MapB->MapR; constants and structure unchanged.
 * Verified only by the strict matcher; where the pair is not a pure mirror the
 * diagnostic names the asymmetry. */
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
extern unsigned char near MapR[];
extern int far FoodR;
extern int far EatCountR;
extern int near RpopT;
extern int near CastePopR[];
extern int near HealthR;

void far EatFoodR(int x, int y)
{
    if (MapR[x * 64 + y] == 0x10)
        MapR[x * 64 + y] = SRand8();
    else
        MapR[x * 64 + y]--;
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
