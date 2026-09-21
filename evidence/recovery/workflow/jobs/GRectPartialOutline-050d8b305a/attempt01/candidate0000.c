struct Rect {
    int left;
    int top;
    int right;
    int bottom;
};

extern void far GBoxFill(int x1, int y1, int x2, int y2, int color);

void far GRectPartialOutline(struct Rect far *rect, int thick, int sides, int color)
{
    struct Rect far *p;

    p = rect;
    if (thick == 0)
        return;
    if (p == 0)
        return;
    if (sides & 2)
        GBoxFill(p->left + thick, p->top + thick, p->right - thick, p->top, color);
    if (sides & 8)
        GBoxFill(p->left + thick, p->bottom - thick, p->right - thick, p->bottom, color);
    if (sides & 1)
        GBoxFill(p->left + thick, p->top, p->left, p->bottom, color);
    if (sides & 4)
        GBoxFill(p->right, p->top, p->right - thick, p->bottom, color);
}
