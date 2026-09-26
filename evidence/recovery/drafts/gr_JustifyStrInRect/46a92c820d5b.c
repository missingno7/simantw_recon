/* Re-read caller margins with the algebraic centered-top expression. */
struct WinRect { int left; int top; int right; int bottom; };
extern int far font_StringWidth(char far *string);
extern int far font_FontHeight(void);
extern void far font_PrintStr(int x, int y, char far *string);
extern void far GBoxFill(int left, int top, int right, int bottom, int color);
extern int near _backColor;
extern int far _lastStrPos;
extern char near fontHeight;
void far gr_JustifyStrInRect(struct WinRect far *rect, char far *string, int justify)
{
    int x;
    struct WinRect r;
    r = *rect;
    switch (justify) {
    case 0: case 3: x = (r.right - font_StringWidth(string) + r.left) / 2; break;
    case 1: x = r.left + 4; break;
    case 2: x = r.right - font_StringWidth(string) - 4; break;
    }
    if (x < r.left) x = r.left;
    r.top = (r.top + r.bottom - font_FontHeight()) / 2;
    font_PrintStr(x, r.top, string);
    if (justify == 3) {
        GBoxFill(_lastStrPos, r.top, rect->right, r.top + (int)fontHeight, _backColor);
        GBoxFill(rect->left, r.top, x, r.top + (int)fontHeight, _backColor);
    }
}
