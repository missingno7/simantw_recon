/* Derived mechanically from the mirrored colony function _PickupFoodB (tools/mirror_pairs.py):
 * colony-specific MAPSYM identifiers swapped FoodB->FoodR, MapB->MapR, PickupFoodB->PickupFoodR; constants and structure unchanged.
 * Verified only by the strict matcher; where the pair is not a pure mirror the
 * diagnostic names the asymmetry. */
/*
 * Hypothesis: the two arguments are the column and row of a B-side food
 * cell.  The cell lives in the private SIMONE_MODULE map at the observed
 * DGROUP offset 0x48e8, with a 64-byte row stride.  Tile 0x10 is replaced
 * by SRand8(); tiles 0x11 through 0x13 are consumed by one.  Either case
 * consumes one entry from the selected match_position counter at the
 * segment-9 offset represented by element 0x4f52 (0x9ea4 / sizeof(int)).
 * The target leaves the counter unchanged when the cell is outside those
 * four food values.
 */
extern unsigned char near MapR[];
extern int far match_position[];
extern int far SRand8(void);

void far PickupFoodR(int x, int y)
{
    unsigned char near *cell;
    int value;
    int changed;

    cell = MapR + (y << 6) + x;
    value = *cell;
    changed = 0;
    if (value == 0x10) {
        *cell = (unsigned char)SRand8();
        changed = 1;
    } else if (value >= 0x11 && value <= 0x13) {
        --*cell;
        changed = 1;
    }
    if (changed != 1) {
        return;
    }
    {
        if (match_position[0x4f52] > 0)
            --match_position[0x4f52];
    }
}
