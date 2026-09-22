/*
 * IsThisFood delegates non-basic categories to IsItFood.  Category values
 * zero and one use the local food tile band 0x10..0x13, returning a 16-bit
 * boolean.
 */
extern int far IsItFood(int tile);

int IsThisFood(int category, int tile)
{
    int result;

    if (category <= 1)
        return IsItFood(tile);
    if (tile < 0x10 || tile > 0x13)
        result = 0;
    else
        result = 1;
    return result;
}
