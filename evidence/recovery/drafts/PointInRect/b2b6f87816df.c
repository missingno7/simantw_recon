/*
 * Test the global mode before materializing branch-local point and rectangle
 * pointers.  Each mode uses the same values with its own edge inclusivity.
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
    if (ribbonBarHeight) {
        register struct Point far *p;
        register struct PointRect far *r;

        p = point;
        r = rect;
        if (p->x >= r->right)
            return 0;
        if (p->x < r->left)
            return 0;
        if (p->y < r->top)
            return 0;
        if (p->y >= r->bottom)
            return 0;
        return 1;
    } else {
        register struct Point far *p;
        register struct PointRect far *r;

        p = point;
        r = rect;
        if (p->x > r->right)
            return 0;
        if (p->x < r->left)
            return 0;
        if (p->y < r->top)
            return 0;
        if (p->y > r->bottom)
            return 0;
        return 1;
    }
}
