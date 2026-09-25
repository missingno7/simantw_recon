/* GInvBox: normalize the exclusive rectangle bounds from two corners, then ask Windows to invert it in clipDC. */
struct InvertRect {
    int left;
    int top;
    int right;
    int bottom;
};

extern int near clipDC;
extern void far pascal InvertRect(int dc, struct InvertRect far *rect);

void GInvBox(volatile int x1, volatile int y1, volatile int x2, volatile int y2)
{
    struct InvertRect rect;

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
