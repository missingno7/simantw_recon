/* Derived mechanically from the mirrored colony function _DropFoodR (tools/mirror_pairs.py):
 * colony-specific MAPSYM identifiers swapped DropFoodR->DropFoodB, FoodR->FoodB, MapR->MapB; constants and structure unchanged.
 * Verified only by the strict matcher; where the pair is not a pure mirror the
 * diagnostic names the asymmetry. */
/* Repeated two-dimensional lvalue lets MSC share one computed cell address. */
extern unsigned char near MapB[64][64];
extern int far FoodB;
extern int far Tindex;
extern unsigned char far Dx8[];
int far DropFoodB(int x, int y)
{
    int level;
    int result;
    volatile unsigned char near * volatile cellHome;
    unsigned char far *attrPtr;

    result = 0;
    cellHome = &MapB[x][y];
    level = MapB[x][y];
    if (level < 16) {
        MapB[x][y] = 16;
        result = 1;
    } else if (level < 19) {
        MapB[x][y]++;
        result = 1;
    }
    ++FoodB;
    attrPtr = &Dx8[Tindex + 0x3D18];
    if (*attrPtr & 8)
        *attrPtr -= 8;
    return result;
}
