/* Paint the indexed window object while preserving the prior GDI selections. */
typedef void (far *PaintCallback)(void);

extern int near mainRootWnd;
extern int near rootWnd;
extern int near clipWind;
extern int near clipDC;
extern int near updateRgn;
extern int near paletteH;
static int near clipObject;
extern void RallocFindMem(long bytes);
extern int far pascal IsWindowVisible(int window);
extern unsigned int far pascal GetProp(int window, char far *name);
extern int far pascal CreateRectRgn(int left, int top, int right, int bottom);
extern int far pascal GetUpdateRgn(int window, int region, int erase);
extern int far pascal BeginPaint(int window, void far *paint);
extern int far pascal EndPaint(int window, void far *paint);
extern int far pascal SelectPalette(int dc, int palette, int forceBackground);
extern int far pascal RealizePalette(int dc);
extern int far pascal SelectObject(int dc, int object);
extern int far pascal DeleteObject(int object);
extern long far pascal DefWindowProc(int window, int message,
                                     unsigned int wParam, unsigned long lParam);
extern void InitPalette(void);
extern void far GSetBigFont(void);
extern void far win_DrawWindow(int objectNumber);

long far PaintStuff(int window, int message, unsigned int wParam,
                    unsigned long lParam, PaintCallback callback)
{
    char paint[32];
    int oldPalette;
    int objectNumber;

    if (window == mainRootWnd || window == rootWnd ||
        !IsWindowVisible(window))
        return DefWindowProc(window, message, wParam, lParam);

    objectNumber = GetProp(window, "INDEX");
    RallocFindMem(0x4e20L);
    clipWind = window;
    updateRgn = CreateRectRgn(0, 0, 10, 10);
    GetUpdateRgn(clipWind, updateRgn, 0);
    clipDC = BeginPaint(clipWind, paint);
    if (clipDC == 0)
        goto cleanup;

    InitPalette();
    oldPalette = SelectPalette(clipDC, paletteH, 0);
    RealizePalette(clipDC);
    clipObject = 0;
    GSetBigFont();
    win_DrawWindow(objectNumber);
    if (callback)
        callback();

    if (oldPalette != 0)
        SelectPalette(clipDC, oldPalette, 0);
    if (clipObject != 0) {
        SelectObject(clipDC, clipObject);
        clipObject = 0;
    }
    EndPaint(clipWind, paint);

cleanup:
    DeleteObject(updateRgn);
    {
        register int zero;
        zero = 0;
        updateRgn = zero;
        clipWind = zero;
        clipDC = zero;
        return zero;
    }
}

