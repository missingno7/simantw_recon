/*
 * win_DrawCasteWindow: redraw the caste tool window (0x1300).  Bit 0 of
 * flags redraws the caste-mix bitmap object (0x1302): the window is
 * clipped to it unless a caste animation is already running there, and
 * if a caste bitmap is allocated it is locked and blitted at the
 * object's rectangle, 4bpp via DoFastBitmap unless displayType marks a
 * monochrome-class display (then 1bpp via DoFastMonoBitmap); the locked
 * bitmap's first two words are its width/height, the pixel data follows.
 * Bit 1 of flags redraws the caste level bars via DrawControlLevels,
 * passing the private level value the caste-mix handlers maintain.
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

extern int far casteAnimHandle;
extern unsigned int near casteBitmap;
extern unsigned char near displayType;
static int near casteLevel = 1;

extern void far clip_SetWin(int window);
extern void far *mem_Lock(unsigned int handle);
extern int far mem_Unlock(unsigned int handle);
extern void far win_GetObjRect(int object, struct WinRect far *rect);
extern void far DoFastBitmap(int x, int y, int width, int height, char far *bits, int flags);
extern void far DoFastMonoBitmap(int x, int y, int width, int height, char far *bits);
extern void far DrawControlLevels(int window, int index, int level);

void far win_DrawCasteWindow(int flags)
{
    struct WinRect rect;
    struct FastBitmap far *bits;
    int x, y;

    if ((char)flags & 1) {
        if (casteAnimHandle == 0)
            clip_SetWin(0x1300);
    }
    if ((char)flags & 1) {
        if (casteBitmap != 0) {
            bits = (struct FastBitmap far *)mem_Lock(casteBitmap);
            win_GetObjRect(0x1302, &rect);
            x = rect.left;
            y = rect.top;
            if ((displayType & 1) == 0)
                DoFastBitmap(x, y, bits->width, bits->height, (char far *)(bits + 1), 0);
            else
                DoFastMonoBitmap(x, y, bits->width, bits->height, (char far *)(bits + 1));
            mem_Unlock(casteBitmap);
        }
    }
    if (flags & 2)
        DrawControlLevels(0x1300, 0, casteLevel);
}
