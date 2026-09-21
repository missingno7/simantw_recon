/*
 * font_DumpFont: release a loaded font.  When the far font pointer is
 * non-null, each of its three far buffer pointers (at 0x1a, 0x1e and
 * 0x22) is freed with mem_free when set, then the font block itself is
 * freed (guarded by a second null test on the parameter, which the
 * compiler re-evaluates from the stack).  The function returns a null
 * far pointer (xor ax,ax / cdq) so callers can clear their handle.
 */
struct Font {
    unsigned char header[0x1a];
    void far *glyphs;
    void far *widths;
    void far *offsets;
};

extern void far mem_free(void far *block);

struct Font far * far font_DumpFont(struct Font far *font)
{
    if (font) {
        if (font->glyphs)
            mem_free(font->glyphs);
        if (font->widths)
            mem_free(font->widths);
        if (font->offsets)
            mem_free(font->offsets);
        if (font)
            mem_free(font);
    }
    return 0;
}
