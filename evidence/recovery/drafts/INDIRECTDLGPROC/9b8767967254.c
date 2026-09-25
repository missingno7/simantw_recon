/*
 * IndirectDlgProc: exported dialog procedure for a window object opened as
 * an indirect dialog.  WM_PAINT is delegated wholesale to PaintStuff with a
 * zero extra argument and its long result returned.  WM_INITDIALOG records
 * the creating object number (low word of lParam) in a private near word,
 * stores the dialog handle in the win_hwnd table slot for that object's
 * window (object >> 8), attaches the object number as the "INDEX" window
 * property and captures the mouse.  WM_LBUTTONDOWN clears that window's
 * win_hwnd slot using the remembered object, releases the capture and ends
 * the dialog with result 0.  Everything else returns FALSE.
 */
#define WM_PAINT        0x000f
#define WM_INITDIALOG   0x0110
#define WM_LBUTTONDOWN  0x0201

extern int near win_hwnd[];
static int near dlgObject;

extern long far PaintStuff(unsigned hwnd, unsigned msg, unsigned wParam, long lParam, long extra);
extern int far pascal SetProp(unsigned hwnd, char far *name, unsigned data);
extern unsigned far pascal SetCapture(unsigned hwnd);
extern void far pascal ReleaseCapture(void);
extern void far pascal EndDialog(unsigned hwnd, int result);

long far pascal _export IndirectDlgProc(unsigned hwnd, unsigned msg, unsigned wParam, long lParam)
{
    switch (msg) {
    case WM_PAINT:
        return PaintStuff(hwnd, msg, wParam, lParam, 0L);
    case WM_INITDIALOG:
        dlgObject = (int)lParam;
        win_hwnd[(int)lParam >> 8] = hwnd;
        SetProp(hwnd, "INDEX", (int)lParam);
        SetCapture(hwnd);
        break;
    case WM_LBUTTONDOWN:
        win_hwnd[dlgObject >> 8] = 0;
        ReleaseCapture();
        EndDialog(hwnd, 0);
        break;
    }
    return 0L;
}
