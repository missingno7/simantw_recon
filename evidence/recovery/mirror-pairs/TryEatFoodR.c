/* Derived mechanically from the mirrored colony function _TryEatFoodB (tools/mirror_pairs.py):
 * colony-specific MAPSYM identifiers swapped BpopT->RpopT, CastePopB->CastePopR, DecEatB->DecEatR, EatCountB->EatCountR, EatFoodB->EatFoodR, FoodB->FoodR, HealthB->HealthR, MapB->MapR, TryEatFoodB->TryEatFoodR; constants and structure unchanged.
 * Verified only by the strict matcher; where the pair is not a pure mirror the
 * diagnostic names the asymmetry. */
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
