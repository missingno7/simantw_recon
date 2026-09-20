struct InvertRect {
    int left;
    int top;
    int right;
    int bottom;
};

extern int near clipDC;
extern void far pascal InvertRect(int dc, struct InvertRect far *rect);

void GInvBox(int x1, int y1, int x2, int y2)
{
    volatile struct InvertRect rect;

    rect.left = x2;
    if (x2 > x1)
        rect.left = x1;
    rect.top = y2;
    if (y2 > y1)
        rect.top = y1;
    rect.right = x2;
    if (x2 < x1) {
        rect.right = x1;
        ++rect.right;
    }
    rect.bottom = y2;
    if (y2 < y1) {
        rect.bottom = y1;
        ++rect.bottom;
    }
    InvertRect(clipDC, (struct InvertRect far *)&rect);
}
