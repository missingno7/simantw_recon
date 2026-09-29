/* Repeated two-dimensional lvalue lets MSC share one computed cell address. */
extern unsigned char near MapR[];
extern int far FoodR;
extern int far Tindex;
extern char far Dx8[];
int far DropFoodR(int x, int y)
{
    int level;
    int result;

    result = 0;
    level = MapR[(x << 6) + y];
    if (level < 16) {
        MapR[(x << 6) + y] = 16;
        result = 1;
    } else if (level < 19) {
        MapR[(x << 6) + y]++;
        result = 1;
    }
    ++FoodR;
    if (Dx8[Tindex + 0x46e6] & 8)
        Dx8[Tindex + 0x46e6] -= 8;
    return result;
}
