/*
 * gr_CenterStrInRect: print a string centred in a rectangle.  The far
 * rectangle is copied into a local (inline movsw struct copy with DS
 * switched, as in the admitted win_GetObjRect), the string width comes
 * from font_StringWidth, and the left edge is moved to centre the string
 * horizontally, clamping to the rectangle's left edge and shrinking the
 * right edge to the string width when it does not fit.  The top edge is
 * moved down by half the spare height (bottom minus font height minus
 * top) and the bottom set to top plus the font height; the string is then
 * printed at the adjusted top-left with font_PrintStr.  The font routines
 * are same-code-group far functions (LINK translation).
 */
struct WinRect {
    int left;
    int top;
    int right;
    int bottom;
};

extern int far font_StringWidth(char far *string);
extern int far font_FontHeight(void);
extern void far font_PrintStr(int x, int y, char far *string);

void far gr_CenterStrInRect(struct WinRect far *rect, char far *string)
{
    int width;
    register int x;
    struct WinRect r;

    r = *rect;
    width = font_StringWidth(string);
    x = (r.right - width + r.left) / 2;
    if (x < r.left) {
        x = r.left;
        r.left = x;
        r.right = x + width;
    }
    (void)x;
    r.top += (r.bottom - font_FontHeight() - r.top) / 2;
    r.bottom = r.top + font_FontHeight();
    font_PrintStr(r.left, r.top, string);
}

