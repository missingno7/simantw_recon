/* DropFoodB(x, y) drops a black ant's carried food onto MapB[(x<<6)+y]:
 * a fresh/low tile (<0x10) is set to the minimum food-pile value 0x10; an
 * existing pile in [0x10,0x13) is grown by one; a mature pile (>=0x13) is
 * left alone. The first two cases report success (result=1), the third
 * reports 0. In every case FoodB is incremented and the dropping ant's own
 * BlistT attribute byte (Dx8[Tindex+0x3d18], via an explicit far pointer --
 * the target spills a 4-byte far pointer to the stack for it, matching an
 * "unsigned char far *attrPtr" local) has its carrying bit (8) cleared if
 * set.
 *
 * DropFoodR is the identical shape against MapR/FoodR/Dx8[Tindex+0x46e6]
 * (the constant 0x9CE B/R field-offset shift already established for
 * KillTailB/R). */

extern unsigned char near MapB[];
extern int far FoodB;
extern int far Tindex;
extern unsigned char far Dx8[];

int far DropFoodB(int x, int y)
{
    unsigned char near *cell;
    unsigned char far *attrPtr;
    int result;
    int level;

    result = 0;
    cell = &MapB[(x << 6) + y];
    level = *cell;
    if (level < 0x10) {
        *cell = 0x10;
        result = 1;
    } else if (level < 0x13) {
        (*cell)++;
        result = 1;
    }
    FoodB++;
    attrPtr = &Dx8[Tindex + 0x3d18];
    if (*attrPtr & 8)
        *attrPtr -= 8;
    return result;
}
