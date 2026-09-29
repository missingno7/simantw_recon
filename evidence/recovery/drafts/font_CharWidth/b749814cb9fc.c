struct Font {
    unsigned char unused0[6];
    int fallbackWidth;
    int signedMetric;
    unsigned char unused1[4];
    int height;
    unsigned char unused2[6];
    int leading;
    unsigned char unused3[0x0a];
    unsigned char far *widths;
    int mode;
    int fallbackIndex;
};

volatile int _font_CharWidth(int character, struct Font far *font)
{
    volatile int glyphWidth;
    volatile int width;
    int adjustment;

    width = 0;
    if (font->mode != 0) {
        adjustment = font->signedMetric < 0;
        glyphWidth = ((int far *)font->widths)[character];
        if (glyphWidth == -1)
            width = font->widths[font->fallbackIndex];
        else
            width = (unsigned char)glyphWidth;
        return width + adjustment;
    }
    return font->fallbackWidth;
}