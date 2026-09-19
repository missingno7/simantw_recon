/* Byte-matched reconstruction; historical declaration spelling is uncertain. */
struct Font {
    unsigned char unused0[14];
    int height;
    unsigned char unused1[6];
    int leading;
};

int _font_FontHeight(struct Font far *font)
{
    return font->height - 1;
}
