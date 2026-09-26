/* Round 7: copied_both_volatile */
/* Round 1, variant 2: copied_pointer. */
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

int _font_CharWidth(int character, struct Font far *font)
{
    struct Font far *f = font;
    volatile int width;
    volatile int glyphWidth;
    int adjustment;

    width = 0;
    if (f->mode == 0)
        return f->fallbackWidth;
    if (f->signedMetric < 0)
        adjustment = 1;
    else
        adjustment = 0;
    glyphWidth = ((int far *)f->widths)[character];
    if (glyphWidth == -1)
        width = f->widths[f->fallbackIndex];
    else
        width = (unsigned char)glyphWidth;
    return width + adjustment;
}
