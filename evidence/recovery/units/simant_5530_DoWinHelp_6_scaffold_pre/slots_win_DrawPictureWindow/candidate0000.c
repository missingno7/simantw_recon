/*
 * win_DrawPictureWindow: redraw the picture window when its dirty flag
 * bit is set.  The window's rectangle is fetched, and if a picture
 * bitmap is selected it is drawn centred horizontally at the top of the
 * rectangle (advancing the rectangle top past it); otherwise the top is
 * just nudged down by two pixels.  The caption font and colour are then
 * set and each line of caption text is centred in a shrinking strip of
 * the rectangle, advancing by the font height per line.
 * Private BSS order follows the original words CAB4 (lines), CAB8 (count),
 * CABA (bitmap): declaration order fixes the private contribution layout.
 */
struct WinRect {
    int left;
    int top;
    int right;
    int bottom;
};

struct BitmapSize {
    int width;
    int height;
};

static char far * far *pictureLines;
static int near pictureLineCount;
static unsigned int near pictureBitmap;

extern void far win_GetObjRect(int object, struct WinRect far *rect);
extern void far gr_BitMapSize(struct BitmapSize far *size, int bitmap);
extern void far win_DrawBitMap(int x, int y, unsigned int bitmap);
extern void far font_SetFont(int font);
extern int far font_FontHeight(void);
extern void far win_SetColorFromObjNum(int objectNumber);
extern void far gr_CenterStrInRect(struct WinRect far *rect, char far *string);

void far win_DrawPictureWindow(int flags)
{
    struct WinRect rect;
    struct BitmapSize size;
    int fontHeight;
    int x;
    int i;

    if (!(flags & 2))
        return;

    win_GetObjRect(0x1e00, &rect);

    if (pictureBitmap == 0) {
        rect.top += 2;
    } else {
        gr_BitMapSize(&size, pictureBitmap);
        x = (rect.left + rect.right - size.width) / 2;
        win_DrawBitMap(x, rect.top, pictureBitmap);
        rect.top += size.height + 2;
    }

    font_SetFont(4);
    fontHeight = font_FontHeight();
    win_SetColorFromObjNum(0x1e01);

    for (i = 0; i < pictureLineCount; i++) {
        rect.bottom = rect.top + fontHeight;
        gr_CenterStrInRect(&rect, pictureLines[i]);
        rect.top += fontHeight;
    }
}
