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
extern volatile unsigned char __based(__segname("SIMANT_DATA_GROUP")) Dx8[];
extern int far pascal GetDesktopWindow(void);
extern int far pascal GetDC(int window);
extern int far pascal GetDeviceCaps(int dc, int index);
extern int far pascal ReleaseDC(int window, int dc);
extern unsigned int far pascal CreatePalette(struct LogicalPalette16 far *palette);
extern void far * far calloc(unsigned int count, unsigned int size);
extern void far free(void far *block);
void far InitPalette(void)
{
    int dc;
    int bits;
    int planes;
    int raster;
    unsigned long depth;
    int i;
    long bit;
    unsigned long colorCount;
    struct LogicalPalette16 far *palette;
    struct PaletteEntry16 far *entry;

    if (paletteH != 0) return;
    dc = GetDC(GetDesktopWindow());
    bits = GetDeviceCaps(dc, 12);
    planes = GetDeviceCaps(dc, 14);
    depth = bits * planes;
    if (depth == 0L) {
        colorCount = 1L;
    } else {
        colorCount = 1L;
        for (bit = 0L; bit < depth; ++bit)
            colorCount <<= 1;
    }
    if (colorCount > 20L) {
        raster = GetDeviceCaps(dc, 0x26);
        if ((raster & 0x0100) != 0) {
            colorCount -= 20L;
            palette = (struct LogicalPalette16 far *)calloc(((unsigned int)colorCount + 2U) * 4U, 1);
                palette->version = 0x0300;
                palette->count = (unsigned int)colorCount;
                for (i = 0; i < (unsigned int)colorCount; ++i) {
                unsigned int color;
                color = (unsigned int)(i % 15) * 4;
                palette->entries[i].red = (unsigned char)Dx8[0x8c40 + color];
                palette->entries[i].green = (unsigned char)Dx8[0x8c41 + color];
                palette->entries[i].blue = (unsigned char)Dx8[0x8c42 + color];
                palette->entries[i].flags = 4;
                }
                entry = palette->entries;
                for (i = 0; i < 16; ++i) {
                entry->red = Dx8[0x8c40 + i * 4];
                entry->green = Dx8[0x8c41 + i * 4];
                entry->blue = Dx8[0x8c42 + i * 4];
                entry->flags = 4;
                palette->entries[(unsigned int)colorCount - i].red = Dx8[0x8c7c - i * 4];
                palette->entries[(unsigned int)colorCount - i].green = Dx8[0x8c7d - i * 4];
                palette->entries[(unsigned int)colorCount - i].blue = Dx8[0x8c7e - i * 4];
                palette->entries[(unsigned int)colorCount - i].flags = 4;
                ++entry;
                }
                if (colorCount < 32L) {
                entry = palette->entries + 17;
                for (i = 0; i < 16; ++i) {
                    entry->red = Dx8[0x8c00 + i * 4];
                    entry->green = Dx8[0x8c01 + i * 4];
                    entry->blue = Dx8[0x8c02 + i * 4];
                    entry->flags = 4;
                    palette->entries[(unsigned int)colorCount - 16 - i].red = Dx8[0x8c3c - i * 4];
                    palette->entries[(unsigned int)colorCount - 16 - i].green = Dx8[0x8c3d - i * 4];
                    palette->entries[(unsigned int)colorCount - 16 - i].blue = Dx8[0x8c3e - i * 4];
                    palette->entries[(unsigned int)colorCount - 16 - i].flags = 4;
                    ++entry;
                }
                }
                paletteH = CreatePalette(palette);
                free(palette);
        } else {
            palette = (struct LogicalPalette16 far *)calloc(0x48, 1);
                palette->version = 0x0300;
                palette->count = 16;
                entry = palette->entries;
                for (i = 0; i < 16; ++i) {
                entry->red = Dx8[0x8c40 + i * 4];
                entry->green = Dx8[0x8c41 + i * 4];
                entry->blue = Dx8[0x8c42 + i * 4];
                entry->flags = 4;
                ++entry;
                }
                paletteH = CreatePalette(palette);
                free(palette);
        }
    }
    ReleaseDC(GetDesktopWindow(), dc);
}
