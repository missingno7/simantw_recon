/*
 * InitApplication: register the three window classes used by the game
 * (the classic WinMain-companion routine, called once when there is no
 * previous instance). Each class shares lpfnWndProc = MainWndProc
 * (MAPSYM MAINWNDPROC, this unit's own window procedure). The class
 * name and icon-name string literals were read directly from the
 * shipped SIMANTW.EXE DGROUP data at DS:0x675 ("SimAnt"), DS:0x67c
 * ("AntRoot"), DS:0x684 ("GenericWindow") and DS:0x692 ("RibbonWindow").
 * "AntRoot" (custom icon, style 0, background 0xd = COLOR_APPWORKSPACE+1)
 * is the root/main frame class; "GenericWindow" (default icon, style
 * 0x1008, background 6 = COLOR_WINDOW+1) and "RibbonWindow" (default
 * icon, style 0x1008, background GetStockObject(LTGRAY_BRUSH)) are
 * filled in that order (AntRoot, GenericWindow, RibbonWindow) but
 * registered in the opposite order (RibbonWindow, GenericWindow,
 * AntRoot), with the three RegisterClass results combined by bitwise
 * OR into the return value.
 */
#define MAKEINTRESOURCE(id) ((char far *)(unsigned long)(id))

typedef long (far pascal *WNDPROC)(int, unsigned int, int, long);

struct WndClass {
    unsigned int style;
    WNDPROC lpfnWndProc;
    int cbClsExtra;
    int cbWndExtra;
    unsigned int hInstance;
    unsigned int hIcon;
    unsigned int hCursor;
    unsigned int hbrBackground;
    char far *lpszMenuName;
    char far *lpszClassName;
};

extern long far pascal MainWndProc(int window, unsigned int message, int wParam, long lParam);
extern unsigned int far pascal LoadIcon(unsigned int instance, char far *name);
extern unsigned int far pascal LoadCursor(unsigned int instance, char far *name);
extern unsigned int far pascal GetStockObject(int object);
extern unsigned int far pascal RegisterClass(struct WndClass far *wndClass);

int far InitApplication(int hInstance)
{
    struct WndClass wc[3];

    wc[0].style = 0;
    wc[0].lpfnWndProc = MainWndProc;
    wc[0].cbClsExtra = 0;
    wc[0].cbWndExtra = 0;
    wc[0].hInstance = hInstance;
    wc[0].hIcon = LoadIcon(hInstance, "SimAnt");
    wc[0].hCursor = LoadCursor(0, MAKEINTRESOURCE(0x7f00));
    wc[0].hbrBackground = 0xd;
    wc[0].lpszMenuName = 0;
    wc[0].lpszClassName = "AntRoot";

    wc[1].style = 0x1008;
    wc[1].lpfnWndProc = MainWndProc;
    wc[1].cbClsExtra = 0;
    wc[1].cbWndExtra = 0;
    wc[1].hInstance = hInstance;
    wc[1].hIcon = LoadIcon(0, MAKEINTRESOURCE(0x7f00));
    wc[1].hCursor = LoadCursor(0, MAKEINTRESOURCE(0x7f00));
    wc[1].hbrBackground = 6;
    wc[1].lpszMenuName = 0;
    wc[1].lpszClassName = "GenericWindow";

    wc[2].style = 0x1008;
    wc[2].lpfnWndProc = MainWndProc;
    wc[2].cbClsExtra = 0;
    wc[2].cbWndExtra = 0;
    wc[2].hInstance = hInstance;
    wc[2].hIcon = LoadIcon(0, MAKEINTRESOURCE(0x7f00));
    wc[2].hCursor = LoadCursor(0, MAKEINTRESOURCE(0x7f00));
    wc[2].hbrBackground = GetStockObject(1);
    wc[2].lpszMenuName = 0;
    wc[2].lpszClassName = "RibbonWindow";

    return RegisterClass(&wc[2]) | RegisterClass(&wc[1]) | RegisterClass(&wc[0]);
}
