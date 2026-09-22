/*
 * InitInstance: the classic WinMain companion that creates this
 * instance's three windows. Saves hInstance into hInst (MAPSYM 0xcc7c),
 * then creates the "AntRoot"-class main frame window mainRootWnd
 * (MAPSYM 0xcd7e) titled "SimAnt", sized to 98% of the screen width and
 * (90% of screen height minus GetSystemMetrics(SM_CYICON)) tall,
 * positioned at (screenWidth/100, screenHeight/100). The width/height
 * percentages use a 32-bit multiply-then-divide (compiler-generated
 * long division helper) to avoid 16-bit overflow; the plain x/y margins
 * use ordinary int division. Window/class name strings were read
 * directly from the shipped SIMANTW.EXE DGROUP data at DS:0x626/0x62d
 * (main), 0x635 (SetProp name), 0x63b/0x64d (ribbon), 0x65a/0x66d
 * (root); all match the classes InitApplication registers ("AntRoot",
 * "RibbonWindow"). On failure to create the main window, returns 0.
 * Otherwise: SetProp(mainRootWnd,"INDEX",-1), ShowWindow(cmdShow|3),
 * UpdateWindow, then reads mainRootWnd's client rect twice (once into
 * screenWidth/screenHeight -- the client area size despite the name --
 * and again to size the child ribbonBarWnd (MAPSYM 0xcd76, full client
 * width, height 0) and rootWnd (MAPSYM 0xcd78, full client rect), both
 * children of mainRootWnd sharing style 0x52000000. Both child windows
 * are updated and the function returns 1.
 */
struct Rect {
    int left;
    int top;
    int right;
    int bottom;
};

extern int near hInst;
extern int near mainRootWnd;
extern int near ribbonBarWnd;
extern int near rootWnd;
extern int near screenWidth;
extern int near screenHeight;

extern int far pascal GetSystemMetrics(int index);
extern int far pascal CreateWindow(char far *className, char far *windowName,
    unsigned long style, int x, int y, int width, int height,
    int parent, int menu, int instance, void far *param);
extern int far pascal SetProp(int window, char far *name, int data);
extern void far pascal ShowWindow(int window, int command);
extern void far pascal UpdateWindow(int window);
extern void far pascal GetClientRect(unsigned int window, struct Rect far *rect);

int far InitInstance(int hInstance, int cmdShow)
{
    struct Rect rect1, rect2;
    int height, heightCopy;

    hInst = hInstance;

    mainRootWnd = CreateWindow("AntRoot", "SimAnt", 0x02cf0000L,
        GetSystemMetrics(0) / 100,
        GetSystemMetrics(1) / 100,
        (int)((long)GetSystemMetrics(0) * 98 / 100),
        (height = (int)((long)GetSystemMetrics(1) * 90 / 100)) - GetSystemMetrics(12),
        0, 0, hInstance, 0);

    if (mainRootWnd == 0)
        return 0;

    SetProp(mainRootWnd, "INDEX", -1);
    ShowWindow(mainRootWnd, cmdShow | 3);
    UpdateWindow(mainRootWnd);

    GetClientRect(mainRootWnd, &rect1);
    screenWidth = rect1.right;
    screenHeight = rect1.bottom;

    GetClientRect(mainRootWnd, &rect2);

    ribbonBarWnd = CreateWindow("RibbonWindow", "SimAnt Ribbon Bar", 0x52000000L,
        0, 0, rect2.right, 0,
        mainRootWnd, 0, hInstance, 0);

    rootWnd = CreateWindow("AntRoot", "SimAnt Root Window", 0x52000000L,
        0, 0, rect2.right, rect2.bottom,
        mainRootWnd, 0, hInstance, 0);

    UpdateWindow(ribbonBarWnd);
    UpdateWindow(rootWnd);

    return 1;
}
