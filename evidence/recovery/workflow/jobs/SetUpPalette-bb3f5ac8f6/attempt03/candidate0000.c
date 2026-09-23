/* Hypothesis: one SIMANT palette initializer. The target selector pool names
   paletteFlag in DGROUP and a segment-8 table rooted at Dx8; this source uses
   those observed bases and does not import win_SetPalette's source/TU. */
struct PaletteInput {
    unsigned char first;
    unsigned char count;
    unsigned int words[32];
};
extern int near rootWnd;
extern int near paletteH;
extern unsigned char far paletteFlag;
extern unsigned char far Dx8[];
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
    int escapeFirst;
    int escapeSecond;
    int oldPalette;
    struct PaletteInput input;

    if (rootWnd == 0)
        return;
    dc = GetDC(0);
    if (paletteFlag == 0)
        goto done;
    if (GetDeviceCaps(dc, 12) < 8)
        goto done;
    if (GetDeviceCaps(dc, 14) < 8)
        goto done;

    escapeFirst = 4;
    if (initialize == 0)
        goto alternate;
    if (Escape(dc, 8, 2, &escapeFirst, 0, 0) == 0)
        goto system_colors;
    escapeSecond = 4;
    if (Escape(dc, 8, 2, &escapeSecond, 0, 0) == 0)
        goto alternate_colors;

    input.first = 0;
    input.count = 0x10;
    if (displayType == 8)
        goto alternate_colors;
    for (i = 0; i < 16; ++i) {
        input.words[i * 2] = ((unsigned int)Dx8[0x8c41 + i * 4] << 8) |
                              Dx8[0x8c40 + i * 4];
        input.words[i * 2 + 1] = Dx8[0x8c42 + i * 4];
    }
    Escape(dc, 4, 0x42, &input, 0, 0);
    goto system_colors;

alternate_colors:
    Escape(dc, 4, 0, 0, 0, 0);
    goto system_colors;

alternate:
    if (Escape(dc, 8, 2, &escapeFirst, 0, 0) == 0)
        goto system_colors;
    escapeSecond = 4;
    if (Escape(dc, 8, 2, &escapeSecond, 0, 0) == 0)
        goto set_palette;
    Escape(dc, 4, 0, 0, 0, 0);
    goto set_palette;

system_colors:
    if ((GetDeviceCaps(dc, 0x26) & 0x100) == 0)
        goto set_palette;
    SetSystemPaletteUse(dc, 1);
    for (i = 0; i < 19; ++i)
        oldSystemColors[i] = GetSysColor(*(unsigned int far *)(Dx8 + 0x8c80 + i * 2));
    SetSysColors(19, (int far *)(Dx8 + 0x8c80),
                 (unsigned long far *)(Dx8 + 0x8ca6));

set_palette:
    InitPalette();
    oldPalette = SelectPalette(dc, paletteH, 0);
    UnrealizeObject(paletteH);
    SelectPalette(dc, oldPalette, 0);

done:
    ReleaseDC(0, dc);
}
