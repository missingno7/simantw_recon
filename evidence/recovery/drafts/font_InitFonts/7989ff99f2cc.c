/*
 * font_InitFonts: load the six game fonts.  The far out_buffer's image
 * pointer is aimed at the private font image buffer in
 * SIMANT_DATA_GROUP, then font_ReadFont loads "font1".."font6" into the
 * private far font table (the table's ten slots immediately precede the
 * buffer; only the first six are filled here).
 */
struct OutBuffer {
    int width;
    int height;
    void far *image;
};

extern struct OutBuffer far out_buffer;
static void far * __based(__segname("SIMANT_DATA_GROUP")) fonts[10];
static unsigned char __based(__segname("SIMANT_DATA_GROUP")) fontBuffer[1288];
extern void far * far font_ReadFont(char far *name);

void far font_InitFonts(void)
{
    out_buffer.image = fontBuffer;
    fonts[0] = font_ReadFont("font1");
    fonts[1] = font_ReadFont("font2");
    fonts[2] = font_ReadFont("font3");
    fonts[3] = font_ReadFont("font4");
    fonts[4] = font_ReadFont("font5");
    fonts[5] = font_ReadFont("font6");
}
