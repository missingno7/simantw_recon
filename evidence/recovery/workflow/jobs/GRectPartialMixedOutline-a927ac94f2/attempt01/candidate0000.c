/*
 * GRectPartialMixedOutline: like the admitted GRectPartialOutline, but
 * for a nonzero thickness draws each requested side (sides&2 top,
 * sides&8 bottom, sides&1 left, sides&4 right) with GPatBox instead of
 * GBoxFill, using GSetAttrib(foreColor,backColor,0x20) and the checker
 * pattern word derived from _foreColor (high byte + 0x10), as in the
 * admitted GMixedFill/GMixedFillBox.  When foreColor==backColor and the
 * display is monochrome-class (displayType bit 0 set), it instead just
 * calls the admitted GRectPartialOutline with foreColor as a solid
 * colour.  A zero thickness does nothing.
 */
struct Rect {
    int left;
    int top;
    int right;
    int bottom;
};

extern unsigned char near displayType;
extern int near _foreColor;
extern void far GSetAttrib(int foreColor, int backColor, int pattern);
extern void far GPatBox(int left, int top, int right, int bottom, unsigned int pattern);
extern void far GRectPartialOutline(struct Rect far *rect, int thick, unsigned char sides, int color);

void far GRectPartialMixedOutline(struct Rect far *rect, int thick, unsigned char sides,
                                   int foreColor, int backColor)
{
    unsigned int pattern;

    if (thick == 0)
        return;
    if (backColor == foreColor && (displayType & 1)) {
        GRectPartialOutline(rect, thick, sides, foreColor);
        return;
    }
    GSetAttrib(foreColor, backColor, 0x20);
    pattern = (((_foreColor >> 8) + 0x10) << 8) | 0x20;
    if (sides & 2)
        GPatBox(rect->left + thick, rect->top + thick, rect->right - thick, rect->top, pattern);
    if (sides & 8)
        GPatBox(rect->left + thick, rect->bottom - thick, rect->right - thick, rect->bottom, pattern);
    if (sides & 1)
        GPatBox(rect->left + thick, rect->top, rect->left, rect->bottom, pattern);
    if (sides & 4)
        GPatBox(rect->right, rect->top, rect->right - thick, rect->bottom, pattern);
}
