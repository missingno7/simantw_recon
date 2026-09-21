struct Font {
    unsigned char reserved0[6];
    int fallbackWidth;
    int signedMetric;
    unsigned char reserved1[0x18];
    unsigned char far *widths;
    int mode;
    int fallbackIndex;
};

int _font_CharWidth(int character, struct Font far *font)
{
    int width;
    int glyphWidth;
    int adjustment;

    width = 0;
    if (font->mode != 0)
        return font->fallbackWidth;
    if (font->signedMetric < 0)
        adjustment = 1;
    else
        adjustment = 0;
    glyphWidth = ((int far *)font->widths)[character];
    if (glyphWidth == -1)
        width = font->widths[font->fallbackIndex];
    else
        width = (unsigned char)glyphWidth;
    return width + adjustment;
}
