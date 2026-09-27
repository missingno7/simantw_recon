/* Normalize exclusive bounds in the four-word RECT passed to InvertRect. */
struct InvertRect { int left; int top; int right; int bottom; };
extern int near clipDC;
extern void far pascal InvertRect(int dc, struct InvertRect far *rect);
void GInvBox(int x1, int y1, int x2, int y2)
{
    struct InvertRect rect;
    rect.left = (x2 > x1) ? x1 : x2;
    rect.top = (y2 > y1) ? y1 : y2;
    rect.right = ((x2 < x1) ? x1 : x2) + 1;
    rect.bottom = ((y2 < y1) ? y1 : y2) + 1;
    InvertRect(clipDC, &rect);
}