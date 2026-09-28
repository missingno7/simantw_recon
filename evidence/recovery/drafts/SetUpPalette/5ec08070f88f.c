/* Round 7, variant 2: palette_flag_word_entries hypothesis. */
/* Round 5, variant 2: rgb_array_presence hypothesis. */
/* Round 4, variant 2: header_and_low_caps hypothesis. */
/* Round 1, variant 4: packed_palette_bytes hypothesis. */
/* Hypothesis: SetUpPalette uses its parameter to select the color-table
   path, reads indexed RGB/system-color tables from their MAPSYM names, caches
   original system colors privately, then restores the selected GDI palette. */
extern int near rootWnd;
extern int near paletteH;
extern int far paletteFlag;
extern unsigned char far Dx8[];
extern unsigned int far sysColor[];
extern unsigned long far colorValue[];
extern unsigned char near displayType;
extern int far pascal GetDC(int window);
extern int far pascal ReleaseDC(int window, int dc);
extern int far pascal GetDeviceCaps(int dc, int index);
extern int far pascal Escape(int dc, int escape, int inputCount,
                             void far *input, void far *output);
extern int far pascal SetSystemPaletteUse(int dc, int use);
extern unsigned long far pascal GetSysColor(int index);
extern int far pascal SetSysColors(int count, int far *indices,
                                   unsigned long far *colors);
extern int far pascal SelectPalette(int dc, int palette, int forceBackground);
extern int far pascal UnrealizeObject(int object);
extern void InitPalette(void);

struct PaletteEntry {
    unsigned int greenBlue;
    unsigned int red;
};
struct PalettePacket {
    unsigned char flags;
    unsigned char count;
    struct PaletteEntry entries[16];
};

static unsigned long oldSystemColors[19];

void far SetUpPalette(volatile int initialize)
{
    int dc;
    int i;
    int escapeIndex;
    int fallbackIndex;
    int oldPalette;
    struct PalettePacket palette;

    if (rootWnd == 0)
        return;

    dc = GetDC(0);
    if (paletteFlag != 0 && GetDeviceCaps(dc, 12) < 8 &&
        GetDeviceCaps(dc, 14) < 8) {
        escapeIndex = 4;
        if (initialize) {
            if (Escape(dc, 8, 2, &escapeIndex, 0)) {
                i = 4;
                if (Escape(dc, 8, 2, &i, 0)) {
                    if (Dx8 != 0) {
                        palette.flags = 0;
                        palette.count = 0x10;
                        for (i = 0; i < 16; ++i) {
                            palette.entries[i].greenBlue =
                                (Dx8[0x8c41 + i * 4] << 8) |
                                 Dx8[0x8c40 + i * 4];
                            palette.entries[i].red = Dx8[0x8c42 + i * 4];
                        }
                        Escape(dc, 4, 0x42, &palette, 0);
                    } else {
                        Escape(dc, 4, 0, 0, 0);
                    }
                }
            }
        } else if (Escape(dc, 8, 2, &escapeIndex, 0)) {
            i = 4;
            if (!Escape(dc, 8, 2, &i, 0))
                Escape(dc, 4, 0, 0, 0);
        }

        if (GetDeviceCaps(dc, 0x26) & 0x100) {
            if (initialize) {
                SetSystemPaletteUse(dc, 2);
                for (i = 0; i < 19; ++i)
                    oldSystemColors[i] = GetSysColor(sysColor[i]);
                SetSysColors(19, sysColor, colorValue);
            } else {
                SetSystemPaletteUse(dc, 1);
                SetSysColors(19, sysColor, oldSystemColors);
            }
        }
    } else {
        fallbackIndex = 4;
        Escape(dc, 8, 2, &fallbackIndex, 0);
        fallbackIndex = 5;
        Escape(dc, 8, 2, &fallbackIndex, 0);
    }

    InitPalette();
    oldPalette = SelectPalette(dc, paletteH, 0);
    UnrealizeObject(paletteH);
    SelectPalette(dc, oldPalette, 0);
    ReleaseDC(0, dc);
}
