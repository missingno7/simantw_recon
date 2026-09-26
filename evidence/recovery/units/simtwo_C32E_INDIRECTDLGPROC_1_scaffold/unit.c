/* Candidate translation unit simtwo_C32E_INDIRECTDLGPROC_1_scaffold: composed from preserved exact-body sources
 * in MAPSYM order. Internal evidence id, not a historical filename.
 * Members: INDIRECTDLGPROC
 * SCAFFOLDED: claimed members in 1 code runs; no pool stand-ins were needed. */

#define WM_PAINT        0x000f
#define WM_INITDIALOG   0x0110
#define WM_LBUTTONDOWN  0x0201
extern int near win_hwnd[];
extern long far PaintStuff(unsigned hwnd, unsigned msg, unsigned wParam, long lParam, long extra);
extern int far pascal SetProp(unsigned hwnd, char far *name, unsigned data);
extern unsigned far pascal SetCapture(unsigned hwnd);
extern void far pascal ReleaseCapture(void);
extern void far pascal EndDialog(unsigned hwnd, int result);




static int near dlgObject;
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

