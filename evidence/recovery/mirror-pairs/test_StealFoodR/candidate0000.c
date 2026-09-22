/* Derived mechanically from the mirrored colony function _StealFoodB (tools/mirror_pairs.py):
 * colony-specific MAPSYM identifiers swapped FoodB->FoodR, StealFoodB->StealFoodR; constants and structure unchanged.
 * Verified only by the strict matcher; where the pair is not a pure mirror the
 * diagnostic names the asymmetry. */
/*
 * StealFoodB addresses the B-side nest map at x*64+y plus the historical
 * table base 0x48e8.  A cell containing the food marker 0x10 is replaced by
 * the next SRand8 byte.  The routine then decrements the shared signed food
 * counter at byte offset 0x9ea4 when that counter is positive.
 */
extern unsigned char near nestMap[];
extern int far SRand8(void);
extern int far foodState[];

void StealFoodR(int x, int y)
{
    int position;

    position = (x << 6) + y + 0x48e8;
    if (nestMap[position] == 0x10)
        nestMap[position] = (unsigned char)SRand8();
    else
        --nestMap[position];

    if (foodState[0x4f52] > 0)
        --foodState[0x4f52];
}
