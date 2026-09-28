struct Font { unsigned char header[0x1a]; void far *glyphs; void far *widths; void far *offsets; };
extern void far mem_free(void far *block);
struct Font far * far font_DumpFont(struct Font far *font) {
    if ((unsigned long)font != 0L) {
        if (font->glyphs) mem_free(font->glyphs);
        if (font->widths) mem_free(font->widths);
        if (font->offsets) mem_free(font->offsets);
        if ((unsigned long)font != 0L) mem_free(font);
    }
    return 0;
}
