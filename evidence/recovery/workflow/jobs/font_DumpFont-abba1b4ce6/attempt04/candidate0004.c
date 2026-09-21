/*
 * font_DumpFont: release a loaded font.  When the far font pointer is
 * non-null, each of its three far buffer pointers (at 0x1a, 0x1e and
 * 0x22) is freed with mem_free when set, then the font block itself is
 * freed (guarded by a second null test).  The pointer is worked on
 * through a far local copy that the compiler keeps in ES:SI (les) and
 * whose segment it pushes from AX for the final free.  The function
 * returns a null far pointer (xor ax,ax / cdq) so callers can clear their
 * handle.
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
    if ((long)font != 0L) {
        if (font->glyphs)
            mem_free(font->glyphs);
        if (font->widths)
            mem_free(font->widths);
        if (font->offsets)
            mem_free(font->offsets);
        if ((long)font != 0L)
            mem_free(font);
    }
    return 0L;
}

