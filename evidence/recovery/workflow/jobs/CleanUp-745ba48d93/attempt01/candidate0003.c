/*
 * CleanUp: shut the application down.  The root window timer is killed
 * and pending WM_TIMER messages drained (PeekMessage with remove and
 * no-yield).  Every open window in the 40-entry win_hwnd table loses its
 * "INDEX" property and is destroyed.  Sound is uninstalled, help is
 * quit for the far help file name, the palette and fonts are closed, the
 * root window destroyed and cleared, the main root window (when the
 * ribbon bar window existed) likewise, and a quit message posted.  The
 * two "INDEX" property names are private string literals.
 */
struct MSG {
    int hwnd;
    unsigned int message;
    unsigned int wParam;
    long lParam;
    unsigned long time;
    int pt_x;
    int pt_y;
};

extern int near rootWnd;
extern int near ribbonBarWnd;
extern int near mainRootWnd;
extern int near win_hwnd[];
extern char far helpFile[];

extern int far pascal KillTimer(int window, unsigned int timer);
extern int far pascal PeekMessage(struct MSG far *message, int hwnd, unsigned int first, unsigned int last, unsigned int remove);
extern int far pascal RemoveProp(int window, char far *name);
extern int far pascal DestroyWindow(int window);
extern int far pascal WinHelp(int window, char far *file, unsigned int command, unsigned long data);
extern void far pascal PostQuitMessage(int code);
extern void far snd_Deinstall(void);
extern void far ClosePalette(void);
extern void far GCloseFonts(void);

void far CleanUp(void)
{
    struct MSG message;
    int near *p;
    int i;

    KillTimer(rootWnd, 0);
    while (PeekMessage(&message, 0, 0x113, 0x113, 3)) {
    }
    p = win_hwnd;
    for (i = 0; i < 40; i++) {
        if (p[i]) {
            RemoveProp(p[i], "INDEX");
            DestroyWindow(p[i]);
            p[i] = 0;
        }
    }
    snd_Deinstall();
    WinHelp(rootWnd, helpFile, 2, 0L);
    ClosePalette();
    GCloseFonts();
    DestroyWindow(rootWnd);
    rootWnd = 0;
    if (ribbonBarWnd) {
        ribbonBarWnd = 0;
        RemoveProp(mainRootWnd, "INDEX");
        DestroyWindow(mainRootWnd);
        mainRootWnd = 0;
    }
    PostQuitMessage(0);
}

