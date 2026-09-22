/*
 * win_DrawModeWindow: redraw the mode tool window (0x1200).  Bit 0 of
 * flags redraws the mode-mix bitmap object (0x1202): the window is
 * clipped to it unless a mode animation is already running there, and
 * if a mode bitmap is allocated it is locked and blitted at the
 * object's rectangle, 4bpp via DoFastBitmap unless displayType marks a
 * monochrome-class display (then 1bpp via DoFastMonoBitmap); the locked
 * bitmap's first two words are its width/height, the pixel data follows.
 * Bit 1 of flags redraws the mode level bars via DrawControlLevels,
 * passing the private level value the mode-mix handlers maintain.
 * Structural twin of win_DrawCasteWindow (same unit_context simant:B324).
 */
struct WinRect {
    int left;
    int top;
    int right;
    int bottom;
};

struct FastBitmap {
    int width;
    int height;
};

extern int far modeAnimHandle;
extern int near modeBitmap;
extern unsigned char near displayType;
static int near modeLevel = 1;

extern void far clip_SetWin(int window);
extern void far *mem_Lock(unsigned int handle);
extern int far mem_Unlock(unsigned int handle);
extern void far win_GetObjRect(int object, struct WinRect far *rect);
extern void far DoFastBitmap(int x, int y, int width, int height, char far *bits, int flags);
extern void far DoFastMonoBitmap(int x, int y, int width, int height, char far *bits);
extern void far DrawControlLevels(int window, int index, int level);

void far win_DrawModeWindow(int flags)
{
    struct WinRect rect;
    struct { int x, y; } pos;
    struct FastBitmap far *bits;

    if (flags & 1) {
        if (modeAnimHandle == 0)
            clip_SetWin(0x1200);
    }
    if (flags & 1) {
        if (modeBitmap != 0) {
            bits = (struct FastBitmap far *)mem_Lock(modeBitmap);
            win_GetObjRect(0x1202, &rect);
            pos.x = rect.left;
            pos.y = rect.top;
            if ((displayType & 1) == 0)
                DoFastBitmap(pos.x, pos.y, bits->width, bits->height, (char far *)(bits + 1), 0);
            else
                DoFastMonoBitmap(pos.x, pos.y, bits->width, bits->height, (char far *)(bits + 1));
            mem_Unlock(modeBitmap);
        }
    }
    if (flags & 2)
        DrawControlLevels(0x1200, 0, modeLevel);
}
