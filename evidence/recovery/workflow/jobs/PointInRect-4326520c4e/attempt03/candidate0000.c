/*
 * Hypothesis: test a far point against a far four-word rectangle.  The
 * ribbon-bar mode uses half-open right/bottom bounds; the inactive mode uses
 * inclusive bounds.  Segment 10 offset 0xbd0a is the exact ribbonBarHeight
 * binding from the symbol map and selector evidence.
 */
struct PointRect {
    int left;
    int top;
    int right;
    int bottom;
};

struct Point {
    int x;
    int y;
};

extern int far ribbonBarHeight;

int far PointInRect(struct Point far *point, struct PointRect far *rect)
{
    int mode;

    mode = ribbonBarHeight;
    if (mode) {
        if (point->x >= rect->right)
            return 0;
        if (point->x < rect->left)
            return 0;
        if (point->y < rect->top)
            return 0;
        if (point->y >= rect->bottom)
            return 0;
        return 1;
    }

    if (point->x > rect->right)
        return 0;
    if (point->x < rect->left)
        return 0;
    if (point->y < rect->top)
        return 0;
    if (point->y > rect->bottom)
        return 0;
    return 1;
}
