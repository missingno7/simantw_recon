/* Repeated two-dimensional lvalue lets MSC share one computed cell address. */
extern unsigned char near MapR[64][64];
extern int far FoodR;
extern int far Tindex;
extern unsigned char far Dx8[];
int far DropFoodR(int x, int y)
{
    int level;
    int result;
    register unsigned char near *cell;
    volatile unsigned char near * volatile cellHome;
    unsigned char far *attrPtr;

    result = 0;
    cell = &MapR[x][y];
    cellHome = cell;
    level = *cell;
    if (level < 16) {
        *cell = 16;
        result = 1;
    } else if (level < 19) {
        (*cell)++;
        result = 1;
    }
    ++FoodR;
    attrPtr = &Dx8[Tindex + 0x46e6];
    if (*attrPtr & 8)
        *attrPtr -= 8;
    return result;
}
