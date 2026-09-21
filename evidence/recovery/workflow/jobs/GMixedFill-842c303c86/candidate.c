/*
 * GMixedFill: fill a far rectangle with either a checker pattern or a
 * solid colour, as the admitted GMixedFillBox does for explicit
 * coordinates.  On a monochrome-class display (displayType bit 0) the
 * colours count as different when their high nibbles differ; otherwise
 * any difference counts.  Different colours set the attribute pair with
 * pattern 0x20 and draw the checker box whose pattern word is derived from
 * the shared foreground attribute (_foreColor, high byte + 0x10, as in the
 * sibling).  Equal colours fill the box solid, but only when the far
 * rectangle pointer is non-null.  GSetAttrib, GPatBox and GBoxFill are
 * same-code-group far functions (LINK translation).
 */
struct WinRect {
    int left;
    int top;
    int right;
    int bottom;
};

extern unsigned char near displayType;
extern int near _foreColor;
extern void far GSetAttrib(int foreColor, int backColor, int pattern);
extern void far GPatBox(int left, int top, int right, int bottom,
                        unsigned int pattern);
extern void far GBoxFill(int left, int top, int right, int bottom, int color);

void far GMixedFill(struct WinRect far *rect, int foreColor, int backColor)
{
    if ((displayType & 1) ? (((foreColor ^ backColor) & 0xf0) != 0)
                          : (backColor != foreColor)) {
        GSetAttrib(foreColor, backColor, 0x20);
        GPatBox(rect->left, rect->top, rect->right, rect->bottom,
                (((_foreColor >> 8) + 0x10) << 8) | 0x20);
    } else if (rect) {
        GBoxFill(rect->left, rect->top, rect->right, rect->bottom,
                 foreColor);
    }
}
