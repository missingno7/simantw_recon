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

extern int far ribbonBarHeight;

int far PointInRect(int far *point, struct PointRect far *rect)
{
    int mode;

    mode = ribbonBarHeight;
    if (mode) {
        if (point[0] >= rect->right)
            return 0;
        if (point[0] < rect->left)
            return 0;
        if (point[1] < rect->top)
            return 0;
        if (point[1] >= rect->bottom)
            return 0;
        return 1;
    }

    if (point[0] > rect->right)
        return 0;
    if (point[0] < rect->left)
        return 0;
    if (point[1] < rect->top)
        return 0;
    if (point[1] > rect->bottom)
        return 0;
    return 1;
}
