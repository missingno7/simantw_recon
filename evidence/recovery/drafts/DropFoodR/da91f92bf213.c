/* Repeated two-dimensional lvalue lets MSC share one computed cell address. */
extern unsigned char near MapR[64][64];
extern int far FoodR;
extern int far Tindex;
extern unsigned char far Dx8[];
int far DropFoodR(int x, int y)
{
    int level;
    int result;
    unsigned char far *attrPtr;

    result = 0;
    level = MapR[x][y];
    if (level < 16) {
        MapR[x][y] = 16;
        result = 1;
    } else if (level < 19) {
        MapR[x][y]++;
        result = 1;
    }
    ++FoodR;
    attrPtr = &Dx8[Tindex + 0x46e6];
    if (*attrPtr & 8)
        *attrPtr -= 8;
    return result;
}
