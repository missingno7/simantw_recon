/* Round 5, variant 2: rgb_array_presence hypothesis. */
/* Round 4, variant 2: header_and_low_caps hypothesis. */
/* Round 1, variant 4: packed_palette_bytes hypothesis. */
/* Hypothesis: SetUpPalette uses its parameter to select the color-table
   path, reads indexed RGB/system-color tables from their MAPSYM names, caches
   original system colors privately, then restores the selected GDI palette. */
extern int near rootWnd;
extern int near paletteH;
extern unsigned char far paletteFlag[];
extern unsigned char far rgb[];
extern unsigned int far sysColor[];
extern unsigned long far colorValue[];
extern unsigned char near displayType;
extern int far pascal GetDC(int window);
extern int far pascal ReleaseDC(int window, int dc);
extern int far pascal GetDeviceCaps(int dc, int index);
extern int far pascal Escape(int dc, int escape, int inputCount,
                             void far *input, int outputCount,
                             void far *output);
extern int far pascal SetSystemPaletteUse(int dc, int use);
extern unsigned long far pascal GetSysColor(int index);
extern int far pascal SetSysColors(int count, int far *indices,
                                   unsigned long far *colors);
extern int far pascal SelectPalette(int dc, int palette, int forceBackground);
extern int far pascal UnrealizeObject(int object);
extern void InitPalette(void);

static unsigned long oldSystemColors[19];

void far SetUpPalette(int initialize)
{
    int dc;
    int i;
    int escapeIndex;
    int oldPalette;
    unsigned int red;
    unsigned int green;
    unsigned int blue;
    unsigned char paletteWords[0x42];

    if (rootWnd == 0)
        return;

    dc = GetDC(0);
    if (paletteFlag[0x32] != 0) {
        if (GetDeviceCaps(dc, 12) < 8 && GetDeviceCaps(dc, 14) < 8) {
            escapeIndex = 4;
            if (initialize) {
                if (Escape(dc, 8, 2, &escapeIndex, 0, 0)) {
                    escapeIndex = 4;
                    if (Escape(dc, 8, 2, &escapeIndex, 0, 0)) {
                        if (rgb != 0) {
                            paletteWords[0] = 0;
                            paletteWords[1] = 0x10;
                            for (i = 0; i < 16; ++i) {
                                red = rgb[i * 4 + 2];
                                green = rgb[i * 4 + 1];
                                blue = rgb[i * 4];
                                paletteWords[2 + i * 4] = (unsigned char)blue;
                                paletteWords[3 + i * 4] = (unsigned char)green;
                                paletteWords[4 + i * 4] = red;
                                paletteWords[5 + i * 4] = 0;
                            }
                            Escape(dc, 4, 0x42, paletteWords, 0, 0);
                        } else {
                            Escape(dc, 4, 0, 0, 0, 0);
                        }
                    }
                }
            } else {
                if (Escape(dc, 8, 2, &escapeIndex, 0, 0)) {
                    escapeIndex = 4;
                    if (!Escape(dc, 8, 2, &escapeIndex, 0, 0))
                        Escape(dc, 4, 0, 0, 0, 0);
                }
            }

            if (GetDeviceCaps(dc, 0x26) & 0x100) {
                SetSystemPaletteUse(dc, 1);
                for (i = 0; i < 19; ++i)
                    oldSystemColors[i] = GetSysColor(sysColor[i]);
                SetSysColors(19, sysColor, colorValue);
            }
        }
    }

    InitPalette();
    oldPalette = SelectPalette(dc, paletteH, 0);
    UnrealizeObject(paletteH);
    SelectPalette(dc, oldPalette, 0);
    ReleaseDC(0, dc);
}
