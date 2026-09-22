/* Derived mechanically from the mirrored colony function _DropFoodB (tools/mirror_pairs.py):
 * colony-specific MAPSYM identifiers swapped DropFoodB->DropFoodR, FoodB->FoodR, MapB->MapR; constants and structure unchanged.
 * Verified only by the strict matcher; where the pair is not a pure mirror the
 * diagnostic names the asymmetry. */
extern unsigned char near MapR[];
extern int far FoodR[];
extern int far Tindex[];
extern unsigned char far Dx8[];

int DropFoodR(int row, int column)
{
    unsigned char *cell;
    unsigned char far *ant;
    int changed;

    changed = 0;
    cell = MapR + (row << 6) + column;
    if (*cell < 0x10) {
        *cell = 0x10;
        changed = 1;
    } else if (*cell < 0x13) {
        ++*cell;
        changed = 1;
    }
    ++FoodR[0x4f52];
    ant = Dx8 + Tindex[0x4db5] + 0x3d18;
    if (*ant & 8)
        *ant -= 8;
    return changed;
}
