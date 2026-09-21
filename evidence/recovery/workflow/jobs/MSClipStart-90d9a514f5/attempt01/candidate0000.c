static int near clipPalette;
static int near clipObject;
extern int near updateRgn;
extern int near clipWind;
extern int near clipDC;
extern int near paletteH;

extern void far RallocFindMem(int low, int high);
extern int far pascal GetDC(int window);
extern void far InitPalette(void);
extern int far pascal SelectPalette(int dc, int palette, int forceBackground);
extern int far pascal RealizePalette(int dc);
extern void GSetBigFont(void);

void far MSClipStart(int window)
{
    RallocFindMem(0x4e20, 0);
    updateRgn = 0;
    clipWind = window;
    clipDC = GetDC(window);
    InitPalette();
    clipPalette = SelectPalette(clipDC, paletteH, 0);
    RealizePalette(clipDC);
    clipObject = 0;
    GSetBigFont();
}
