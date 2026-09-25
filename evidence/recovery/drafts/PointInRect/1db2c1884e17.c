/*
 * Evaluate the point coordinates before the corresponding rectangle bounds,
 * holding each coordinate while the far rectangle field is compared.
 */
struct Point {
    int x;
    int y;
};
struct PointRect {
    int left;
    int top;
    int right;
    int bottom;
};

extern int __based(__segname("SIMANT_DATA_GROUP")) ribbonBarHeight;

int far PointInRect(struct Point far *point, struct PointRect far *rect)
{
    int value;

    if (ribbonBarHeight) {
        value = point->x;
        if (value >= rect->right)
            return 0;
        if (value < rect->left)
            return 0;
        value = point->y;
        if (value < rect->top)
            return 0;
        if (value >= rect->bottom)
            return 0;
        return 1;
    }

    value = point->x;
    if (value > rect->right)
        return 0;
    if (value < rect->left)
        return 0;
    value = point->y;
    if (value < rect->top)
        return 0;
    if (value > rect->bottom)
        return 0;
    return 1;
}
