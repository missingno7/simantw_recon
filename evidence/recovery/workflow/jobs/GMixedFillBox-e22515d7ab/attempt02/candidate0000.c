/*
 * Hypothesis: equal foreground/background colors use a solid fill, while
 * differing colors use the historical checker-pattern path.  The attribute
 * call receives the two color arguments and pattern 0x20; the checker word
 * is then derived from the shared foreground attribute.  The packet's DS
 * byte has no exact MAPSYM name, so this uses the already evidenced
 * foreground-color binding rather than a numeric address.
 */
extern int near _foreColor;
extern void far GSetAttrib(int foreColor, int backColor, int pattern);
extern void far GPatBox(int left, int top, int right, int bottom,
                        unsigned int pattern);
extern void far GBoxFill(int left, int top, int right, int bottom, int color);

void far GMixedFillBox(int left, int top, int right, int bottom,
                       int foreColor, int backColor)
{
    if (backColor != foreColor) {
        GSetAttrib(foreColor, backColor, 0x20);
        GPatBox(left, top, right, bottom,
                (((_foreColor >> 8) + 0x10) << 8) | 0x20);
    } else {
        GBoxFill(left, top, right, bottom, foreColor);
    }
}
