/* Store food on the map cell, report whether the pile grew, increment the food total, and clear the carrying bit in the ant record. */
extern unsigned char near MapB[];
extern int far FoodB;
extern int far Tindex;
extern unsigned char far Dx8[];

int far DropFoodB(int x, int y)
{
    unsigned char near *volatile cell;
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
