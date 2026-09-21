/*
 * font_DumpFont: release a loaded font.  When the far font pointer is
 * non-null, each of its three far buffer pointers (at 0x1a, 0x1e and
 * 0x22) is freed with mem_free when set, then the font block itself is
 * freed (guarded by a second null test).  The font is handled as a
 * doubleword handle (as in the verified ExtractWord cursor idiom) and
 * cast to the structure pointer at each use, which is why the compiler
 * loads it with les for the first member test, pushes its segment from AX
 * for the final free and returns a long zero (xor ax,ax / cdq).
 */
struct Font {
    unsigned char header[0x1a];
    void far *glyphs;
    void far *widths;
    void far *offsets;
};

extern void far mem_free(void far *block);

long far font_DumpFont(struct Font far *font)
{
    if (font) {
        if (font->glyphs)
            mem_free(font->glyphs);
        if (font->widths)
            mem_free(font->widths);
        if (font->offsets)
            mem_free(font->offsets);
        if (font)
            mem_free((void far *)font);
    }
    return 0L;
}

