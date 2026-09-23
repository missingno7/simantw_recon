/* Hypothesis: SetUpPalette prepares indexed-color escape tables from the
   shared Dx8 tables, updates the Windows system-color cache, and restores
   the prior DC/palette state.  This source does not assume win_SetPalette's TU. */
struct PaletteEntryWords {
    unsigned int first;
    unsigned int second;
};

extern int near rootWnd;
extern int near paletteH;
extern unsigned char far Dx8[];
extern unsigned int far GetDC(int window);
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

static unsigned long setupSysColors[19];

void far SetUpPalette(int initialize)
{
    int dc;
    int index;
    int escapeIndex;
    int paletteWords[32];
    unsigned int red;
    unsigned int green;
    unsigned int blue;
    unsigned int packed;
    unsigned int systemColor;

    if (rootWnd == 0)
        return;

    dc = GetDC(0);
    if (GetDeviceCaps(dc, 12) < 8)
        goto finish;
    if (GetDeviceCaps(dc, 14) < 8)
        goto finish;

    escapeIndex = 4;
    if (initialize) {
        if (Escape(dc, 8, 2, &escapeIndex, 0, 0)) {
            escapeIndex = 4;
            if (Escape(dc, 8, 2, &escapeIndex, 0, 0)) {
                for (index = 0; index < 16; ++index) {
                    red = Dx8[0x8c42 + index * 4];
                    green = Dx8[0x8c41 + index * 4];
                    blue = Dx8[0x8c40 + index * 4];
                    packed = (red & 0x20) |
                        (((((blue & 0x10) >> 1 | (green & 0x10)) >> 1 |
                            (blue & 0x20) | (red & 0x10)) >> 1 |
                           (green & 0x20)) >> 1);
                    paletteWords[index * 2] = (green & 0x10) | (blue & 0x10);
                    paletteWords[index * 2 + 1] = packed;
                }
                Escape(dc, 4, 0x42, paletteWords, 0, 0);
            } else {
                Escape(dc, 4, 0, 0, 0, 0);
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
        for (index = 0; index < 19; ++index) {
            systemColor = (unsigned int)Dx8[0x8c80 + index * 2];
            setupSysColors[index] = GetSysColor(systemColor);
        }
        SetSysColors(19, (int far *)(Dx8 + 0x8c80),
                     (unsigned long far *)(Dx8 + 0x8ca6));
    }

finish:
    InitPalette();
    SelectPalette(dc, paletteH, 0);
    UnrealizeObject(paletteH);
    SelectPalette(dc, paletteH, 0);
    ReleaseDC(0, dc);
}
