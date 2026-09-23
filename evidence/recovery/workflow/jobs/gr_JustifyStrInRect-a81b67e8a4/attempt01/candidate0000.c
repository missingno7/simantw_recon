/* Position a string by the requested justification and clear its margins for mode three. */
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
    struct WinRect r;
    int x;

    r = *rect;
    if (justify == 0 || justify == 3)
        x = (r.right - font_StringWidth(string) + r.left) / 2;
    else if (justify == 1)
        x = r.left + 4;
    else if (justify == 2)
        x = r.right - font_StringWidth(string) - 4;

    if (x < r.left)
        x = r.left;
    r.top += (r.bottom - font_FontHeight() - r.top) / 2;
    font_PrintStr(x, r.top, string);
    if (justify == 3) {
        GBoxFill(_lastStrPos, r.top, r.right,
                 r.top + (int)fontHeight, _backColor);
        GBoxFill(r.left, r.top, x,
                 r.top + (int)fontHeight, _backColor);
    }
}
