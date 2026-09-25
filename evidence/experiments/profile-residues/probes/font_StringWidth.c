/*
 * _font_StringWidth: pixel width of a NUL-terminated far string in a font.
 * A font without a width table (+0x26 zero) is monospaced: the result is
 * strlen(text) times the cell width at +6.  Otherwise each character adds
 * its width-table entry (far int table at +0x22/+0x24, indexed by the
 * unsigned character); an entry of -1 uses the low byte of the entry for
 * the default character (+0x28) instead, and every character also adds
 * one extra pixel when the spacing word at +8 is negative.
 */
struct Font {
    unsigned char header[6];
    int cellWidth;
    int spacing;
    unsigned char rest[0x22 - 0xa];
    int far *widths;
    int defaultChar;
};

extern unsigned int far strlen(const char far *text);

int far _font_StringWidth(char far *text, struct Font far *font)
{
    int width;
    int i;
    int extra;
    int defaultWidth;
    int entry;
    int result;

    width = 0;
    i = 0;
    if (font->widths == 0) {
        result = strlen(text) * font->cellWidth;
    } else {
        extra = (font->spacing < 0) ? 1 : 0;
        if (text[0] != 0) {
            defaultWidth = (unsigned char)font->widths[font->defaultChar];
            do {
                entry = font->widths[(unsigned char)text[i]];
                if (entry == -1)
                    width += defaultWidth;
                else
                    width += (unsigned char)entry;
                i++;
                width += extra;
            } while (text[i] != 0);
        }
        result = width;
    }
    return result;
}
