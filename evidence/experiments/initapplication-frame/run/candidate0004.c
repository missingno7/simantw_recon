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
    struct WndClass wcRibbon, wcGeneric, wcRoot;
volatile char unused[26];

    wcRoot.style = 0;
    wcRoot.lpfnWndProc = MainWndProc;
    wcRoot.cbClsExtra = 0;
    wcRoot.cbWndExtra = 0;
    wcRoot.hInstance = hInstance;
    wcRoot.hIcon = LoadIcon(hInstance, "SimAnt");
    wcRoot.hCursor = LoadCursor(0, MAKEINTRESOURCE(0x7f00));
    wcRoot.hbrBackground = 0xd;
    wcRoot.lpszMenuName = 0;
    wcRoot.lpszClassName = "AntRoot";

    wcGeneric.style = 0x1008;
    wcGeneric.lpfnWndProc = MainWndProc;
    wcGeneric.cbClsExtra = 0;
    wcGeneric.cbWndExtra = 0;
    wcGeneric.hInstance = hInstance;
    wcGeneric.hIcon = LoadIcon(0, MAKEINTRESOURCE(0x7f00));
    wcGeneric.hCursor = LoadCursor(0, MAKEINTRESOURCE(0x7f00));
    wcGeneric.hbrBackground = 6;
    wcGeneric.lpszMenuName = 0;
    wcGeneric.lpszClassName = "GenericWindow";

    wcRibbon.style = 0x1008;
    wcRibbon.lpfnWndProc = MainWndProc;
    wcRibbon.cbClsExtra = 0;
    wcRibbon.cbWndExtra = 0;
    wcRibbon.hInstance = hInstance;
    wcRibbon.hIcon = LoadIcon(0, MAKEINTRESOURCE(0x7f00));
    wcRibbon.hCursor = LoadCursor(0, MAKEINTRESOURCE(0x7f00));
    wcRibbon.hbrBackground = GetStockObject(1);
    wcRibbon.lpszMenuName = 0;
    wcRibbon.lpszClassName = "RibbonWindow";

    return RegisterClass(&wcRibbon) | RegisterClass(&wcGeneric) | RegisterClass(&wcRoot);
}
