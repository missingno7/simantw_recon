/* Hypothesis: construct the device palette from the SimAnt color tables after checking the desktop display caps. */
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
    struct LogicalPalette16 far *palette;

    if (paletteH != 0) return;
    window = GetDesktopWindow();
    dc = GetDC(window);
    bits = GetDeviceCaps(dc, 12);
    planes = GetDeviceCaps(dc, 14);
    depth = bits * planes;
    raster = GetDeviceCaps(dc, 0x26);
    if ((raster & 0x0100) != 0 && depth != 0) {
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
    ReleaseDC(window, dc);
}
