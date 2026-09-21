/* Candidate translation unit simant_5530_prefix2: composed from preserved exact-body sources
 * in MAPSYM order. Internal evidence id, not a historical filename.
 * Members: _PictStrnDialog, _win_DrawPictureWindow */

extern int far OptionStates[];
extern void far StopSimulation(void);
extern char far * far * far LoadStringAnt(int object);
extern void far PictureDialog(char far * far *strings, int count, int picture, int force);
extern void far free(void far *block);
extern void far db_PurgeObject(int object, int kind);
extern void far RestartSimulation(void);
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
static unsigned int near pictureBitmap;
static int near pictureLineCount;
static char far * far *pictureLines;
extern void far win_GetObjRect(int object, struct WinRect far *rect);
extern void far gr_BitMapSize(struct BitmapSize far *size, int bitmap);
extern void far win_DrawBitMap(int x, int y, unsigned int bitmap);
extern void far font_SetFont(int font);
extern int far font_FontHeight(void);
extern void far win_SetColorFromObjNum(int objectNumber);
extern void far gr_CenterStrInRect(struct WinRect far *rect, char far *string);

void far PictStrnDialog(int picture, int object, int force)
{
    int count;
    char far * far *strings;

    if (force != 0 || OptionStates[3] != 0) {
        StopSimulation();
        count = 0;
        strings = LoadStringAnt(object);
        if (strings) {
            while (strings[count] != 0)
                count++;
        }
        PictureDialog(strings, count, picture, force);
        if (strings) {
            free(strings);
            db_PurgeObject(object, 4);
        }
        RestartSimulation();
    }
}

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

