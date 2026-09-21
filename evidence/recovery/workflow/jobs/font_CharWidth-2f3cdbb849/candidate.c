struct Font {
    unsigned char reserved0[6];
    int fallbackWidth;
    int signedMetric;
    unsigned char reserved1[0x18];
    unsigned char far *widths;
    int mode;
    int fallbackIndex;
};

union FontPointer {
    struct Font far *pointer;
    unsigned int words[2];
};

int _font_CharWidth(int character, unsigned int fontOffset,
                    unsigned int fontSegment)
{
    int width;
    int glyphWidth;
    int adjustment;
    union FontPointer fontPointer;

    fontPointer.words[0] = fontOffset;
    fontPointer.words[1] = fontSegment;

    width = 0;
    if (fontPointer.pointer->mode != 0)
        return fontPointer.pointer->fallbackWidth;
    if (fontPointer.pointer->signedMetric < 0)
        adjustment = 1;
    else
        adjustment = 0;
    glyphWidth = ((int far *)fontPointer.pointer->widths)[character];
    if (glyphWidth == -1)
        width = fontPointer.pointer->widths[
            fontPointer.pointer->fallbackIndex];
    else
        width = (unsigned char)glyphWidth;
    return width + adjustment;
}
