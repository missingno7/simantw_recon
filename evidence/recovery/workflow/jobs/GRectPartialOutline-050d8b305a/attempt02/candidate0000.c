struct Rect {
    int left;
    int top;
    int right;
    int bottom;
};

extern void far GBoxFill(int x1, int y1, int x2, int y2, int color);

void far GRectPartialOutline(struct Rect far *rect, int thick, int sides, int color)
{
    if (thick == 0)
        return;
    if (rect == 0)
        return;
    if (sides & 2)
        GBoxFill(rect->left + thick, rect->top + thick, rect->right - thick, rect->top, color);
    if (sides & 8)
        GBoxFill(rect->left + thick, rect->bottom - thick, rect->right - thick, rect->bottom, color);
    if (sides & 1)
        GBoxFill(rect->left + thick, rect->top, rect->left, rect->bottom, color);
    if (sides & 4)
        GBoxFill(rect->right, rect->top, rect->right - thick, rect->bottom, color);
}
