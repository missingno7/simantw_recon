/* Hypothesis: a palette-capable display gets a color-count-sized palette after reserving the 20 system colors; other displays use the fixed CGA table. */
struct PaletteEntry16 {
    unsigned char red;
    unsigned char green;
    unsigned char blue;
    unsigned char flags;
};
struct LogicalPalette16 {
    unsigned int version;
    unsigned int count;
    struct PaletteEntry16 entries[17];
};
extern int near paletteH;
extern char far Dx8[];
extern int far pascal GetDesktopWindow(void);
extern int far pascal GetDC(int window);
extern int far pascal GetDeviceCaps(int dc, int index);
extern int far pascal ReleaseDC(int window, int dc);
extern unsigned int far pascal CreatePalette(struct LogicalPalette16 far *palette);
extern void far * far calloc(unsigned int count, unsigned int size);
extern void far free(void far *block);
void far InitPalette(void)
{
    int window;
    int dc;
    int bits;
    int planes;
    int raster;
    int depth;
    int i;
    unsigned long colorCount;
    unsigned int count;
    struct LogicalPalette16 far *palette;
    struct PaletteEntry16 far *entry;

    if (paletteH != 0) return;
    window = GetDesktopWindow();
    dc = GetDC(window);
    bits = GetDeviceCaps(dc, 12);
    planes = GetDeviceCaps(dc, 14);
    depth = bits * planes;
    if (depth == 0)
        colorCount = 1L;
    else
        colorCount = 1L << depth;
    if (colorCount > 20L) {
        raster = GetDeviceCaps(dc, 0x26);
        if ((raster & 0x0100) != 0) {
            count = (unsigned int)(colorCount - 20L);
            palette = (struct LogicalPalette16 far *)calloc((count + 2U) * 4U, 1);
            if (palette != 0) {
                palette->version = 0x0300;
                palette->count = count;
                entry = palette->entries;
                for (i = 0; i < count; ++i) {
                    unsigned int color;
                    color = (unsigned int)(i % 15) * 4;
                    entry[i].red = (unsigned char)Dx8[0x8c40 + color];
                    entry[i].green = (unsigned char)Dx8[0x8c41 + color];
                    entry[i].blue = (unsigned char)Dx8[0x8c42 + color];
                    entry[i].flags = 4;
                }
                paletteH = CreatePalette(palette);
                free(palette);
            }
        } else {
            palette = (struct LogicalPalette16 far *)calloc(0x48, 1);
            if (palette != 0) {
                palette->version = 0x0300;
                palette->count = 16;
                for (i = 0; i < 16; ++i) {
                    palette->entries[i].red = (unsigned char)Dx8[0x8c00 + i * 4];
                    palette->entries[i].green = (unsigned char)Dx8[0x8c01 + i * 4];
                    palette->entries[i].blue = (unsigned char)Dx8[0x8c02 + i * 4];
                    palette->entries[i].flags = 4;
                }
                paletteH = CreatePalette(palette);
                free(palette);
            }
        }
    }
    ReleaseDC(window, dc);
}
