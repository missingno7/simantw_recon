/*
 * win_RectFill: fill a rectangle using the colour table entry cached at
 * colorEntry (the private DGROUP far pointer at 0xcc58, same object used
 * by the admitted win_SetColorFromObj).  When entry[2] and entry[3]
 * differ and displayType's low bit is clear, GSetAttrib is set from
 * entry[0]/entry[2]/entry[3] (each byte sign-extended and replicated via
 * *0x101), the rectangle is patted with pattern 0 (inset by one on the
 * right/bottom when a ribbon bar is present), then GSetAttrib is
 * restored to entry[0]/entry[2]/entry[0].  Otherwise the rectangle is
 * patted directly with pattern entry[2]*0x101 (same ribbon inset rule).
 */
struct Rect {
    int left;
    int top;
    int right;
    int bottom;
};

extern void far GSetAttrib(int foreColor, int backColor, int pattern);
extern void far GPatBox(int left, int top, int right, int bottom, int pattern);
extern unsigned char near displayType;
extern int near ribbonBarHeight;
static char far *colorEntry;

void far win_RectFill(struct Rect far *rect)
{
    int fore, back, pat;

    if (colorEntry[3] != colorEntry[2] && !(displayType & 1)) {
        pat = colorEntry[3] * 0x101;
        back = colorEntry[2] * 0x101;
        fore = colorEntry[0] * 0x101;
        GSetAttrib(fore, back, pat);
        if (ribbonBarHeight != 0)
            GPatBox(rect->left, rect->top, rect->right - 1, rect->bottom - 1, 0);
        else
            GPatBox(rect->left, rect->top, rect->right, rect->bottom, 0);
        GSetAttrib(colorEntry[0] * 0x101, colorEntry[2] * 0x101, colorEntry[0] * 0x101);
    } else {
        if (ribbonBarHeight != 0)
            GPatBox(rect->left, rect->top, rect->right - 1, rect->bottom - 1, colorEntry[2] * 0x101);
        else
            GPatBox(rect->left, rect->top, rect->right, rect->bottom, colorEntry[2] * 0x101);
    }
}
