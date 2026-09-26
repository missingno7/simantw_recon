struct Point { int x; int y; };
struct PointRect { int left; int top; int right; int bottom; };
extern int far ribbonBarHeight;
int far PointInRect(struct Point far *point, struct PointRect far *rect)
{
    if (ribbonBarHeight)
        return point->x < rect->right && point->x >= rect->left &&
               point->y >= rect->top && point->y < rect->bottom;
    return point->x <= rect->right && point->x >= rect->left &&
           point->y >= rect->top && point->y <= rect->bottom;
}
