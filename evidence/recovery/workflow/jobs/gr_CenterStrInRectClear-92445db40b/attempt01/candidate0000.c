/* Center and print a string in a rectangle, then clear unused horizontal margins. */
struct WinRect { int left; int top; int right; int bottom; };
extern int far font_StringWidth(char far *string);
extern int far font_FontHeight(void);
extern void far font_PrintStr(int x, int y, char far *string);
extern void far GBoxFill(int left, int top, int right, int bottom, int color);
extern int near _backColor;

void far gr_CenterStrInRectClear(struct WinRect far *rect, char far *string)
{
    int width;
    int x;
    struct WinRect r;

    r = *rect;
    width = font_StringWidth(string);
    x = (r.right - width + r.left) / 2;
    if (x < r.left)
        x = r.left;
    r.left = x;
    r.right = x + width;
    r.top += (r.bottom - font_FontHeight() - r.top) / 2;
    r.bottom = r.top + font_FontHeight();
    font_PrintStr(r.left, r.top, string);
    if (rect->left < r.left)
        GBoxFill(rect->left, r.top, r.left - 1, r.bottom - 1, _backColor);
    if (rect->right > r.right)
        GBoxFill(r.right, r.top, rect->right - 1, r.bottom - 1, _backColor);
}
