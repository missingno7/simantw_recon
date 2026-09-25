/* DropFoodR: same shape as DropFoodB (see DropFoodB.c), against
 * MapR/FoodR/Dx8[Tindex+0x46e6] (the constant 0x9CE B/R field-offset
 * shift). */

extern unsigned char near MapR[];
extern int far FoodR;
extern int far Tindex;
extern unsigned char far Dx8[];

int far DropFoodR(int x, int y)
{
    unsigned char near *cell;
    unsigned char far *attrPtr;
    int result;
    int level;

    result = 0;
    cell = &MapR[(x << 6) + y];
    level = *cell;
    if (level < 0x10) {
        *cell = 0x10;
        result = 1;
    } else if (level < 0x13) {
        (*cell)++;
        result = 1;
    }
    FoodR++;
    attrPtr = &Dx8[Tindex + 0x46e6];
    if (*attrPtr & 8)
        *attrPtr -= 8;
    return result;
}
